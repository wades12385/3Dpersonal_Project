#include "stdafx.h"
#include "Logo.h"
#include "Loading.h"
#include "TestScene.h"
#include "LogoImg.h"


CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
	, m_pLoading(nullptr)
{
}

HRESULT CLogo::Initialize_Scene()
{
	CManagement::Get_Instance()->Ready_Texture(L"LogoImg", L"../../Resources/Texture/Logo.jpg", 1); //Logoimg 
	CRectBuffer* pRect = CRectBuffer::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_Resource(L"Rect_Buffer", eResourcesID::RectBuffer, pRect);// Rect³Ö¾î³ù°í 
	
	//Loading
	m_pLoading = CLoading::Create(m_pDevice,eLoadID::Test);

	///
	//CManagement::Get_Instance()->Ready_Mesh(L"Core_1", eResourcesID::StaticMesh,
	//	L"../../Resources/Mesh/Static/Player/Core/Core_1/", L"Core_1.X");

	//CManagement::Get_Instance()->Ready_Mesh(L"StaticMesh_Stage1",
	//	eResourcesID::StaticMesh, L"../../Resources/Mesh/Static/Stage/Test/", L"Stage1.X");
	///

	//logoimg proto
	CGameObject* pObj = CLogoImg::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_LogoImg", pObj);
	return S_OK;
}

HRESULT CLogo::ReInitialize_Scene()
{

	return S_OK;
}

HRESULT CLogo::Awake_Scene()
{
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_LogoImg", L"Layer_Image");


	return S_OK;
}

HRESULT CLogo::Ready_Scene()
{

	return S_OK;
}

_uint CLogo::Update_Scene(const _float& fTimeDeleta)
{

	if (m_pLoading->Get_Finish())
	{

		if (KeyDown(DIK_RETURN))
		{
			Engine::CScene*		pScene = nullptr;
			pScene = CTestScene::Create(m_pDevice);
			NULL_CHECK_RETURN(pScene, -1);
			CManagement::Get_Instance()->SetUp_ChangeScene(eSceneID::Test, pScene);
			CManagement::Get_Instance()->ClearForScene(eSceneID::Logo);
			return 0;
		}
	}

	return 0;
}

_uint CLogo::LateUpdate_Scene(const _float& fTimeDeleta)
{


	return 0;
}

void CLogo::Render_Scene()
{
	Render_Font(L"Font_Default", m_pLoading->Get_String(), &_vec2(10.f, 10.f),D3DCOLOR_XRGB(255,0,0));
	return;
}

void CLogo::Free()
{
	SafeRelease(m_pLoading);
	CScene::Free();
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CLogo(pDevice);;
}

