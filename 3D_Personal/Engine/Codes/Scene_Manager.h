#pragma once
#ifndef __SCENEMANAGER_H__

#include "Base.h"
#include "Scene.h"

BEGIN(Engine)
class CScene_Manager final : public CBase
{
	DECLARE_SINGLETON(CScene_Manager)
private:
	explicit CScene_Manager();
	virtual	 ~CScene_Manager()= default;
public:
	HRESULT Set_CurrentScene(const _int& iSceneID, CScene* pCurrentScene);
	HRESULT Get_SceneID(OUT _int& rSceneID);
public:
	HRESULT Awake_SceneMgr();
	HRESULT Ready_SceneMgr();
	_uint	Update_SceneMgr(const _float& fTimeDeleta);
	_uint	LateUpdate_SceneMgr(const _float& fTimeDeleta);
	void	Render_Scene();
public:
	virtual void Free() override;
private:
	CScene*	m_pCurrentScene;
	_int  m_iSceneID;
};
END

#define __SCENEMANAGER_H__
#endif
	