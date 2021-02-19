#pragma once
#ifndef __MFCCOLBOX_H__
#include "Gameobject.h"

USING(Engine)
class CColBox : public CGameObject
{
private:
	explicit CColBox(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CColBox() = default;
public:
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint UpdateGameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdateGameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	virtual CGameObject * Clone() override;


	void	Set_Pos(const _vec3& vPos);
	void	Set_Scale(const _vec3& vScale);
	_bool   Peeking( _vec3 vRayPos ,  _vec3 vRayDir);
	
	static CColBox* Create(LPDIRECT3DDEVICE9 pDevice);
public:
	CTransform*			m_pTrans = nullptr;
	CColliderBox*		m_pCollsion = nullptr;
	eBoxType::eBoxType  m_eType;
	_int				m_iNavID;
	_bool				m_bHide;
	
};

#define __MFCCOLBOX_H__
#endif
