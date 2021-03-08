#include "NaviMesh.h"


USING(Engine)

CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
	, m_bHideCell(false)
	, m_bSelect(false)
	, m_bLoad(false)
	, m_iNaviID(NOT_FOUND)
	, m_vBaseColor(VCOLOR_GRAY)
	, m_bToolMode(false)
{
}

CNaviMesh::CNaviMesh(const CNaviMesh& other)
	: CComponent(other)
	, m_vecCell(other.m_vecCell)
	, m_vecVTX(other.m_vecVTX)
	, m_vecIndex(other.m_vecIndex)
	, m_bSelect(false)
	, m_bLoad(other.m_bLoad)
	, m_vecLoadData(other.m_vecLoadData)
	, m_iNaviID(other.m_iNaviID)
	, m_bHideCell(false)
	, m_vBaseColor(other.m_vBaseColor)
	, m_bToolMode(other.m_bToolMode)
{
	for (auto& iter : m_vecCell)
		iter->AddRef();

	MSG_BOX(L"warring CNaviMesh clone");
}


HRESULT Engine::CNaviMesh::Ready_NavigationMesh(vector<CNaviMesh*>* pNaviMeshs)
{
	CCell* pCell = nullptr;
	if(m_bToolMode)
		m_listRelation.resize(m_vecVTX.size(), list<CCell*>());

	for (size_t i = 0; i < m_vecIndex.size(); ++i)
	{
		if(m_bLoad)
			pCell = CCell::Create(m_pDevice, i, m_vecIndex[i], &m_vecVTX,m_vBaseColor, m_bToolMode, pNaviMeshs);
		else
			pCell = CCell::Create(m_pDevice, i , m_vecIndex[i], &m_vecVTX,VCOLOR_GRAY,m_bToolMode);

		NULL_CHECK_RETURN(pCell, E_FAIL);
		m_vecCell.push_back(pCell);

		if (m_bToolMode)
		{
			m_listRelation[m_vecIndex[i]._A - 1].emplace_back(pCell);
			m_listRelation[m_vecIndex[i]._B - 1].emplace_back(pCell);
			m_listRelation[m_vecIndex[i]._C - 1].emplace_back(pCell);
		}

	}

	FAILED_CHECK(Link_Cell());

	if (m_bLoad)
	{
		
		// 트리거 셀 , 트리거 라인 로드 데이터 적용
		for (auto& tTriggerCell : m_vecLoadData)
		{
			if (tTriggerCell.bOnLineTrigger)
			{
				for (size_t i = 0; i < eLineID::End; ++i)
				{
					m_vecCell[tTriggerCell.iCellIdx]->Set_LineTrigger((eLineID::eLineID)i, (eCellType::eCellType)tTriggerCell.vLine[i].iLineType);
					if (tTriggerCell.vLine[i].iLineType == eCellType::Connect)
					{
						for (auto& LinkCell : tTriggerCell.vLine[i].vecLinkCells)
						{
							m_vecCell[tTriggerCell.iCellIdx]->Get_Line((eLineID::eLineID)i)
								->Get_LinkCells().emplace_back(LinkCell);
						}
					}
				}
			}
			else
			{
				m_vecCell[tTriggerCell.iCellIdx]->Set_CellType(eCellType::Connect);
				for (auto& LinkCell : tTriggerCell.vecLinkCells)
				{
					m_vecCell[tTriggerCell.iCellIdx]->Add_LinkCell(LinkCell);
				}
				
			}
	
		}
		m_vecLoadData.clear();
		m_vecLoadData.shrink_to_fit();
	}
	return S_OK;
}

void Engine::CNaviMesh::Render_Meshes()
{
	if (m_bHideCell)
		return;

	for (auto& iter : m_vecCell)
	{
		iter->Set_SelectNav(m_bSelect);
		iter->Render_Cell();
	}
}


eCompare::eCompare CNaviMesh::CompareCell(_int& iNavID, _int& iCellIdx, const  _vec3&	vEndPos, const _float& fRange)
{
	//직선 원충돌 할떄 필요한 값들 적용
	return m_vecCell[iCellIdx]->Compare(&vEndPos, iNavID, iCellIdx);
}

