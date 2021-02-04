#pragma once
#ifndef __SCENEMANAGER_H__

#include "Base.h"
#include "Scene.h"

BEGIN(Engine)
class CSceneManager final : public CBase
{

	DECLARE_SINGLETON(CSceneManager)
private:
	explicit CSceneManager();
	virtual	 ~CSceneManager()= default;

public:
	HRESULT Set_CurrentScene(const _int& iSceneID, shared_ptr<CScene> pCurrentScene);

	HRESULT Get_SceneID(OUT _int& rSceneID);
public:
	_uint Update_Scene(const _float& fTimeDeleta);
	_uint LateUpdate_SceneMgr(const _float& fTimeDeleta);
	void  Render_Scene();
public:
	virtual void Free() override;

private:
	shared_ptr<CScene>	m_pCurrentScene = nullptr;
	_int  m_iSceneID;
};
END

#define __SCENEMANAGER_H__
#endif
	