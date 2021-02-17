#include "stdafx.h"
#include "NaviObj.h"
#include "Cell.h"
#include "Line.h"
CNaviObj::CNaviObj(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
	,m_bModding(false)
	, m_bHideVtx(false)
	,m_bHideCell(false)
{
}

HRESULT CNaviObj::Ready_Prototype()
{
	//Trans
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	//NaviMesh
	m_pNaviCom = (CNaviMesh*)CManagement::Get_Instance()->Clone_Resource(m_szNaviTag, eResourcesID::NaviMesh);
	CGameObject::Add_Component(eComponentID::NaviMesh, m_pNaviCom);
	//Static
	m_pStaticMesh = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(L"Sphere", eResourcesID::StaticMesh);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pStaticMesh);
	m_eRenderID = eRenderID::Priority;

	return S_OK;
}

HRESULT CNaviObj::Awake_GameObject()
{
return S_OK;
}

HRESULT CNaviObj::Ready_GameObject()
{
	return S_OK;
}

_uint CNaviObj::UpdateGameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);

	//Hide Option 
	if (m_bHideCell != m_pNaviCom->IsHideCell())
		m_pNaviCom->Set_HideCell(m_bHideCell);


	return _uint();
}

_uint CNaviObj::LateUpdateGameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CNaviObj::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pNaviCom->Render_Meshes();
	Render_CellVertex();
	return S_OK;
}

CGameObject * CNaviObj::Clone()
{
	return nullptr;
}

void CNaviObj::Render_CellVertex()
{
	if (m_bHideVtx)
		return;

	CManagement::Get_Instance()->Get_Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	_matrix CellVTXWorld;
	D3DXMatrixIdentity(&CellVTXWorld);
	for (auto& CellVtx : m_pNaviCom->Get_vCellVtx())
	{
		CellVTXWorld._11 = 0.2f;
		CellVTXWorld._22 = 0.2f;
		CellVTXWorld._33 = 0.2f;
		CellVTXWorld._41 = CellVtx.x;
		CellVTXWorld._42 = CellVtx.y;
		CellVTXWorld._43 = CellVtx.z;
		CManagement::Get_Instance()->Get_Device()->SetTransform(D3DTS_WORLD, &CellVTXWorld);
		//CManagement::Get_Instance()->Get_Device()->SetTexture(0, nullptr);
		m_pStaticMesh->Render_Meshes();

	}

	CManagement::Get_Instance()->Get_Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

bool CNaviObj::Vertex_Peeking(_vec2 pt, OUT int& idx)
{
	_matrix CellVTXWorld;
	D3DXMatrixIdentity(&CellVTXWorld);
	BOOL	bHit = false;
	DWORD   dwIndex = 0;
	LPD3DXBUFFER ppHits = nullptr;
	DWORD	pCountHit = 0;
	_vec3	vRayDir, vRayPos , vOriRayDir, vOriRayPos;
	_uint iIndex = 0;
	
	SetUpRay(pt, vOriRayPos, vOriRayDir);

	//To Local
	for (auto& CellVtx : m_pNaviCom->Get_vCellVtx())
	{
		D3DXMatrixTranslation(&CellVTXWorld, CellVtx.x, CellVtx.y, CellVtx.z);
		D3DXMatrixInverse(&CellVTXWorld, NULL, &CellVTXWorld);
		D3DXVec3TransformCoord(&vRayPos, &vOriRayPos, &CellVTXWorld);
		D3DXVec3TransformNormal(&vRayDir, &vOriRayDir, &CellVTXWorld);
		_float	fU, fV, fDist;
		D3DXIntersect(m_pStaticMesh->Get_OriMesh(),
			&vRayPos, &vRayDir, &bHit, &dwIndex, &fU, &fV, &fDist, &ppHits, &pCountHit);
		if (bHit == TRUE)
		{
			idx = iIndex;
			return true;
		}
		++iIndex;
	}
	return  false;
}

_bool CNaviObj::Cell_Peeking(_vec2 pt, OUT int & idx)
{
	_vec3	vRayDir, vRayPos;
	_float	fU, fV, fDist;

	SetUpRay(pt, vRayPos, vRayDir);

	for (auto& Cell : m_pNaviCom->Get_vCell())
	{
		const _vec3* A = Cell->Get_Point(eCellpt::A);
		const _vec3* B = Cell->Get_Point(eCellpt::B);
		const _vec3* C = Cell->Get_Point(eCellpt::C);

		if (D3DXIntersectTri(A, B, C, &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			idx = Cell->Get_CellIndex();
			return true;
		}
	}
	return false;
}

void CNaviObj::SetUpRay(const _vec2& pt, OUT _vec3 & RayPos, OUT _vec3 & RayDir)
{
	_vec3	 vViewPortPt;
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	_matrix matProj, matView;

	CManagement::Get_Instance()->Get_Device()->GetViewport(&ViewPort);
	CManagement::Get_Instance()->Get_Device()->GetTransform(D3DTS_PROJECTION, &matProj);
	CManagement::Get_Instance()->Get_Device()->GetTransform(D3DTS_VIEW, &matView);

	// to Proj
	vViewPortPt.x = pt.x / (ViewPort.Width * 0.5f) - 1.f;
	vViewPortPt.y = pt.y / -(ViewPort.Height * 0.5f) + 1.f;
	vViewPortPt.z = 0.1f;


	// To Veiw
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vViewPortPt, &vViewPortPt, &matProj);


	RayPos = _vec3(0.f, 0.f, 0.f);
	RayDir = vViewPortPt - RayPos;

	// To world
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&RayPos, &RayPos, &matView);
	D3DXVec3TransformNormal(&RayDir, &RayDir, &matView);
}

