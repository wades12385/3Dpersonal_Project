#include "Scene_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CScene_Manager)

CScene_Manager::CScene_Manager()
	:m_iCurSceneID(NONE_SCENE)
	, m_pCurrentScene(nullptr)
	, m_pInitLog(nullptr)
	, m_bWaitChangeScene(false)
	, m_iNextSceneID(NONE_SCENE)
{
}

//���Ӹ޴����� awake Ready ���� ������ �Ŵ�����Ʈ���� ȣ���ϴ°ɷ�
HRESULT CScene_Manager::Set_CurrentScene(const _int&  iSceneID,  CScene*  pCurrentScene)
{
	//���ڰ� ���� üũ 
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
	//�������� �߰� �����ǵ� ���������� ...
	m_pCurrentScene = pCurrentScene;
	//ó�� �� ���� 
	if (m_iCurSceneID == NONE_SCENE)
		m_iCurSceneID = iSceneID;
	//�ٸ������� �Ѿ��	
	else
	{
		if (m_iNextSceneID != NONE_SCENE)
		{
			MSG_BOX(L"Error Recalling SetCurScene() ");
			return E_FAIL;
		}

		m_bWaitChangeScene = true;
		m_iNextSceneID = iSceneID;
	}

	return S_OK;
}

//���� �����°� ��������� üũ 
//�� ��ȯ�� GameObjManagerReady�ҋ� ���� �� id�� �޾ƾ��ϴ� ����ȯ ���� ���������� ������� ��ID�� �Ѿ
HRESULT CScene_Manager::Get_SceneID(OUT _int& rSceneID)
{
	if (m_iCurSceneID == NONE_SCENE)
		return E_FAIL;

	if(m_bWaitChangeScene && m_iNextSceneID != NONE_SCENE)
		rSceneID = m_iNextSceneID;
	else
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

void CScene_Manager::Check_WaitChange()
{
	if (m_bWaitChangeScene)
	{
		m_iCurSceneID = m_iNextSceneID;
		m_iNextSceneID = NONE_SCENE;
		m_bWaitChangeScene = false;
	}
}

void CScene_Manager::Free()
{
	SafeDeleteArray(m_pInitLog);
	SafeRelease(m_pCurrentScene);
}

