#pragma once
#ifndef __COlLIBOX_H__
#include "GameObject.h"

USING(Engine)

class ColliBox : public CGameObject
{
private:
	explicit ColliBox(LPDIRECT3DDEVICE9 pDevice);
	explicit ColliBox(const ColliBox& other);
	virtual ~ColliBox() = default;

public:
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	virtual CGameObject * Clone() override;


	void	Set_Pos(const _vec3& vPos);
	void	Set_Scale(const _vec3& vScale);


	static ColliBox* Create(LPDIRECT3DDEVICE9 pDevice);
private:
	virtual void Free() override;
public:
	CTransform*			m_pTrans = nullptr;
	CCollider*			m_pCollider = nullptr;

	_int				m_iNavID;

	_bool				m_bTrigger;
	_bool				m_bHide;
	_bool				m_bSelect;
};

#define __COlLIBOX_H__
#endif
