#pragma once
#ifndef __LIGHTMANAGER_H__
#include "Base.h"
#include "Light.h"
BEGIN(Engine)
class ENGINE_DLL CLight_Manager : public CBase
{
	DECLARE_SINGLETON(CLight_Manager)
private:
	explicit CLight_Manager();
	virtual ~CLight_Manager() = default;
public:
	HRESULT		Add_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);

	// CBase을(를) 통해 상속됨
private:
	list<CLight*>				m_LightList;
	virtual void Free() override;
};
END
#define __LIGHTMANAGER_H__
#endif
