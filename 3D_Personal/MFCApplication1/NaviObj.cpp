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
	//Static
	m_pStaticMesh = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(L"Sphere", eResourcesID::StaticMesh);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pStaticMesh);
	m_eRenderID = eRenderID::Priority;

	//ZeroMemory(m_pTexture, sizeof(LPDIRECT3DTEXTURE9) * 2);
	ZeroMemory(m_ipeekIdx, sizeof(_int) * eCellpt::End);

	for (_ulong i = 0; i < 2; ++i)
	{
		m_pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

		D3DLOCKED_RECT		LockRect;
		ZeroMemory(&LockRect, sizeof(D3DLOCKED_RECT));
		m_pTexture[i]->LockRect(0, &LockRect, NULL, 0);
		*((_ulong*)LockRect.pBits) = D3DXCOLOR(1.f , 1.f - (1.f * i), 1.f - (1.f * i), 1.f);
		m_pTexture[i]->UnlockRect(0);
	}

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

_uint CNaviObj::Update_GameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);

	//Hide Option 
	if (m_bHideCell != m_pNaviCom->IsHideCell())
		m_pNaviCom->Set_HideCell(m_bHideCell);


	return _uint();
}

_uint CNaviObj::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CNaviObj::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pDevice->SetTexture(0, nullptr);
	m_pNaviCom->Render_Meshes();
	Render_CellVertex();
	return S_OK;
}

CGameObject * CNaviObj::Clone()
{
	return nullptr;
}

void CNaviObj::Set_Navi( CNaviMesh * pNavi)
{
	if (m_pNaviCom != nullptr)
		return;

	m_pNaviCom = pNavi;
	CGameObject::Add_Component(eComponentID::NaviMesh, m_pNaviCom);
}

