#pragma once
#ifndef __PLAYERCAMERA_H__
#include "Camera.h"
USING(Engine)
class CPlayerCamera : public CCamera
{
private:
	explicit CPlayerCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlayerCamera(const CPlayerCamera& other);
	virtual ~CPlayerCamera() = default;
public:
	// CCamera을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;

	virtual HRESULT RenderGameObject() override;
public:
	void Update_Move(CTransform* pTarget , CCollider* pCollidere);


public:

	const _float Get_CameraDis() { return m_fCameraDis; }
	const _float Get_CameraAngle() { return m_fCameraAngle; }

public:
	static CPlayerCamera* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone() override;
private:
	CTransform*		m_pTransCom = nullptr;
	_float			m_fCameraDis;
	_float          m_fCameraAngle;
private:
	virtual void Free() override;
};

#define __PLAYERCAMERA_H__
#endif
