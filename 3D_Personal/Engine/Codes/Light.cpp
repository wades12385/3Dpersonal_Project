#include "Light.h"

USING(Engine)

CLight::CLight(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_iIndex(0)
{
	ZeroMemory(&m_tLightInfo, sizeof(D3DLIGHT9));
	m_pDevice->AddRef();
}

HRESULT CLight::Ready_Light(const D3DLIGHT9* pLightInfo, const _uint & iIndex)
{
	memcpy(&m_tLightInfo, pLightInfo, sizeof(D3DLIGHT9));

	m_iIndex = iIndex;

	m_pDevice->SetLight(iIndex, pLightInfo);
	m_pDevice->LightEnable(iIndex, TRUE);

	return S_OK;
}

CLight * CLight::Create(LPDIRECT3DDEVICE9 pDevice, const D3DLIGHT9 * pLightInfo, const _uint & iIndex)
{
	CLight*	pIns = new CLight(pDevice);

	if (FAILED(pIns->Ready_Light(pLightInfo, iIndex)))
		SafeRelease(pIns);

	return pIns;
}

void CLight::Free()
{
	m_pDevice->LightEnable(m_iIndex, FALSE);
	SafeRelease(m_pDevice);
}
