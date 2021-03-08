#include "stdafx.h"
#include "NaviMesh_Manager.h"
#include "Management.h"

IMPLEMENT_SINGLETON(CNaviMesh_Manager)

CNaviMesh_Manager::CNaviMesh_Manager()
{
}


CNaviMesh_Manager::~CNaviMesh_Manager()
{
}

HRESULT CNaviMesh_Manager::Load(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath)
{
	CNaviMesh* pMesh = CNaviMesh::Load(pDevice, pFilePath,false,&m_vecNaviMesh);
	NULL_CHECK_RETURN(pMesh,E_FAIL);
	m_vecNaviMesh.emplace_back(pMesh);
	return S_OK;
}

void CNaviMesh_Manager::ClearMesh()
{
	for (auto& pMesh : m_vecNaviMesh)
	{
		SafeRelease(pMesh);
	}
	m_vecNaviMesh.clear();
	m_vecNaviMesh.shrink_to_fit();
}

vector<CNaviMesh*>& CNaviMesh_Manager::Get_Mesh()
{
	if (m_vecNaviMesh.empty())
	{
		MSG_BOX(L"no exist navMesh");
	}

	 return m_vecNaviMesh;
}

HRESULT CNaviMesh_Manager::Lading_Navi(_vec3& vPos,  const _int& iNavID, const _int& iCellIdx)
{
	if (0 > iNavID || (_uint)iNavID >= m_vecNaviMesh.size())
	{
		MSG_BOX(L"out Range Vector");
		return E_FAIL;
	}

	m_vecNaviMesh[iNavID]->OnNaviMesh(vPos,iCellIdx);

	return S_OK;
}

void CNaviMesh_Manager::Render_Navi()
{
	_matrix matwolrd; 
	D3DXMatrixIdentity(&matwolrd);
	CManagement::Get_Instance()->Get_Device()->SetTransform(D3DTS_WORLD, &matwolrd);

	for (auto& pNavi : m_vecNaviMesh)
	{
		pNavi->Render_Meshes();
	}
}

void CNaviMesh_Manager::Free()
{
	ClearMesh();
}
