#include "stdafx.h"
#include "DirectApp.h"
#include "NaviModifyScene.h"
#include "ToolCamera.h"

IMPLEMENT_SINGLETON(CDirectApp)

CDirectApp::CDirectApp()
	:m_iFPS(0)
	,m_fTime(0.f)
{
}


HRESULT CDirectApp::ReadyEngine(HWND hWnd)
{
	FAILED_CHECK(Engine::Ready_Timer(L"Loop_Timer"));
	FAILED_CHECK(Engine::Ready_Timer(L"FPS60"));
	FAILED_CHECK(Engine::Ready_Frame(L"Frame60", 60.f));
	FAILED_CHECK(Engine::Ready_DXInput(::AfxGetInstanceHandle(), g_hWnd));

	g_hWnd = hWnd;
	m_pManagement = CManagement::Get_Instance();
	m_pManagement->AddRef();

	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY, eWinMode::Window)))
	{
		MSG_BOX(L"Failed To ReadyEngine");
		return E_FAIL;
	}

	ZeroMemory(m_szFPS, sizeof(_tchar) * 16);
	FAILED_CHECK(Engine::Ready_Font(m_pManagement->Get_Device(), L"Font_Default", L"궁서", 10, 15, FW_HEAVY));

	Ready_ProtoType();


	if (FAILED(m_pManagement->SetUpCurrentScene(eToolScene::NaviModify, 
		CNaviModifyScene::Create(CManagement::Get_Instance()->Get_Device()))))
		return E_FAIL;

	return S_OK;
}

void CDirectApp::Running(_float & fTimeDelta)
{
	Engine::Update_InputDev();
	m_pManagement->UpdateEngine(fTimeDelta);

	m_pManagement->BegineRender();
	m_pManagement->RenderEngine(g_hWnd);
	ShowFPS(fTimeDelta);
	m_pManagement->EndRender(g_hWnd);

}

void CDirectApp::ShowFPS(_float & fTimeDelta)
{
	++m_iFPS;
	m_fTime += fTimeDelta;
	if (m_fTime >= 1.f)
	{
		wsprintf(m_szFPS, L"%d", m_iFPS);
		m_fTime = 0.f;
		m_iFPS = 0;
	}
	Engine::Render_Font(L"Font_Default", m_szFPS, &_vec2(10.f,10.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void CDirectApp::Free()
{
	Engine::Release_Engine(); 
	SafeRelease(m_pManagement);
	CManagement::Get_Instance()->ReleaseEngine();
}

void CDirectApp::Ready_ProtoType()
{
	//카메라 프로토 생성
	CGameObject* pObj = CToolCamera::Create(m_pManagement->Get_Device());
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Camera",pObj);
}
