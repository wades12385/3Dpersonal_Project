#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Graphic_Device.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "Resource_Manager.h"
#include "Renderer.h"

BEGIN(Engine)
class ENGINE_DLL CManagement final : public CBase
{
	DECLARE_SINGLETON(CManagement)
private:
	explicit CManagement();
	virtual ~CManagement() = default;
public:
	/* For.General */
	HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, eWinMode eDisplaymode);
	_uint	UpdateEngine(const _float& fTimeDelta);
	HRESULT RenderEngine(HWND hWnd = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);
	void	BegineRender();
	void	EndRender(HWND hWnd);

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 Get_Device();
public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene);
	_int	Get_SceneID();
	HRESULT	SceneInitLog_Reserve(const _int& iSceneCnt);
public: 
	/* For.GameObjectManager */
	HRESULT		 Ready_GameObjectPrototype(const  _tchar* pProtoTag, CGameObject* pPrototype);
	CGameObject* Ready_GameObject(const size_t& nSceneID , const _tchar* GameObjectTag, const _tchar* pLayerTag);
	CGameObject* Ready_GameObject(const _tchar* GameObjectTag, const _tchar* pLayerTag);
	CGameObject* LateReady_GameObject(const _tchar* GameObjectTag, const _tchar* pLayerTag);
	
	CGameObject* Add_GameObject(const _tchar* GameObjectTag, const _tchar* pLayerTag);
	void		 Add_InstantGameObject( CGameObject* pGameObj, const _tchar* pLayerTag);

	CGameObject* Get_GameObjet(const _tchar* pLayerTag);  
	list<CGameObject*>* Get_GameObjetList(const _tchar* pLayerTag);

public:
	/*For.ResourcesManagner*/
	HRESULT		 Ready_Mesh(const _tchar* pMeshTag, eResourcesID::eResourcesID eType, const _tchar* pFilePath, const _tchar* pFileName);
	HRESULT		 Load_NavMesh(const _tchar* pMeshTag,const _tchar* pFilePath);


	HRESULT		 Ready_Texture(const _tchar * pResouceTag, const _tchar * pFilePath, const _uint & iCnt);
	CComponent*	 Clone_Resource(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourcesID);
public: 
	/* For.Renderer */
	HRESULT		 Add_Renderer(eRenderID eID, CGameObject* pGameObject);
public:
	virtual void Free() override;
	static void ReleaseEngine();
private:
	// SingleTon
	CGraphic_Device*				m_pGraphic_Dev = nullptr;
	CScene_Manager*					m_pSceneManager = nullptr;
	CGameObject_Manager*			m_pGameObjectManager = nullptr;
	CResource_Manager*				m_pResource_Manager = nullptr;
	CRenderer*						m_pRenderer = nullptr;
};
END

#define __MANAGEMENT_H__
#endif

/*
Summary
����������� Ŀ�ø� ȸ�� 
�޴�����Ʈ�� ���� �𸣰� �Ŵ������� �ֻ����� �� Ŭ������ �ΰ� ���� �̱������ ���� �𸣰� 

//  [2/3/2021 wades]
�������� �̱������� �ٲٴ°� ���ϼ��� �ֱ��ѵ� ���߿� �ؾ��� 
��ġ �����ϴ� setter�߰��ؼ� �ϸ� �ɵ�

*/