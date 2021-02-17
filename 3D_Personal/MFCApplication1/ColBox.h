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

	static CColBox* Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pComTag);
public:
	CTransform*		m_pTrans = nullptr;
	CColliderBox*		m_pCollsion = nullptr;
	_bool			m_bHide;
	
	
};

#define __MFCCOLBOX_H__
#endif
