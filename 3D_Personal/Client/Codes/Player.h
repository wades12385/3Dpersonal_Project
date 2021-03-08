#pragma once
#ifndef __PLAYER_H__
#include "GameObject.h"
USING(Engine)
class CPlayer : public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlayer(const CPlayer& other);
	virtual ~CPlayer() = default;


public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint	Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint	LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
public:

private:
	void								Key_Input(const _float& fDeltaTime);
	void								Move_Input(const _float& fDeltaTime);

	//위치 보정 밑 여러 작업 수행 
	void								Update_Move();
	void								Update_Core(const _vec3& vAxis, const _float& fDeltaTime);
	void								Update_Camera();

	//
	void							Move_Navi(const _vec3& vScala);
	void							Test_Radius();
private:
	class CPlayerCore*				m_pCore = nullptr;
	class CPlayerCamera*			m_pCamera = nullptr;
	CTransform*						m_pTrans = nullptr;
	CCollider*						m_pCollider = nullptr;
	_float							m_fMoveSpeed;
	_float							m_fSpinSpeed;
	_float							m_fCoreSpinSpeed;

	//move logic
	_vec3							m_vMoveEndPos; // 이동 연산 결과값 보관용
	_vec3							m_vMoveScala;
	_vec3							m_vMoveDir;

	_bool							m_bIsMoving;
	_vec3							m_vCoreAxis;
public:
	static  CPlayer*				Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject*			Clone() override;
private:
	virtual void Free() override;
};
#define __PLAYER_H__
#endif
