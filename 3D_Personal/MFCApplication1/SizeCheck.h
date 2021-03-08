#pragma once
#ifndef __MFCSIZE_CHECK_H__
#include "GameObject.h"

USING(Engine)
class CSizeCheck : public CGameObject
{
private:
	explicit CSizeCheck(LPDIRECT3DDEVICE9 pDevice);
	explicit CSizeCheck(const CSizeCheck& other);
	virtual ~CSizeCheck() = default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	virtual CGameObject * Clone() override;


	static CSizeCheck* Create(LPDIRECT3DDEVICE9 pDevice);
	void Set_ColliderSize(_float fSize);
	virtual void Free() override;
public:
	CTransform*		m_pTrans = nullptr;
	CCollider*		m_pCollider = nullptr;

	_bool			m_bHide;
	_float			m_fSize;

};

#define __MFCSIZE_CHECK_H__
#endif // !__MFCSIZE_CHECK_H__