void CNaviObj::Render_CellVertex()
{
	if (m_bHideVtx)
		return;

	CManagement::Get_Instance()->Get_Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	_matrix CellVTXWorld;
	D3DXMatrixIdentity(&CellVTXWorld);
	_int iIndex = 0;
	for (auto& CellVtx : m_pNaviCom->Get_Vertex())
	{
		//피킹에 따라 텍스쳐 변경 
		//m_pDevice->SetTexture(0, m_pTexture[true]);
		if (Check_Peeking(iIndex))
			m_pDevice->SetTexture(0, m_pTexture[1]);
		else
			m_pDevice->SetTexture(0, m_pTexture[0]);


		CellVTXWorld._11 = 0.15f;
		CellVTXWorld._22 = 0.15f;
		CellVTXWorld._33 = 0.15f;
		CellVTXWorld._41 = CellVtx.x;
		CellVTXWorld._42 = CellVtx.y;
		CellVTXWorld._43 = CellVtx.z;
		CManagement::Get_Instance()->Get_Device()->SetTransform(D3DTS_WORLD, &CellVTXWorld);
		//CManagement::Get_Instance()->Get_Device()->SetTexture(0, nullptr);
		m_pStaticMesh->Render_Meshes();
		++iIndex;
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
	for (auto& CellVtx : m_pNaviCom->Get_Vertex())
	{
		CellVTXWorld._11 = 0.15f;
		CellVTXWorld._22 = 0.15f;
		CellVTXWorld._33 = 0.15f;
		CellVTXWorld._41 = CellVtx.x;
		CellVTXWorld._42 = CellVtx.y;
		CellVTXWorld._43 = CellVtx.z;

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

_bool CNaviObj::Cell_Peeking(_vec2 pt, OUT int & idx , OUT _vec3& PeekPos)
{
	_vec3	vRayDir, vRayPos;
	_float	fU, fV, fDist;
	// V1 + U(V2 - V1) + V(V3 - V1).
	SetUpRay(pt, vRayPos, vRayDir);

	for (auto& Cell : m_pNaviCom->Get_vCell())
	{
		const _vec3* A = Cell->Get_Point(eCellpt::A);
		const _vec3* B = Cell->Get_Point(eCellpt::B);
		const _vec3* C = Cell->Get_Point(eCellpt::C);

		if (D3DXIntersectTri(A, B, C, &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			PeekPos = *A + (fU *(*B - *A)) + (fV * (*C - *A));
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

_bool CNaviObj::Check_Peeking(const _int & iIdx)
{
	if (m_bPeekCell)
	{
		for (int i = 0; i < eCellpt::End; ++i)
			if (iIdx == m_ipeekIdx[i])
				return true;
	}
	else if(m_bPeekVTX)
	{
		if (iIdx == m_ipeekIdx[0])
			return true;
	}
	return false;
}

HRESULT CNaviObj::SaveFile(const _tchar * pFilePath)
{
	//CString strFileName = Dlg.GetFileName();
	HANDLE hFile = CreateFile(pFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte;
	/*
	네비매쉬 아이디
	base Color
	버텍스 백터크기 , 데이터 
	인덱스 백터크기 , 데이터 

	-트리거 셀orline 
	셀 idx
	셀의 라인이 트리거인지 
	bool 값에 따라 
	라인 트리거라인이 몇개인지 
	몇번 라인, 라인 타입
	--
	셀의 
	*/
	//WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

	_vec3 vColor = m_pNaviCom->Get_Color();
	_int iNaviID = m_pNaviCom->Get_NaviID();
	WriteFile(hFile, &iNaviID, sizeof(_int), &dwByte, nullptr); // iD
	WriteFile(hFile, &vColor, sizeof(_vec3), &dwByte, nullptr); // Base Color

	_uint iSize = m_pNaviCom->Get_Vertex().size(); // vtxvector size
	WriteFile(hFile, &iSize, sizeof(_uint), &dwByte, nullptr);

	for (auto& vtxPos : m_pNaviCom->Get_Vertex())
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
		if (pCell->Get_CellType() == eCellType::Connect || pCell->IsOnLineTrigger())
		{
			_uint iCellIdx = pCell->Get_CellIndex();
			_bool isOnLineTrigger = pCell->IsOnLineTrigger();
			WriteFile(hFile, &iCellIdx, sizeof(_uint), &dwByte, nullptr); // pCellIdx
			WriteFile(hFile, &isOnLineTrigger, sizeof(_bool), &dwByte, nullptr); // onLineTrigger

			//라인으로 connect
			if (isOnLineTrigger)
			{
				for (int i = 0; i < eLineID::End; ++i)
				{
					// lineType
					_uint iLineType = pCell->Get_Line((eLineID::eLineID)i)->Get_Type();
					WriteFile(hFile, &iLineType, sizeof(_uint), &dwByte, nullptr);
					// IF 추가해서 추가로 쓰기 
					if (iLineType == eCellType::Connect)
					{
						_uint iLinkCellsCnt = pCell->Get_Line((eLineID::eLineID)i)->Get_LinkCells().size();
						vector<LINKCELL>& Linkcells = pCell->Get_Line((eLineID::eLineID)i)->Get_LinkCells();
						WriteFile(hFile, &iLinkCellsCnt, sizeof(_uint), &dwByte, nullptr); // size
						for (auto& LinkCell : Linkcells)
						{
							WriteFile(hFile, &LinkCell.iNaviID, sizeof(_int), &dwByte, nullptr); // Connet navid
							WriteFile(hFile, &LinkCell.iCellIdx, sizeof(_int), &dwByte, nullptr); // Connet cellidx
						}
					}
				}
			}
			//Cell에서 connet
			else
			{
				vector<LINKCELL>& Linkcells =  pCell->Get_LinkCells();
				_uint iLinkCellsCnt = Linkcells.size();
				WriteFile(hFile, &iLinkCellsCnt, sizeof(_uint), &dwByte, nullptr); // size
				for (auto& LinkCell : Linkcells)
				{
					WriteFile(hFile, &LinkCell.iNaviID, sizeof(_int), &dwByte, nullptr); // Connet navid
					WriteFile(hFile, &LinkCell.iCellIdx, sizeof(_int), &dwByte, nullptr); // Connet cellidx
				}
			}
		
		}
	}
	CloseHandle(hFile);
	return S_OK;
}

CNaviObj * CNaviObj::Create(LPDIRECT3DDEVICE9 pDevice)
{
	//하나씩으로만 안만들거같은데 
	CNaviObj* pIns = new CNaviObj(pDevice);
	pIns->Ready_Prototype();
	return pIns;
}

void CNaviObj::Free()
{
	for (int i = 0; i < 2; ++i)
	{
		SafeRelease(m_pTexture[i]);
	}
	CGameObject::Free();
}
