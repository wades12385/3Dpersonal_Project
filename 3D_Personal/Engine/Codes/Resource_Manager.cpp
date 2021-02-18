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

HRESULT CResource_Manager::Ready_Texture(LPDIRECT3DDEVICE9 pDevice, const _tchar * pTextureTag, const _tchar * pPath, const _uint & iCnt)
{
	RESOURCEMAP::iterator Res_finditer;

	if (FAILED(overlapCheck_Comp(pTextureTag, eResourcesID::Texture, Res_finditer)))
		return E_FAIL;

	CResources*	pResources = CTexture::Create(pDevice, pPath, iCnt);
	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_mapResouces[eResourcesID::Texture].emplace(pTextureTag, pResources);
	return S_OK;
}


HRESULT CResource_Manager::Ready_Mesh(LPDIRECT3DDEVICE9 pDevice, const _tchar * pMeshTag, eResourcesID::eResourcesID eType,
	const _tchar * pFilePath, const _tchar * pFileName)
{
	NULL_CHECK_RETURN(m_mapResouces, E_FAIL);
	
	RESOURCEMAP::iterator Res_finditer;

	if (FAILED(overlapCheck_Comp(pMeshTag, eType, Res_finditer)))
		return E_FAIL;

	CResources*	pResource = nullptr;

	switch (eType)
	{
	case Engine::eResourcesID::StaticMesh:
		pResource = CStaticMesh::Create(pDevice, pFilePath, pFileName);
		break;
	case Engine::eResourcesID::DynamicMesh:
		pResource = CDynamicMesh::Create(pDevice, pFilePath, pFileName);
		break;
	case Engine::eResourcesID::NaviMesh:
		pResource = CNaviMesh::Create(pDevice,pFilePath);
		break;
	default:
		return E_FAIL;
	}
	NULL_CHECK_RETURN(pResource, E_FAIL);
	m_mapResouces[eType].emplace(pMeshTag, pResource);

	return S_OK;
}

HRESULT CResource_Manager::Load_Mesh(LPDIRECT3DDEVICE9 pDevice, const _tchar * pMeshTag, const _tchar * pFilePath)
{
	NULL_CHECK_RETURN(m_mapResouces, E_FAIL);

	RESOURCEMAP::iterator Res_finditer;

	if (FAILED(overlapCheck_Comp(pMeshTag, eResourcesID::NaviMesh, Res_finditer)))
		return E_FAIL;

	CResources*	pResource = nullptr;
	pResource = CNaviMesh::Load(pDevice, pFilePath);
	NULL_CHECK_RETURN(pResource, E_FAIL);
	m_mapResouces[eResourcesID::NaviMesh].emplace(pMeshTag, pResource);

	return S_OK;
}

//Áßº¹Ã¼Å© ¹Ø Å½»ö¿ë
HRESULT CResource_Manager::overlapCheck_Comp(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourceID, RESOURCEMAP::iterator& iter )
{
	iter = find_if(m_mapResouces[eResourceID].begin(), m_mapResouces[eResourceID].end(), CTagFinder(pCompTag));

	if (iter != m_mapResouces[eResourceID].end())
	{
	
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
