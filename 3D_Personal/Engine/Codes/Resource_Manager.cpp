#include "Resource_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResource_Manager)

CResource_Manager::CResource_Manager()
{
}


HRESULT CResource_Manager::Ready_Resourece(LPDIRECT3DDEVICE9 pDevice , const _tchar * pCompTag, 
	const eResourcesID::eResourcesID & eCompID, const CComponent * pComp)
{
	RESOURCEMAP::iterator Res_finditer;

	if (FAILED(overlapCheck_Comp(pCompTag, eCompID, Res_finditer)))
		return E_FAIL;



	return S_OK;
}

CComponent* CResource_Manager::Clone(const _tchar * pCompTag, const eResourcesID::eResourcesID & eResourceID)
{
	RESOURCEMAP::iterator Res_finditer;

	overlapCheck_Comp(pCompTag, eResourceID, Res_finditer);

	if (FAILED(FindCheck_Comp(Res_finditer, eResourceID)))
		return nullptr;

	CComponent* pClone = Res_finditer->second->Clone();

	return pClone;
}


HRESULT CResource_Manager::Ready_Meshes(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pMeshTag, eResourcesID::eResourcesID eType, const _tchar * pFilePath, const _tchar * pFileName)
{
	NULL_CHECK_RETURN(m_mapResouces, E_FAIL);
	
	RESOURCEMAP::iterator Res_finditer;

	if (FAILED(overlapCheck_Comp(pMeshTag, eType, Res_finditer)))
		return E_FAIL;

	CResources*	pResource = nullptr;

	switch (eType)
	{
	case Engine::eResourcesID::StaticMesh:
		pResource = CStaticMesh::Create(pGraphicDev, pFilePath, pFileName);
		break;
	case Engine::eResourcesID::DynamicMesh:
		pResource = CDynamicMesh::Create(pGraphicDev, pFilePath, pFileName);
		break;
	case Engine::eResourcesID::NaviMesh:
		pResource = CNaviMesh::Create(pGraphicDev);
		break;
	default:
		return E_FAIL;
	}
	NULL_CHECK_RETURN(pResource, E_FAIL);
	m_mapResouces[eType].emplace(pMeshTag, pResource);

	return S_OK;
}

//Áßº¹Ã¼Å© ¹Ø Å½»ö¿ë
HRESULT CResource_Manager::overlapCheck_Comp(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourceID, RESOURCEMAP::iterator& iter )
{
	iter = find_if(m_mapResouces[eResourceID].begin(), m_mapResouces[eResourceID].end(), CTagFinder(pCompTag));

	if (iter != m_mapResouces[eResourceID].end())
	{
		_tchar szBuff[128] = L"";
		swprintf_s(szBuff, L"Exisit %s Resource", pCompTag);
		MSG_BOX(szBuff);
		return E_FAIL;
	}

	return S_OK;
}

//Å½»ö Ã¼Å©
HRESULT CResource_Manager::FindCheck_Comp(RESOURCEMAP::iterator & iter, const eResourcesID::eResourcesID& eResourceID)
{
	if (iter == m_mapResouces[eResourceID].end())
		return E_FAIL;

	return S_OK;
}
void CResource_Manager::Free()
{
	for (_uint i = 0; i < eResourcesID::End; ++i)
	{
		for (auto& pair : m_mapResouces[i])
		{
			SafeRelease(pair.second);
		}
		m_mapResouces[i].clear();
	}
}
