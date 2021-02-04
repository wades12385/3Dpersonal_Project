#include "NaviMesh.h"


USING(Engine)

CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 pDevice)
	:CMesh(pDevice)
	, m_dwIndex(0)
{
}

CNaviMesh::CNaviMesh(const CNaviMesh& rhs)
	: CMesh(rhs)
	, m_dwIndex(rhs.m_dwIndex)
	, m_vecCell(rhs.m_vecCell)
{
	for (auto& iter : m_vecCell)
		iter->AddRef();
}


HRESULT Engine::CNaviMesh::Ready_NavigationMesh()
{

	CCell*	pCell = nullptr;
	//m_vecCell.reserve(4);

	//// 0번
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 2.f), &_vec3(2.f, 0.f, 0.f), &_vec3(0.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 1번
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 2.f), &_vec3(2.f, 0.f, 2.f), &_vec3(2.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 2번
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(0.f, 0.f, 4.f), &_vec3(2.f, 0.f, 2.f), &_vec3(0.f, 0.f, 2.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//// 3번
	//pCell = CCell::Create(m_pGraphicDev, m_vecCell.size(), &_vec3(2.f, 0.f, 2.f), &_vec3(4.f, 0.f, 0.f), &_vec3(2.f, 0.f, 0.f));
	//NULL_CHECK_RETURN(pCell, E_FAIL);
	//m_vecCell.push_back(pCell);

	//FAILED_CHECK_RETURN(Link_Cell(), E_FAIL);

	return S_OK;
}

void Engine::CNaviMesh::Render_Meshes()
{
	for (auto& iter : m_vecCell)
		iter->Render_Cell();
}


_vec3 Engine::CNaviMesh::Move_OnNaviMesh(const _vec3* pTargetPos, const _vec3* pTargetDir)
{
	_vec3	vEndPos = *pTargetPos + *pTargetDir;

	if (eCompare::Move == m_vecCell[m_dwIndex]->Compare(&vEndPos, &m_dwIndex))
		return vEndPos;

	else if (eCompare::Stop == m_vecCell[m_dwIndex]->Compare(&vEndPos, &m_dwIndex))
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
					m_vecCell[i]->Get_Point(eCellpt::B),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::AB, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(eNeighbor::BC) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(eCellpt::B),
					m_vecCell[i]->Get_Point(eCellpt::C),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::BC, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(eNeighbor::CA) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(eCellpt::C),
					m_vecCell[i]->Get_Point(eCellpt::A),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(eNeighbor::CA, m_vecCell[j]);
				continue;
			}
		}
	}

	return S_OK;
}

Engine::CNaviMesh* Engine::CNaviMesh::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNaviMesh*	pIns = new CNaviMesh(pGraphicDev);

	if (FAILED(pIns->Ready_NavigationMesh()))
		SafeRelease(pIns);

	return pIns;
}

CComponent * CNaviMesh::Clone()
{
	return new CNaviMesh(*this);
}

void Engine::CNaviMesh::Free()
{
	for_each(m_vecCell.begin(), m_vecCell.end(), CDeleteObj());
	m_vecCell.clear();

	CMesh::Free();
}

//////////////////////////////////////////////////////////////////////////
HRESULT CNaviMesh::Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName)
{
	return E_NOTIMPL;
}
