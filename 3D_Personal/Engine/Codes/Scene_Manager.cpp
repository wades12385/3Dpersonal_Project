#include "Scene_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CScene_Manager)

CScene_Manager::CScene_Manager()
	:m_iSceneID(-1)
	, m_pCurrentScene(nullptr)
{
}

//게임메니저와 awake Ready 연계 때문에 매니지먼트에서 호출하는걸로
HRESULT CScene_Manager::Set_CurrentScene(const _int&  iSceneID,  CScene*  pCurrentScene)
{
	if (nullptr == pCurrentScene || m_iSceneID == iSceneID)
		return E_FAIL;

	SafeRelease(m_pCurrentScene);

	m_pCurrentScene = pCurrentScene;
	m_iSceneID = iSceneID;

	return S_OK;
}

//현재 씬상태가 결정됬는지 체크 후 아웃으로 받음
HRESULT CScene_Manager::Get_SceneID(OUT _int& rSceneID)
{
	if (m_iSceneID == NONE_SCENE)
		return E_FAIL;

	rSceneID = m_iSceneID;
	return S_OK;
}

HRESULT CScene_Manager::Awake_SceneMgr()
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->Awake_Scene();
}

HRESULT CScene_Manager::Ready_SceneMgr()
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->Ready_Scene();
}

_uint CScene_Manager::Update_SceneMgr(const _float& fTimeDeleta)
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->Update_Scene(fTimeDeleta);
}

_uint CScene_Manager::LateUpdate_SceneMgr(const _float& fTimeDeleta)
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->LateUpdate_Scene(fTimeDeleta);
}

void CScene_Manager::Render_Scene()
{
	if (nullptr == m_pCurrentScene)
		return ;

	return m_pCurrentScene->Render_Scene();
}

void CScene_Manager::Free()
{
	SafeRelease(m_pCurrentScene);
}
