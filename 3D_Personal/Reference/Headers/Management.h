#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Graphic_Device.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "Resource_Manager.h"
#include "Renderer.h"
#include "Datatable_Manager.h"

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
	HRESULT ClearForScene(_int iSceneIndex);//게임매니저의 레이어 데이터 삭제 예약을 검
	void	BegineRender();
	void	EndRender(HWND hWnd);

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 Get_Device();
public:
	/* For.SceneManager */
	// 
	HRESULT			    SetUp_ChangeScene(_int iSceneID, CScene* pCurrentScene);
	_int				Get_SceneID();
	HRESULT				SceneInitLog_Reserve(const _int& iSceneCnt);
public: 
	/* For.GameObjectManager */
	HRESULT				Ready_GameObjectPrototype(const  _tchar* pProtoTag, CGameObject* pPrototype);
	CGameObject*		Ready_GameObject(const size_t& nSceneID, const _tchar* GameObjectTag, const _tchar* pLayerTag);
	CGameObject*		Ready_GameObject(const _tchar* ProtoTag, const _tchar* pLayerTag);
	CGameObject*		LateReady_GameObject(const _tchar* GameObjectTag, const _tchar* pLayerTag);

	void				Add_InstantGameObject(CGameObject* pGameObj, const _tchar* pLayerTag);
	CGameObject*		Add_InstantGameObject(const _tchar* pProtoTag, const _tchar* pLayerTag);

	CGameObject*		Get_GameObjet(const _tchar* pLayerTag);
	list<CGameObject*>* Get_GameObjetList(const _tchar* pLayerTag);
public:
	/*For.ResourcesManagner*/
	HRESULT		 Ready_Resource(const _tchar* pCompTag,const eResourcesID::eResourcesID& eCompID, CResources* pComp);
	HRESULT		 Ready_Mesh(const _tchar* pMeshTag, eResourcesID::eResourcesID eType, const _tchar* pFilePath, const _tchar* pFileName);
	HRESULT		 Load_NavMesh(const _tchar* pMeshTag,const _tchar* pFilePath);

	HRESULT		 Ready_Texture(const _tchar * pResouceTag, const _tchar * pFilePath, const _uint & iCnt);
	CComponent*	 Clone_Resource(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourcesID);
public: 
	/* For.Renderer */
	HRESULT		 Add_Renderer(eRenderID eID, CGameObject* pGameObject);
public:
	HRESULT		Load_DataTable(const _tchar* pFilePath);
	HRESULT		Save_DataTable(const _tchar * pFilePath);
	vector<OBJDATA>* Get_DataTableVector();

public:
	virtual void Free() override;
	static void ReleaseEngine();
private:
	// SingleTon
	CGraphic_Device*				m_pGraphic_Dev = nullptr;
	CScene_Manager*					m_pSceneManager = nullptr;
	CGameObject_Manager*			m_pGameObjectManager = nullptr;
	CResource_Manager*				m_pResource_Manager = nullptr;
	CDatatable_Manager*				m_pDataTable_Manager = nullptr;
	CRenderer*						m_pRenderer = nullptr;
	_bool							m_bWaitChangeScene;
	list<_int>						m_listChangeSeneIdReservation; // 예전 씬들이 보관 이

};
END

#define __MANAGEMENT_H__
#endif

/*
Summary
수직상승적인 커플링 회피 
메니지먼트는 서로 모르게 매니저들의 최상위를 이 클래스로 두고 하위 싱글톤들은 서로 모르게 

//  [2/3/2021 wades]
랜더러가 싱글톤으로 바꾸는게 통일성이 있긴한데 나중에 해야지 
장치 참조하는 setter추가해서 하면 될듯

*/