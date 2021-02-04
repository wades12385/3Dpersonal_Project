#include "GameObject_Manager.h"
#include "Engine_Function.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGameObject_Manager)

CGameObject_Manager::CGameObject_Manager()
{
}

HRESULT CGameObject_Manager::Awake_GameObject(const _int & iScene)
{
	auto Scene_find = m_mapObjManager.find(iScene);

	if (Scene_find == m_mapObjManager.end())
	{
		MSG_BOX(L"not exisit SceneID");
		return E_FAIL;
	}

	return 	Scene_find->second->Awake_Layer();
}

HRESULT CGameObject_Manager::Ready_GameObject(const _int & iScene)
{
	auto Scene_find = m_mapObjManager.find(iScene);

	if (Scene_find == m_mapObjManager.end())
	{
		MSG_BOX(L"not exisit SceneID");
		return E_FAIL;
	}

	return 	Scene_find->second->Ready_Layer();
}

_uint CGameObject_Manager::UpdateGameObject(const _int& iScene, const _float& fDeltaTime)
{

	auto Scene_find = m_mapObjManager.find(iScene);

	if (Scene_find == m_mapObjManager.end())
	{
		MSG_BOX(L"not exisit SceneID");
		return RETURN_FAILED;
	}

	return 	Scene_find->second->Update_Layer(fDeltaTime);
}

_uint CGameObject_Manager::LateUpdateGameObject(const _int& iScene, const _float& fDeltaTime)
{
	if (m_mapObjManager.empty())
		return 0;
	
	auto Scene_find = m_mapObjManager.find(iScene);

	if (Scene_find == m_mapObjManager.end())
	{
		MSG_BOX(L"not exisit SceneID");
		return RETURN_FAILED;
	}

	return Scene_find->second->LateUpdate_Layer(fDeltaTime);
}


HRESULT CGameObject_Manager::Ready_SceneLayer(const _int & iScene)
{
	auto GameObj_finditer = m_mapObjManager.find(iScene);

	if (FAILED(FindCheck_Obj(GameObj_finditer)))
	{
		m_mapObjManager.emplace(iScene, CLayer::Create());
	}

	return S_OK;
}

HRESULT CGameObject_Manager::Add_ProtoType(const _tchar * pProtoTag,  CGameObject*  pPrototype)
{
	auto ProtoType_iterfind = find_if(m_mapPrototypes.begin(), m_mapPrototypes.end(), CTagFinder(pProtoTag));

	if (m_mapPrototypes.end() != ProtoType_iterfind)
	{
		TCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Exisit %s Prototype", pProtoTag);
		MSG_BOX(szBuffer);
		return E_FAIL;
	}

	m_mapPrototypes.emplace(pProtoTag, pPrototype);

	return S_OK;
}



CGameObject* CGameObject_Manager::Add_GameObejct(const _int & iScene,
	const _tchar* pLayerTag, const _tchar* GameObjectTag)
{
	//find Prototype
	auto Proto_Iterfind = find_if(m_mapPrototypes.begin(), m_mapPrototypes.end(), CTagFinder(GameObjectTag));
	if (FAILED(FindCheck_Proto(Proto_Iterfind)))
	{
		TCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Prototype", GameObjectTag);
		MSG_BOX(szBuffer);
		return nullptr;
	}

	CGameObject* pClone = Proto_Iterfind->second->Clone();
	// clone check
	if (nullptr == pClone)
	{
		TCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Failed To Clone %s Prototype", GameObjectTag);
		MSG_BOX(szBuffer);
		return nullptr;
	}

	//find Scene
	//SceneID 추가 끝 
	auto Manager_Iterfind = m_mapObjManager.find(iScene);
	if (Manager_Iterfind == m_mapObjManager.end())
	{
		Manager_Iterfind = m_mapObjManager.emplace(iScene, CLayer::Create()).first;
	}

	Manager_Iterfind->second->Add_GameObject(pLayerTag, pClone);
	return pClone;
}


HRESULT CGameObject_Manager::ClearForScene(const _int& iScene)
{
	auto iter_find = m_mapObjManager.find(iScene);
	if (m_mapObjManager.end() == iter_find)
	{
		MSG_BOX(L"not exisit SceneID");
		return E_FAIL;
	}
	SafeRelease(iter_find->second);
	m_mapObjManager.erase(iter_find);

	return S_OK;
}

CGameObject * CGameObject_Manager::Get_GameObject(const _int & iScene, const _tchar * pLayerTag)
{

	auto iter_find = m_mapObjManager.find(iScene);

	if (FAILED(FindCheck_Obj(iter_find)))
	{
		MSG_BOX(L"no exisit SceneID");
		return nullptr;
	}

	return (*iter_find).second->Get_GameObject(pLayerTag);
}

list<CGameObject*>* CGameObject_Manager::Get_Layer(const _int & iScene, const _tchar * pLayerTag)
{
	auto iter_find = m_mapObjManager.find(iScene);

	if (FAILED(FindCheck_Obj(iter_find)))
	{
		MSG_BOX(L"no exisit SceneID");
		return nullptr;
	}

	return (*iter_find).second->Get_Layer(pLayerTag);
}


void CGameObject_Manager::Free()
{
	//프로토타입 클리어 
	for (auto& pair : m_mapPrototypes)
	{
		SafeRelease(pair.second);
	}
	m_mapPrototypes.clear();

	for (auto& pair : m_mapObjManager)
	{
		SafeRelease(pair.second);
	}
	m_mapObjManager.clear();
}

//  [2/2/2021 Administrator]
//인자값 두개이상 되면 귀찮아지는데 전역적으로 사용하기 쉽게 stl 템플릿으로 덕칠하는것도 아닌건같고 
HRESULT CGameObject_Manager::FindCheck_Obj(LAYERS::iterator& rIter)
{
	if (rIter == m_mapObjManager.end())
		return E_FAIL;

	return S_OK;
}

HRESULT CGameObject_Manager::FindCheck_Proto(PROTOTYPES::iterator & rIter)
{
	if (rIter == m_mapPrototypes.end())
		return E_FAIL;

	return S_OK;
}
