#pragma once
#ifndef __FONT_H__	
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CFont : public CBase
{
private:
	explicit CFont(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CFont() = default;

public:
	HRESULT		Ready_Font(const _tchar* pFontType,
		const _uint& iWidth,
		const _uint& iHeight,
		const _uint& iWeight);

	void		Render_Font(const _tchar* pString,const _vec2* pPos, D3DXCOLOR Color);

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	LPD3DXFONT				m_pFont;
	LPD3DXSPRITE			m_pSprite;

public:
	static CFont*		Create(LPDIRECT3DDEVICE9 pDevice,
		const _tchar* pFontType,const _uint& iWidth,const _uint& iHeight, const _uint& iWeight);
private:
	virtual void Free()override;
};
END
#define __FONT_H__
#endif