_vec3 CNaviMesh::MoveNaviMesh(_int & iNavID, _int & CellIdx, const _vec3 & vTargetPos, const _vec3 & vTargetDir, const _float & fRange)
{
	//  리브 값도 처리 할려면 오브젝트의 상태를 바꿔야하니깐 그냥 eCompare 내보내는것도 아니면 오브젝트 상태 컨트롤 하는 인자 받는 새로운 함수에서 이거 호출 해서 compare ㄹ명령에 따라  상태 변경 하는거롤 ? 
	// -> 반환값을 compare로 바꾸고 새로운 함수 만들어서 컨트롤 하는걸로 
	_vec3	vEndPos = vTargetPos + vTargetDir;
	_vec3   vOriPos = vTargetPos;

	eCompare::eCompare eOrder = CompareCell(iNavID, CellIdx, vEndPos, fRange);
	switch (eOrder)
	{
	case Engine::eCompare::Move:
		return vEndPos;
		break;
	case Engine::eCompare::Stop:
		return vOriPos;
		break;
	case Engine::eCompare::Leave:
		return vOriPos;
	}

	return _vec3();
}

void CNaviMesh::Set_BaseColor(const _vec3 & vColor)
{
	m_vBaseColor = vColor;
	for (auto& pCell : m_vecCell)
	{
		pCell->Set_BaseColor(vColor);
		if (pCell->Get_CellType() == eCellType::Base)
			pCell->Set_CellType(eCellType::Base);
	}
}

HRESULT Engine::CNaviMesh::Link_Cell()
{
	for (_ulong i = 0; i < m_vecCell.size(); ++i)
	{
		for (_ulong j = 0; j < m_vecCell.size(); ++j)
		{
			if (i == j)
				continue;

			if (nullptr == m_vecCell[i]->Get_Neighbor(eNeighbor::AB) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(eCellpt::A),
					m_vecCell[i]->Get_Point(eCellpt::B), m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::AB, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(eNeighbor::BC) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(eCellpt::B),
					m_vecCell[i]->Get_Point(eCellpt::C), m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::BC, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(eNeighbor::CA) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(eCellpt::C),
					m_vecCell[i]->Get_Point(eCellpt::A), m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::CA, m_vecCell[j]);
				continue;
			}
		}
	}

	return S_OK;
}

HRESULT CNaviMesh::Find_CurCellIdx(const _vec3 & vPos, _int& m_vMoveEndPos)
{
	for (auto& pCell : m_vecCell)
	{
		if (pCell->IsInside(vPos))
		{
			m_vMoveEndPos  = pCell->Get_CellIndex();
			return S_OK;
		}
	}

	return E_FAIL;
}

void CNaviMesh::OnNaviMesh(_vec3 & vPos, const _int& iCellidx)
{
	  
	D3DXPLANE	plane;
	D3DXPlaneFromPoints(
		&plane,
		m_vecCell[iCellidx]->Get_Point(eCellpt::A),
		m_vecCell[iCellidx]->Get_Point(eCellpt::B),
		m_vecCell[iCellidx]->Get_Point(eCellpt::C));


	if (0.f == plane.b)
		plane.b = 0.00000001f;

	vPos.y = -(plane.a * vPos.x + plane.c * vPos.z + plane.d) / plane.b;
}

void CNaviMesh::Modifying_Vertex(const _uint & iVtxIdx)
{
	for (auto& pCell : m_listRelation[iVtxIdx])
	{
		pCell->Modifying_Buffer();
	}
}

void CNaviMesh::Modifying_CellIdx(const _uint & iCellIdx)
{
	m_vecCell[iCellIdx]->Modifying_Buffer();
}

Engine::CNaviMesh* Engine::CNaviMesh::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath, const _bool& bToolMode)
{
	CNaviMesh*	pIns = new CNaviMesh(pDevice);

	if (FAILED(pIns->Ready_Meshes(pFilePath,bToolMode)))
		SafeRelease(pIns);

	pIns->Ready_NavigationMesh();
	return pIns;
}

CNaviMesh * CNaviMesh::Load(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath, const _bool& bToolMode, vector<CNaviMesh*>* pNaviMeshs)
{
	CNaviMesh*	pIns = new CNaviMesh(pDevice);

	if (FAILED(pIns->Load_Mesh(pFilePath,bToolMode)))
		SafeRelease(pIns);

	pIns->Ready_NavigationMesh(pNaviMeshs);
	return pIns;
}

void Engine::CNaviMesh::Free()
{
	for (auto& Cell : m_vecCell)
	{
		SafeRelease(Cell);
	}
	m_vecCell.clear();
	m_vecCell.shrink_to_fit();

	m_vecLoadData.clear();
	m_vecLoadData.shrink_to_fit();

	m_listRelation.clear();
	m_listRelation.shrink_to_fit();

	CComponent::Free();
}

HRESULT CNaviMesh::Ready_Component()
{
	return S_OK;
}

