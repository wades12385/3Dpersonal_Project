#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"

CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
{
	m_pManagement->AddRef();
}

HRESULT CMainApp::ReadyMainApp()
{
	if (FAILED( m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY, eWinMode::Window)))
	{
		MSG_BOX(L"Failed To ReadyEngine");
		return E_FAIL;
	}

	m_pDevice = m_pManagement->Get_Device();
	SafeAddRef(m_pDevice);
	/* Α¶Έν off */
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (FAILED(m_pManagement->SetUpCurrentScene((_uint)eSceneID::Logo, CLogo::Create(m_pDevice))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CMainApp::Running(const _float & fTimeDelta)
{

	m_pManagement->UpdateEngine(fTimeDelta);

	m_pManagement->RenderEngine(g_hWnd);

	return ;
}


HRESULT CMainApp::ReadyStaticResources()
{
	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		MSG_BOX(L"Failed To Create CMainApp");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	SafeRelease(m_pManagement);
	SafeRelease(m_pDevice);
	CManagement::Get_Instance()->ReleaseEngine();
}
