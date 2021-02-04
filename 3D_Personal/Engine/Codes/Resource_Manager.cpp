#include "Resource_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResource_Manager)

CResource_Manager::CResource_Manager()
{
}

void CResource_Manager::Free()
{
	for (_uint i = 0; i < (_uint)eResourcesID::End; ++i)
	{
		for (auto& pair : m_mapResouces[i])
		{
			SafeRelease(pair.second);
		}
		m_mapResouces[i].clear();
	}
}

HRESULT CResource_Manager::Ready_Resourece(LPDIRECT3DDEVICE9 pDevice , const _tchar * pCompTag, const eResourcesID & eCompID, const CComponent * pComp)
{
	if (FAILED(ExisitCheck_Comp(pCompTag, eCompID)))
		return E_FAIL;



	return S_OK;
}

CComponent* CResource_Manager::Clone(const _tchar * pCompTag, const eResourcesID & eResourceID)
{
	RESOURCEMAP::iterator Resourec_Finditer = find_if(m_mapResouces[(_uint)eResourceID].begin(), m_mapResouces[(_uint)eResourceID].end(), CTagFinder(pCompTag));

	if (FAILED(FindCheck_Comp(Resourec_Finditer, eResourceID)))
		return nullptr;

	CComponent* pClone = Resourec_Finditer->second->Clone();

	return pClone;
}

//중복체크 
HRESULT CResource_Manager::ExisitCheck_Comp(const _tchar* pCompTag, const eResourcesID& eResourceID, RESOURCEMAP::iterator& iter )
{
	auto& iter = find_if(m_mapResouces[(_uint)eResourceID].begin(), m_mapResouces[(_uint)eResourceID].end(), CTagFinder(pCompTag));

	if (iter != m_mapResouces[(_uint)eResourceID].end())
	{
		_tchar szBuff[128] = L"";
		swprintf_s(szBuff, L"Exisit %s Resource", pCompTag);
		MSG_BOX(szBuff);
		return E_FAIL;
	}

	return S_OK;
}

//탐색 체크
HRESULT CResource_Manager::FindCheck_Comp(RESOURCEMAP::iterator & iter, const eResourcesID& eResourceID)
{
	if (iter == m_mapResouces[(_uint)eResourceID].end())
		return E_FAIL;

	return S_OK;
}
