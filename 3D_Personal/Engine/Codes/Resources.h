#pragma once
#ifndef __RESOURCES_H__
#include "Component.h"
BEGIN(Engine)
class ENGINE_DLL CResources abstract : public CComponent
{
protected:
	explicit CResources(LPDIRECT3DDEVICE9 pDevice);
	explicit CResources(const CResources& other);
	virtual ~CResources() = default;
public:
	// CComponent을(를) 통해 상속됨
	virtual HRESULT Ready_Component() override;
	virtual HRESULT Update_Component(const _float & fTimeDelta = 0.f) override;
	virtual void Free() override;

	virtual CComponent* Clone()PURE;
protected:
	_bool				m_bClone;
};
END

#define __RESOURCES_H__
#endif