HRESULT CNaviObj::SaveFile(const _tchar * pFilePath)
{
	//CString strFileName = Dlg.GetFileName();
	HANDLE hFile = CreateFile(pFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte;
	/*
	(네비매쉬 아이디)
	버텍스 백터

	인덱스 백터
	-트리거 쉘-	
	(트리거 셀 갯수)
	트리거 셀인덱스번호
	라인 트리거라인이 몇개인지 
	몇번 라인, 라인 타입
	(Connect 일경우 다음 네비 매쉬Id ,셀 인덱스)

	*/
	//WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

	_uint iSize = m_pNaviCom->Get_vCellVtx().size(); // vtxvector size
	WriteFile(hFile, &iSize, sizeof(_uint), &dwByte, nullptr);

	for (auto& vtxPos : m_pNaviCom->Get_vCellVtx())
	{
		WriteFile(hFile, &vtxPos, sizeof(_vec3), &dwByte, nullptr);
	}
	iSize = m_pNaviCom->Get_vIndex().size(); // Cellidx size
	WriteFile(hFile, &iSize, sizeof(_uint), &dwByte, nullptr);

	for (auto& vtxIndex : m_pNaviCom->Get_vIndex())
	{
		WriteFile(hFile, &vtxIndex, sizeof(CELLVTXIDX), &dwByte, nullptr);
	}
	//트리거 셀이 몇개인지 그거 저장해서 리저브 용으로 


	for (auto& pCell : m_pNaviCom->Get_vCell())
	{
		if (pCell->Get_CellType() != eCellType::Base)
		{
			_uint iCellIdx = pCell->Get_CellIndex();
			_uint iCellType = pCell->Get_CellType();
			WriteFile(hFile, &iCellIdx, sizeof(_uint), &dwByte, nullptr); // pCellIdx
			WriteFile(hFile, &iCellType, sizeof(_uint), &dwByte, nullptr); // pCellIdx
			for (int i = 0; i < eLineID::End; ++i)
			{
				_uint iLineType = pCell->Get_Line((eLineID::eLineID)i)->Get_Type();
				WriteFile(hFile, &iLineType, sizeof(_uint), &dwByte, nullptr); // lineType
				// IF 추가해서 추가로 쓰기 
			}
		}
	}
	CloseHandle(hFile);
	return S_OK;
}

CNaviObj * CNaviObj::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pComTag)
{
	//하나씩으로만 안만들거같은데 
	CNaviObj* pIns = new CNaviObj(pDevice);
	pIns->Set_Tag(pComTag);
	pIns->Ready_Prototype();
	return pIns;
}

void CNaviObj::Free()
{
	CGameObject::Free();
}
