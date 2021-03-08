#pragma once
#ifndef __TOOLCAMERA_H__
#include "Camera.h"
USING(Engine)
class CToolCamera : public CCamera
{
private:
	explicit CToolCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CToolCamera(const CToolCamera& other);
	virtual ~CToolCamera() = default;
public:
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	
	static CToolCamera* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone() override;

	void Move(const _float fDeltaTime);

	virtual void Free() override;
	CToolCamera* Get_Ins() { return this; }
	_bool			m_bFix;
	_float			m_fSpeed;
	_float			m_fAngleSpeed;

};

#define __TOOLCAMERA_H__
#endif
