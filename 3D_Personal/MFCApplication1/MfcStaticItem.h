#pragma once
#ifndef __MFCSTATIC_ITEM_H__
#include "Item.h"
USING(Engine)
class CMfcStaticItem : public CItem
{
private:
	explicit CMfcStaticItem(LPDIRECT3DDEVICE9 pDevice);
	explicit CMfcStaticItem(const CMfcStaticItem& other);
	virtual ~CMfcStaticItem() = default;

public:
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;

	static CMfcStaticItem* Create(LPDIRECT3DDEVICE9 pDevice,const _int& iTableID);
	virtual CGameObject *  Clone() override;

	void    Set_Sacle(_float fScale);
public:
	_bool				m_bSelect;
private:
	virtual void Free() override;
};

#define __MFCSTATIC_ITEM_H__
#endif
