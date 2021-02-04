#include "Management.h"

USING(Engine)

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pGraphic_Dev(CGraphic_Device::Get_Instance())
	, m_pSceneManager(CScene_Manager::Get_Instance())
	, m_pGameObjectManager(CGameObject_Manager::Get_Instance())
	, m_pResource_Manager(CResource_Manager::Get_Instance())
{
	SafeAddRef(m_pGraphic_Dev);
	SafeAddRef(m_pSceneManager);
	SafeAddRef(m_pGameObjectManager);
	SafeAddRef(m_pResource_Manager);
}

HRESULT CManagement::ReadyEngine( HWND hWnd, 
	_uint iWinCX,  _uint iWinCY,  eWinMode eDisplaymode)
{
	if (FAILED(m_pGraphic_Dev->Ready_Graphic_Device(hWnd, iWinCX, iWinCY, eDisplaymode)))
		return E_FAIL;

	m_pRenderer = CRenderer::Create(m_pGraphic_Dev->Get_Device());

	NULL_CHECK_RETURN_MSG(m_pRenderer, E_FAIL, L"Failed To Create Renderer");

	return S_OK;
}

_uint CManagement::UpdateEngine(const _float& fTimeDelta)
{

	NULL_CHECK_RETURN(m_pSceneManager, 0);


	_int nSceneID = -1;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return 0;

	/*update*/
	m_pSceneManager->Update_SceneMgr(fTimeDelta);
	m_pGameObjectManager->UpdateGameObject(nSceneID, fTimeDelta);

	//  [2/3/2021 wades]
	//Update �� late ���� ���а��� �ѱ�� ���� �̰ɷ� ����ȯ �ٷ� ���� �� 

	/* LateUpdate */
	m_pSceneManager->LateUpdate_SceneMgr(fTimeDelta);
	m_pGameObjectManager->LateUpdateGameObject(nSceneID, fTimeDelta);

	return 0;
}

HRESULT CManagement::RenderEngine(HWND hWnd)
{
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);

	m_pGraphic_Dev->Render_Begine(D3DCOLOR_XRGB(0, 0, 255));

	if (FAILED(m_pRenderer->Render(hWnd)))
	{
		MSG_BOX(L"Error Rendering");
		return E_FAIL;
	}

	m_pGraphic_Dev->Render_End(hWnd);

	return S_OK;
}

HRESULT CManagement::ClearForScene(_int iSceneIndex)
{
	if (FAILED(m_pGameObjectManager->ClearForScene(iSceneIndex)))
		return E_FAIL;

	return S_OK;
}

LPDIRECT3DDEVICE9 CManagement::Get_Device()
{
	NULL_CHECK_RETURN(m_pGraphic_Dev, nullptr);

	return m_pGraphic_Dev->Get_Device();
}

HRESULT CManagement::SetUpCurrentScene(_int iSceneID, CScene * pCurrentScene)
{
	NULL_CHECK_RETURN(m_pSceneManager, E_FAIL);

	FAILED_CHECK(m_pSceneManager->Set_CurrentScene(iSceneID, pCurrentScene));
	m_pGameObjectManager->Ready_SceneLayer(iSceneID);

	//////////////////////////////////////////////////////////////////////////
	m_pSceneManager->Awake_SceneMgr();
	m_pGameObjectManager->Awake_GameObject(iSceneID);
	m_pSceneManager->Ready_SceneMgr();
	m_pGameObjectManager->Ready_GameObject(iSceneID);
	return S_OK;
}

_int CManagement::Get_SceneID()
{
	_int iSceneID = NONE_SCENE;

	if(FAILED(m_pSceneManager->Get_SceneID(iSceneID)))
		MSG_BOX(L"Current Scene is None");

	return iSceneID;
}

HRESULT CManagement::AddGameObjectPrototype(
	const _tchar* pProtoTag,
	CGameObject* pPrototype)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, E_FAIL);

	return m_pGameObjectManager->Add_ProtoType(pProtoTag, pPrototype);
}

//Call GameMgr
CGameObject* CManagement::AddGameObject(const size_t & nSceneID, const _tchar*  pLayerTag , const _tchar*  GameObjectTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);


	return m_pGameObjectManager->Add_GameObejct(nSceneID, pLayerTag, GameObjectTag);
}

//Call GameMgr

CGameObject* CManagement::AddGameObject(const _tchar * GameObjectTag, const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager, nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->Add_GameObejct(nSceneID, pLayerTag, GameObjectTag);
}

CComponent * CManagement::Clone_Componet()
{
	return nullptr;
}

//Call Renderer
HRESULT CManagement::AddRenderer(eRenderID eID, CGameObject* pGameObject)
{
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);

	return m_pRenderer->Add_Renderer(eID, pGameObject);
}

void CManagement::Free()
{
	SafeRelease(m_pRenderer);
	SafeRelease(m_pSceneManager);
	SafeRelease(m_pGameObjectManager);
	SafeRelease(m_pResource_Manager);
	SafeRelease(m_pGraphic_Dev);
}

void CManagement::ReleaseEngine()
{
	if (CManagement::Release_Instance())
		MSG_BOX(L"Faild Release to Management");

	if (CGameObject_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CGameObject_Manager");
	if (CResource_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CComponent_Manager");
	if (CScene_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CScene_Manager");
	if (CGraphic_Device::Release_Instance())
		MSG_BOX(L"Faild Release to CGraphic_Device");
}
