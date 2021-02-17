#pragma once
#ifndef __CAMERA_H__
#include "GameObject.h"
BEGIN(Engine)
class ENGINE_DLL CCamera abstract : public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CCamera(const CCamera& other);
	virtual ~CCamera()= default;

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _uint	LateUpdateGameObject(const _float & fDeltaTime) override;
public:
	const CAMERA_DESC& Get_Camera() { return m_tCameraDesc; }
	void  Set_Camera(const CAMERA_DESC tCameraDesc) { m_tCameraDesc = tCameraDesc; };
protected:
	virtual void Free() override;
protected:
	CAMERA_DESC m_tCameraDesc;
};
END
#define __CAMERA_H__
#endif
