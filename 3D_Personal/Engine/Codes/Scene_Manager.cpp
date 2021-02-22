#include "Scene_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CScene_Manager)

CScene_Manager::CScene_Manager()
	:m_iCurSceneID(-1)
	, m_pCurrentScene(nullptr)
	, m_pInitLog(nullptr)
{
}

//게임메니저와 awake Ready 연계 때문에 매니지먼트에서 호출하는걸로
HRESULT CScene_Manager::Set_CurrentScene(const _int&  iSceneID,  CScene*  pCurrentScene)
{
	if (nullptr == pCurrentScene || m_iCurSceneID == iSceneID)
	{
		SafeRelease(pCurrentScene);
		return E_FAIL;
	}

	SafeRelease(m_pCurrentScene);
	
	if (m_pInitLog[iSceneID])
	{
		if (FAILED(pCurrentScene->ReInitialize_Scene()))
		{
			SafeRelease(pCurrentScene);
			return E_FAIL;
		}
	}
	else
	{
		m_pInitLog[iSceneID] = true;
		if (FAILED(pCurrentScene->Initialize_Scene()))
		{
			SafeRelease(pCurrentScene);
			return E_FAIL;
		}
	}
	m_pCurrentScene = pCurrentScene;
	m_iCurSceneID = iSceneID;
	return S_OK;
}

//현재 씬상태가 결정됬는지 체크 후 아웃으로 받음
HRESULT CScene_Manager::Get_SceneID(OUT _int& rSceneID)
{
	if (m_iCurSceneID == NONE_SCENE)
		return E_FAIL;

	rSceneID = m_iCurSceneID;
	return S_OK;
}

HRESULT CScene_Manager::Scene_InitLogReserve(const _uint & iCnt)
{
	if (m_pInitLog != nullptr)
		return E_FAIL;

	m_pInitLog = new _bool[iCnt];
	ZeroMemory(m_pInitLog, sizeof(_bool) * iCnt);
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
	SafeDeleteArray(m_pInitLog);
	SafeRelease(m_pCurrentScene);
}

