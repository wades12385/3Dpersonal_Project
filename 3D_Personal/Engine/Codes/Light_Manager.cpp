#include "Light_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CLight_Manager)

CLight_Manager::CLight_Manager()
{
}

HRESULT CLight_Manager::Add_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9 * pLightInfo, const _uint & iIndex)
{
	CLight*	pLight = CLight::Create(pGraphicDev, pLightInfo, iIndex);
	NULL_CHECK_RETURN(pLight, E_FAIL);

	m_LightList.push_back(pLight);

	return S_OK;
}

void CLight_Manager::Free()
{
	for (auto& pLight : m_LightList)
	{
		SafeRelease(pLight);
	}
	m_LightList.clear();
}

