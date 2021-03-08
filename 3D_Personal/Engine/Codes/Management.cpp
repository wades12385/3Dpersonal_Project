#include "Management.h"

USING(Engine)

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pGraphic_Dev(CGraphic_Device::Get_Instance())
	, m_pSceneManager(CScene_Manager::Get_Instance())
	, m_pGameObjectManager(CGameObject_Manager::Get_Instance())
	, m_pResource_Manager(CResource_Manager::Get_Instance())
	, m_pDataTable_Manager(CDatatable_Manager::Get_Instance())
	, m_bWaitChangeScene(false)
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

	/*update*/
	m_pSceneManager->Update_SceneMgr(fTimeDelta);
	m_pGameObjectManager->UpdateGameObject(m_pSceneManager->Get_SceneID(), fTimeDelta);

	/* LateUpdate */
	m_pSceneManager->LateUpdate_SceneMgr(fTimeDelta);
	m_pGameObjectManager->LateUpdateGameObject(m_pSceneManager->Get_SceneID(), fTimeDelta);

	return 0;
}

HRESULT CManagement::RenderEngine(HWND hWnd)
{
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);


	if (FAILED(m_pRenderer->Render(hWnd)))
	{
		MSG_BOX(L"Error Rendering");
		return E_FAIL;
	}

	m_pSceneManager->Render_Scene();

	//현재 씬을 랜더 까지 끝내고 릴리즈 
	if (m_bWaitChangeScene)
	{
		for (auto& iScneneID : m_listChangeSeneIdReservation)
		{
			m_pGameObjectManager->ClearForScene(iScneneID);
		}
		m_pSceneManager->Check_WaitChange();

		m_listChangeSeneIdReservation.clear();
		m_bWaitChangeScene = false;
	}
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
	//둘 이상의 예약이 들어올경우 중복 체크 
	if(m_listChangeSeneIdReservation.empty() == false)
	{
		auto& Find_iter = find( m_listChangeSeneIdReservation.begin() , m_listChangeSeneIdReservation.end() ,iSceneIndex);
		if (Find_iter == m_listChangeSeneIdReservation.end())
		{
			m_bWaitChangeScene = true;
			m_listChangeSeneIdReservation.emplace_back(iSceneIndex);
			return S_OK;
		}
		return E_FAIL;
	}
	m_listChangeSeneIdReservation.emplace_back(iSceneIndex);
	m_bWaitChangeScene = true;
	return S_OK;
}

LPDIRECT3DDEVICE9 CManagement::Get_Device()
{
	NULL_CHECK_RETURN(m_pGraphic_Dev, nullptr);

	return m_pGraphic_Dev->Get_Device();
}

HRESULT CManagement::SetUp_ChangeScene(_int iSceneID, CScene * pCurrentScene)
{
	NULL_CHECK_RETURN(m_pSceneManager, E_FAIL);

	FAILED_CHECK(m_pSceneManager->Set_CurrentScene(iSceneID, pCurrentScene));
	m_bWaitChangeScene = true;
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

CGameObject* CManagement::Ready_GameObject(const _tchar * ProtoTag, const _tchar * pLayerTag)
{
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager, nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

	return m_pGameObjectManager->Ready_GameObejct(nSceneID, pLayerTag, ProtoTag);
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
	NULL_CHECK_RETURN(m_pGameObjectManager, nullptr);
	NULL_CHECK_RETURN(m_pSceneManager,nullptr);

	_int nSceneID = NONE_SCENE;
	if (FAILED(m_pSceneManager->Get_SceneID(nSceneID)))
		return nullptr;

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

HRESULT CManagement::Ready_Resource(const _tchar * pCompTag, const eResourcesID::eResourcesID & eCompID, CResources * pComp)
{
	NULL_CHECK_RETURN(m_pResource_Manager, E_FAIL);


	return m_pResource_Manager->Ready_Resourece(m_pGraphic_Dev->Get_Device(), pCompTag, eCompID, pComp);
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

HRESULT CManagement::Load_DataTable(const _tchar * pFilePath)
{
	NULL_CHECK_RETURN(m_pDataTable_Manager, E_FAIL);

	return m_pDataTable_Manager->Load_DataTable(pFilePath);
}

HRESULT CManagement::Save_DataTable(const _tchar * pFilePath)
{
	return m_pDataTable_Manager->Save_DataTable(pFilePath);
}

vector<OBJDATA>* CManagement::Get_DataTableVector()
{
	return m_pDataTable_Manager->Get_DataTableVector();
}

void CManagement::Free()
{
	m_listChangeSeneIdReservation.clear();


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

	if(CDatatable_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to Release_Instance");
	if (CGameObject_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CGameObject_Manager");
	if (CResource_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CComponent_Manager");
	if (CScene_Manager::Release_Instance())
		MSG_BOX(L"Faild Release to CScene_Manager");
	if (CGraphic_Device::Release_Instance())
		MSG_BOX(L"Faild Release to CGraphic_Device");
}

