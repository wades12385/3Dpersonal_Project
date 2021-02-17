#pragma once
#ifndef __LIGHT_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CLight final : public CBase
{
private:
	explicit CLight(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLight() = default;

	// CBase을(를) 통해 상속됨
public:
	HRESULT				Ready_Light(const D3DLIGHT9* pLightInfo, const _uint& iIndex);
	static CLight*		Create(LPDIRECT3DDEVICE9 pDevice, const D3DLIGHT9* pLightInfo, const _uint& iIndex);

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DLIGHT9				m_tLightInfo;
	_uint					m_iIndex;
	virtual void Free() override;
};


END

#define __LIGHT_H__
#endif
