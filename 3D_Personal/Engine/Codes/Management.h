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
����������� Ŀ�ø� ȸ�� 
�޴�����Ʈ�� ���� �𸣰� �Ŵ������� �ֻ����� �� Ŭ������ �ΰ� ���� �̱������ ���� �𸣰� 

//  [2/3/2021 wades]
�������� �̱������� �ٲٴ°� ���ϼ��� �ֱ��ѵ� ���߿� �ؾ��� 
��ġ �����ϴ� setter�߰��ؼ� �ϸ� �ɵ�

*/