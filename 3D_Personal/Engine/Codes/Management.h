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

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 Get_Device();
public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene);
	_int	Get_SceneID();
public: 
	/* For.GameObjectManager */
	HRESULT		 AddGameObjectPrototype(const  _tchar* pProtoTag, CGameObject* pPrototype);
	CGameObject* AddGameObject(const size_t& nSceneID , const _tchar* GameObjectTag, const _tchar* pLayerTag);
	CGameObject* AddGameObject(const _tchar* GameObjectTag, const _tchar* pLayerTag);
public:
	CComponent*	 Clone_Componet();
public: /* For.Renderer */
	HRESULT AddRenderer(eRenderID eID, CGameObject* pGameObject);

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
수직상승적인 커플링 회피 
메니지먼트는 서로 모르게 매니저들의 최상위를 이 클래스로 두고 하위 싱글톤들은 서로 모르게 

//  [2/3/2021 wades]
랜더러가 싱글톤으로 바꾸는게 통일성이 있긴한데 나중에 해야지 
장치 참조하는 setter추가해서 하면 될듯

*/