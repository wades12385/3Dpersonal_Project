#pragma once
#ifndef __COMPONENT_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent(LPDIRECT3DDEVICE9 pDevice);
	explicit CComponent(const CComponent& other);
	virtual ~CComponent() = default;

public:
	virtual HRESULT Ready_Component() PURE;
	virtual HRESULT Update_Component(const _float& fTimeDelta = 0.f) PURE;

	virtual void Free()PURE;

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
};
END

#define __COMPONENT_H__
#endif                                                                                                                                                                                                                  