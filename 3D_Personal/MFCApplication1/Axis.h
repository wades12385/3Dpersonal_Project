#pragma once
#ifndef __MFCAXIS_H__
#include "GameObject.h"
USING(Engine)
class CAxis : public CGameObject
{
private:
	explicit CAxis(LPDIRECT3DDEVICE9 pDevice);
	explicit CAxis(const CAxis& other);
	virtual ~CAxis() = default;
public:


	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	virtual CGameObject * Clone() override;

	static CAxis* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
public:
	_vec3     m_vPosition;
	_bool	  m_bShow;

	LPD3DXLINE					m_pDXLine = nullptr;


};

#define __MFCAXIS_H__ 
#endif // !__MFCAXIS_H__
