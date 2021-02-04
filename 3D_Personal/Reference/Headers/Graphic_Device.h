#pragma once
#ifndef __GRAPHIC_DEVICE_H__

#include "Base.h"

BEGIN(Engine)
class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)
private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device() =default;
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice;}
public:
	HRESULT Ready_Graphic_Device(HWND hWnd, _uint iWinCX, _uint iWinCY, eWinMode eDisplayMode);

	void Render_Begine(D3DXCOLOR Color);
	void Render_End(HWND hTargetHwnd = NULL);
public:
	virtual void Free() override;

private:	
	LPDIRECT3D9 m_pSDK; 
	LPDIRECT3DDEVICE9 m_pDevice; 
};
END

#define __GRAPHIC_DEVICE_H__
#endif