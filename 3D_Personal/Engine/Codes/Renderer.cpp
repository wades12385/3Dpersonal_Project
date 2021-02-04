#include "Renderer.h"
#include "GameObject.h"

USING(Engine)


CRenderer::CRenderer(const LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(m_pDevice);
}

HRESULT CRenderer::Add_Renderer(eRenderID eID,  CGameObject* pGameObject)
{
	if (0 > (_int)eID || eRenderID::End <= eID)
	{
		MSG_BOX(L"Out of range Render list");
		return E_FAIL;
	}

	if (nullptr == pGameObject)
		return E_FAIL;

	m_GameObjects[(_int)eID].emplace_back(pGameObject);
	SafeAddRef(pGameObject);
	return S_OK;
}

HRESULT CRenderer::Render(HWND hWnd)
{
	if (FAILED(RenderPriority()))
		return E_FAIL;

	if (FAILED(RenderNoAlpha()))
		return E_FAIL;

	if (FAILED(RenderAlpha()))
		return E_FAIL;

	if (FAILED(RenderUI()))
		return E_FAIL;


	return S_OK;
}

HRESULT CRenderer::RenderPriority()
{
	for (auto& pObject : m_GameObjects[(_int)eRenderID::Priority])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_int)eRenderID::Priority].clear();

	return S_OK;
}

HRESULT CRenderer::RenderNoAlpha()
{
	for (auto& pObject : m_GameObjects[(_int)eRenderID::NoAlpha])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;
		SafeRelease(pObject);

	}

	m_GameObjects[(_int)eRenderID::NoAlpha].clear();

	return S_OK;
}

HRESULT CRenderer::RenderAlpha()
{
	for (auto& pObject : m_GameObjects[(_int)eRenderID::Alpha])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;
		SafeRelease(pObject);

	}

	m_GameObjects[(_int)eRenderID::Alpha].clear();

	return S_OK;
}

HRESULT CRenderer::RenderUI()
{
	for (auto& pObject : m_GameObjects[(_int)eRenderID::UI])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;
		SafeRelease(pObject);

	}

	m_GameObjects[(_int)eRenderID::UI].clear();

	return S_OK;
}

CRenderer * CRenderer::Create(const LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	return new CRenderer(pDevice);
}

void CRenderer::Free()
{
	//shared list이니 그냥 클리어 
	for (_int i = 0; i < (_int)eRenderID::End; ++i)
	{
		for (auto& pObj : m_GameObjects[i])
		{
			SafeRelease(pObj);
		}
		m_GameObjects[i].clear();
	}

	SafeRelease(m_pDevice);
}
