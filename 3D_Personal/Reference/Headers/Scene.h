#pragma once
#ifndef __SCENE_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CScene abstract : public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CScene() = default;

public:
	virtual HRESULT Initialize_Scene()PURE;
	virtual HRESULT ReInitialize_Scene()PURE;
	virtual	HRESULT	Awake_Scene()PURE;
	virtual HRESULT Ready_Scene()PURE;
	virtual _uint	Update_Scene(const _float& fTimeDeleta) PURE;
	virtual _uint	LateUpdate_Scene(const _float& fTimeDeleta)PURE;
	virtual void	Render_Scene()PURE;
public:
	virtual void Free() override;
protected:
	LPDIRECT3DDEVICE9 m_pDevice;
};
END

#define __SCENE_H__
#endif

/*
Awake는 오브젝트들 추가하고 
Ready에서 오브젝트들 참조(래퍼런스 증가)
Render는 일단 디버깅용으로 폰트출력 

aasdfasdfasdfasdfsdf
*/