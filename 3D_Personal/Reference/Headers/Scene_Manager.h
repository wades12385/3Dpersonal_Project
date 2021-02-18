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
	HRESULT Scene_InitLogReserve(const _uint& iCnt);
public:
	HRESULT Awake_SceneMgr();
	HRESULT Ready_SceneMgr();
	_uint	Update_SceneMgr(const _float& fTimeDeleta);
	_uint	LateUpdate_SceneMgr(const _float& fTimeDeleta);
	void	Render_Scene();
public:
	virtual void Free() override;
private:
	// 맵으로 만들고 키값 유무로 첫생성 루틴 
	// 생성뒤 다시 돌아오면 리콜 루틴 

	_bool*	m_pInitLog; // 씬 첫생성 로그
	CScene*	m_pCurrentScene;
	_int  m_iCurSceneID;
};
END

#define __SCENEMANAGER_H__
#endif
	