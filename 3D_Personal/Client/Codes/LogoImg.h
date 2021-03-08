#pragma once
#ifndef __LOGOIMG_H__
#include "GameObject.h"
USING(Engine)
class CLogoImg : public CGameObject
{
private:
	CLogoImg(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLogoImg() = default;
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	virtual CGameObject * Clone() override;

	static CLogoImg* Create(LPDIRECT3DDEVICE9 pDevice);
private:
	CRectBuffer*			m_pBufferCom = nullptr;
	CTexture*				m_pTexCom = nullptr;
	CTransform*				m_pTransCom= nullptr;
private:
	virtual void Free() override;
};

#define __LOGOIMG_H__
#endif
