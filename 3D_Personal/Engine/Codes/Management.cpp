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
	//Update 랑 late 에서 실패값을 넘기고 있음 이걸로 씬전환 바로 들어가도 됨 

	/* LateUpdate */
	m_pSceneManager->LateUpdate_SceneMgr(fTimeDelta);
	m_pGameObjectManager->LateUpdateGameObject(nSceneID, fTimeDelta);

	return 0;
}

HRESULT CManagement::RenderEngine(HWND hWnd)
{
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);

	//m_pGraphic_Dev->Render_Begine(D3DCOLOR_XRGB(46, 116, 50));

	if (FAILED(m_pRenderer->Render(hWnd)))
	{
		MSG_BOX(L"Error Rendering");
		return E_FAIL;
	}

	//m_pGraphic_Dev->Render_End(hWnd);

	return S_OK;
}

void CManagement::BegineRender()
{
	m_pGraphic_Dev->Render_Begine(D3DCOLOR_XRGB(46, 116, 50));

}

void CManagement::EndRender(HWND hWnd)
{
	m_pGraphic_Dev->Render_End(hWnd);
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

HRESULT CManagement::SceneInitLog_Reserve(const _int & iSceneCnt)
{
	NULL_CHECK_RETURN(m_pSceneManager, E_FAIL);


	return m_pSceneManager->Scene_InitLogReserve(iSceneCnt);
}

HRESULT CManagement::Ready_GameObjectPrototype(
	const _tchar* pProtoTag,
	CGameObject* pPrototype)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, E_FAIL);

	return m_pGameObjectManager->Ready_ProtoType(pProtoTag, pPrototype);
}

CGameObject* CManagement::Ready_GameObject(const size_t & nSceneID, const _tchar*  pLayerTag , const _tchar*  GameObjectTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);


	return m_pGameObjectManager->Ready_GameObejct(nSceneID, pLayerTag, GameObjectTag);
}

CGameObject* CManagement::Ready_GameObject(const _tchar * GameObjectTag, const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager, nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->Ready_GameObejct(nSceneID, pLayerTag, GameObjectTag);
}

CGameObject * CManagement::LateReady_GameObject(const _tchar * GameObjectTag, const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager, nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->LateReady_GameObejct(nSceneID, pLayerTag, GameObjectTag);
}



void  CManagement::Add_InstantGameObject(CGameObject * pGameObj,const _tchar * pLayerTag)
{
	NULL_CHECK(m_pGameObjectManager);
	NULL_CHECK(m_pSceneManager);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return;

	return m_pGameObjectManager->Add_InstanceGameObject(nSceneID, pGameObj, pLayerTag);
}

CGameObject* CManagement::Add_InstantGameObject(const _tchar * pProtoTag, const _tchar * pLayerTag)
{
	NULL_CHECK(m_pGameObjectManager);
	NULL_CHECK(m_pSceneManager);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return;

	return m_pGameObjectManager->Add_InstanceGameObject(nSceneID, pProtoTag, pLayerTag);
}

CGameObject * CManagement::Get_GameObjet(const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, NULL);
	NULL_CHECK_RETURN(m_pSceneManager, NULL);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->Get_GameObject(nSceneID, pLayerTag);
}

list<CGameObject*>* CManagement::Get_GameObjetList(const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager, nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->Get_Layer(nSceneID, pLayerTag);
}

HRESULT CManagement::Ready_Mesh(const _tchar * pMeshTag, eResourcesID::eResourcesID eType, const _tchar * pFilePath, const _tchar * pFileName)
{
	NULL_CHECK_RETURN(m_pResource_Manager, E_FAIL);


	return m_pResource_Manager->Ready_Mesh(m_pGraphic_Dev->Get_Device(), pMeshTag, eType, pFilePath, pFileName);
}

HRESULT CManagement::Load_NavMesh(const _tchar * pMeshTag, const _tchar * pFilePath)
{
	NULL_CHECK_RETURN(m_pResource_Manager, E_FAIL);

	return m_pResource_Manager->Load_Mesh(m_pGraphic_Dev->Get_Device(), pMeshTag, pFilePath);
}

HRESULT CManagement::Ready_Texture(const _tchar * pResouceTag, const _tchar * pFilePath, const _uint & iCnt)
{
	NULL_CHECK_RETURN(m_pResource_Manager, E_FAIL);

	return m_pResource_Manager->Ready_Texture(m_pGraphic_Dev->Get_Device(), pResouceTag, pFilePath, iCnt);;
}

CComponent * CManagement::Clone_Resource(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourcesID)
{
	NULL_CHECK_RETURN(m_pResource_Manager, nullptr);

	return m_pResource_Manager->Clone(pCompTag, eResourcesID);
}

//Call Renderer
HRESULT CManagement::Add_Renderer(eRenderID eID, CGameObject* pGameObject)
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