HRESULT CNaviMesh::Update_Component(const _float & fTimeDelta/* = 0.f*/)
{
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CNaviMesh::Ready_Meshes(const _tchar * pFilePath, const _bool& bToolMod)
{
	FILE* pFile = nullptr;
	if (0 != _tfopen_s(&pFile, pFilePath, TEXT("r")))
	{
		MSG_BOX(L"failed Load");
		return E_FAIL;
	}
	TCHAR szWord[MAX_PATH + 1] = TEXT("");
	CELLVTXIDX	tIndex;
	_vec3 pt = vZero;
	CCell*	pCell = nullptr;
	m_bToolMode = bToolMod;

	while (EOF != _ftscanf_s(pFile, TEXT("%s"), szWord, MAX_PATH))
	{
		if (0 == _tcscmp(TEXT("v"), szWord))
		{
			_ftscanf_s(pFile, TEXT("%f %f %f\n"), &pt.x, &pt.y, &pt.z);
			m_vecVTX.emplace_back(pt);
		}
		else if (0 == _tcscmp(TEXT("f"), szWord))
		{
			_ftscanf_s(pFile, TEXT("%d %d %d\n"), &tIndex._A, &tIndex._B, &tIndex._C);
			m_vecIndex.emplace_back(tIndex);
		}
	}
	fclose(pFile);
	return S_OK;
}

HRESULT CNaviMesh::Load_Mesh(const _tchar * pFilePath, const _bool& bToolMod)
{
	m_bLoad = true;
	m_bToolMode = bToolMod;

	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;
	DWORD dwByte;
	_uint iVtxCnt = 0;
	_uint iIdxCnt = 0;

	_vec3 vVtxPos;
	CELLVTXIDX vCellIdx;

	ReadFile(hFile, &m_iNaviID, sizeof(_int), &dwByte, nullptr); //ID
	ReadFile(hFile, &m_vBaseColor, sizeof(_vec3), &dwByte, nullptr); //COLOR

	ReadFile(hFile, &iVtxCnt, sizeof(_uint), &dwByte, nullptr); //iVtxsize
	for (_uint i = 0; i < iVtxCnt; ++i)
	{
		ReadFile(hFile, &vVtxPos, sizeof(_vec3), &dwByte, nullptr); // data
		m_vecVTX.emplace_back(vVtxPos);
	}
	ReadFile(hFile, &iIdxCnt, sizeof(_uint), &dwByte, nullptr); //iCellIdxsize
	for (_uint i = 0; i < iIdxCnt; ++i)
	{
		ReadFile(hFile, &vCellIdx, sizeof(CELLVTXIDX), &dwByte, nullptr); // data
		m_vecIndex.emplace_back(vCellIdx);
	}


	LOADDATA tCell;
	LINKCELL tLink;

	auto ResetLoadData = [](LOADDATA& tData) {
		for (_int i = 0; i < eLineID::End; ++i)
		{
			tData.vLine[i].vecLinkCells.clear();
			tData.vLine[i].vecLinkCells.shrink_to_fit();
		}
		tData.vecLinkCells.clear();
		tData.vecLinkCells.shrink_to_fit();
	};

	while (true)
	{
		ReadFile(hFile, &tCell.iCellIdx, sizeof(_uint), &dwByte, nullptr);
		if (dwByte == 0)
			break;
		ReadFile(hFile, &tCell.bOnLineTrigger, sizeof(_bool), &dwByte, nullptr);

		//line link
		if (tCell.bOnLineTrigger)
		{
			for (int i = 0; i < eLineID::End; ++i)
			{
				ReadFile(hFile, &tCell.vLine[i].iLineType, sizeof(_int), &dwByte, nullptr); // Linetype
				if (tCell.vLine[i].iLineType == eCellType::Connect)
				{
					//Link count
					_uint iLinkCnt = 0;
					ReadFile(hFile, &iLinkCnt, sizeof(_uint), &dwByte, nullptr); // NavId
					for (_uint j = 0; j < iLinkCnt; ++j)
					{
						ReadFile(hFile, &tLink.iNaviID, sizeof(_int), &dwByte, nullptr); // NavId
						ReadFile(hFile, &tLink.iCellIdx, sizeof(_int), &dwByte, nullptr); // CellIdx

						tCell.vLine[i].vecLinkCells.emplace_back(tLink);
					}
			
				}
			}
		}
		else //case cell
		{
			_uint iLinkCnt = 0;
			ReadFile(hFile, &iLinkCnt, sizeof(_uint), &dwByte, nullptr); // NavId
			for (_uint j = 0; j < iLinkCnt; ++j)
			{
				ReadFile(hFile, &tLink.iNaviID, sizeof(_int), &dwByte, nullptr); // NavId
				ReadFile(hFile, &tLink.iCellIdx, sizeof(_int), &dwByte, nullptr); // CellIdx

				tCell.vecLinkCells.emplace_back(tLink);
			}
		}

		m_vecLoadData.emplace_back(tCell);
		ResetLoadData(tCell);
	}

	CloseHandle(hFile);
	return S_OK;
}
