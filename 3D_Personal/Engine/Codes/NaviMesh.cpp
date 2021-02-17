#include "NaviMesh.h"


USING(Engine)

CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 pDevice)
	:CMesh(pDevice)
	, m_iCurIndex(0)
	, m_bHideCell(false)
	, m_bSelect(false)
	, m_bLoad(false)
{
}

CNaviMesh::CNaviMesh(const CNaviMesh& other)
	: CMesh(other)
	, m_iCurIndex(other.m_iCurIndex)
	, m_vecCell(other.m_vecCell)
	, m_vecVTX(other.m_vecVTX)
	, m_vecIndex(other.m_vecIndex)
	, m_bSelect(false)
	, m_bLoad(other.m_bLoad)
	, m_vecLoadData(other.m_vecLoadData)
{
	for (auto& iter : m_vecCell)
		iter->AddRef();
}


HRESULT Engine::CNaviMesh::Ready_NavigationMesh()
{
	m_listRelation.resize(m_vecVTX.size(), list<CCell*>());

	for (size_t i = 0; i < m_vecIndex.size(); ++i)
	{
		auto pCell = CCell::Create(m_pDevice, i , m_vecIndex[i], &m_vecVTX);
		NULL_CHECK_RETURN(pCell, E_FAIL);
		m_vecCell.push_back(pCell);

		m_listRelation[m_vecIndex[i]._A - 1].emplace_back(pCell);
		m_listRelation[m_vecIndex[i]._B - 1].emplace_back(pCell);
		m_listRelation[m_vecIndex[i]._C - 1].emplace_back(pCell);
	}

	FAILED_CHECK(Link_Cell());

	if (m_bLoad)
	{
		for (auto& tData : m_vecLoadData)
		{
			m_vecCell[tData.iCellIdx]->Set_CellType((eCellType::eCellType)tData.iCellType);

			for (size_t i = 0; i < tData.vLine.size(); ++i)
			{
				m_vecCell[tData.iCellIdx]->Get_Line((eLineID::eLineID)i)->
					Set_Type((eCellType::eCellType)tData.vLine[i].iLineType);
			}
		}
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


_vec3 Engine::CNaviMesh::Move_OnNaviMesh(const _vec3* pTargetPos, const _vec3* pTargetDir)
{
	_vec3	vEndPos = *pTargetPos + *pTargetDir;

	if (eCompare::Move == m_vecCell[m_iCurIndex]->Compare(&vEndPos, &m_iCurIndex))
		return vEndPos;

	else if (eCompare::Stop == m_vecCell[m_iCurIndex]->Compare(&vEndPos, &m_iCurIndex))
		return *pTargetPos;

	return *pTargetPos;
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

Engine::CNaviMesh* Engine::CNaviMesh::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath)
{
	CNaviMesh*	pIns = new CNaviMesh(pDevice);

	if (FAILED(pIns->Ready_Meshes(pFilePath,NULL)))
		SafeRelease(pIns);

	return pIns;
}

CNaviMesh * CNaviMesh::Load(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath)
{
	CNaviMesh*	pIns = new CNaviMesh(pDevice);

	if (FAILED(pIns->Load_Mesh(pFilePath)))
		SafeRelease(pIns);

	return pIns;
}

CComponent * CNaviMesh::Clone()
{
	CNaviMesh*	pIns = new CNaviMesh(*this);

	if (FAILED(pIns->Ready_NavigationMesh()))
		SafeRelease(pIns);

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

	CMesh::Free();
}

//////////////////////////////////////////////////////////////////////////
HRESULT CNaviMesh::Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName)
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

HRESULT CNaviMesh::Load_Mesh(const _tchar * pFilePath)
{
	m_bLoad = true;
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;
	DWORD dwByte;
	_uint iVtxCnt = 0;
	_uint iIdxCnt = 0;

	_vec3 vVtxPos;
	CELLVTXIDX vCellIdx;

	ReadFile(hFile, &iVtxCnt, sizeof(_uint), &dwByte, nullptr); //iVtxCnt
	for (_uint i = 0; i < iVtxCnt; ++i)
	{
		ReadFile(hFile, &vVtxPos, sizeof(_vec3), &dwByte, nullptr);
		m_vecVTX.emplace_back(vVtxPos);
	}
	ReadFile(hFile, &iIdxCnt, sizeof(_uint), &dwByte, nullptr); //iCellIdxCnt
	for (_uint i = 0; i < iIdxCnt; ++i)
	{
		ReadFile(hFile, &vCellIdx, sizeof(CELLVTXIDX), &dwByte, nullptr);
		m_vecIndex.emplace_back(vCellIdx);
	}


	LINEDATA Line;
	LOADDATA data;
	while (true)
	{
		ReadFile(hFile, &data.iCellIdx, sizeof(_uint), &dwByte, nullptr);
		if (dwByte == 0)
			break;
		ReadFile(hFile, &data.iCellType, sizeof(_uint), &dwByte, nullptr);
		for (int i = 0; i < eLineID::End; ++i)
		{
			ReadFile(hFile, &Line.iLineType, sizeof(_uint), &dwByte, nullptr); // Linetype
			// IF 추가해서 추가로 저장
			data.vLine.emplace_back(Line);
		}
		m_vecLoadData.emplace_back(data);
	}

	CloseHandle(hFile);

	return S_OK;
}
