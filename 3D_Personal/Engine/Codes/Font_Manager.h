#pragma once
#ifndef __FONTMANAGER_H__
#include "Base.h"
#include "Font.h"

BEGIN(Engine)
class ENGINE_DLL CFont_Manager : public CBase
{
	DECLARE_SINGLETON(CFont_Manager)

public:
	explicit CFont_Manager();
	virtual ~CFont_Manager() = default;

public:
	HRESULT	Ready_Font(LPDIRECT3DDEVICE9 pDeivce,
		const _tchar* pFontTag,const _tchar* pFontType,
		const _uint& iWidth,
		const _uint& iHeight,
		const _uint& iWeight);

	void	Render_Font(const _tchar* pFontTag, const _tchar* pString,const _vec2* pPos,D3DXCOLOR Color);
private:
	CFont*		Find_Font(const _tchar* pFontTag);
private:
	unordered_map<const _tchar*, CFont*>		m_mapFont;
public:
	virtual void Free();
};
END
#define __FONTMANAGER_H__
#endif
