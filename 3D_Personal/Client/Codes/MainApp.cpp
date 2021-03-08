#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"

CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
	,m_iFPS(0)
	,m_fTime(0)

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

	m_pManagement->SceneInitLog_Reserve(eSceneID::End);
	FAILED_CHECK(Engine::Ready_Font(m_pManagement->Get_Device(), L"Font_Default", L"±Ã¼­", 10, 25, FW_HEAVY));

	/* Á¶¸í off */
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (FAILED(m_pManagement->SetUp_ChangeScene((_uint)eSceneID::Logo, CLogo::Create(m_pDevice))))
	{
		return E_FAIL;
	}


	ZeroMemory(m_szFPS, sizeof(_tchar) * 64);

	return S_OK;
}

void CMainApp::Running(const _float & fTimeDelta)
{
	ShowFPS(fTimeDelta);
	Engine::Update_InputDev();
	m_pManagement->UpdateEngine(fTimeDelta);

	m_pManagement->BegineRender();
	m_pManagement->RenderEngine(g_hWnd);
	m_pManagement->EndRender(g_hWnd);

}


HRESULT CMainApp::ReadyStaticResources()
{
	return S_OK;
}

void CMainApp::ShowFPS(const _float & fTimeDelta)
{
	++m_iFPS;
	m_fTime += fTimeDelta;
	if (m_fTime >= 1.f)
	{
		wsprintf(m_szFPS, L"FPS: %d", m_iFPS);
		m_fTime = 0.f;
		m_iFPS = 0;
	}
	SetWindowText(g_hWnd, m_szFPS);
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
	CNaviMesh_Manager::Release_Instance();

	SafeRelease(m_pManagement);
	SafeRelease(m_pDevice);
	CManagement::Get_Instance()->ReleaseEngine();
}
