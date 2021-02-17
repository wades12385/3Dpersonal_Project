#include "Font_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFont_Manager)

CFont_Manager::CFont_Manager()
{
}

HRESULT CFont_Manager::Ready_Font(LPDIRECT3DDEVICE9 pDeivce, const _tchar * pFontTag, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	CFont*		pFont = nullptr;

	pFont = Find_Font(pFontTag);
	if (nullptr != pFont)
		return E_FAIL;

	pFont = CFont::Create(pDeivce, pFontType, iWidth, iHeight, iWeight);
	NULL_CHECK_RETURN(pFont, E_FAIL);

	m_mapFont.emplace(pFontTag, pFont);

	return S_OK;
}

void CFont_Manager::Render_Font(const _tchar * pFontTag, const _tchar * pString, const _vec2 * pPos, D3DXCOLOR Color)
{
	CFont*	pFont = Find_Font(pFontTag);
	NULL_CHECK(pFont);

	pFont->Render_Font(pString, pPos, Color);
}

CFont * CFont_Manager::Find_Font(const _tchar * pFontTag)
{
	auto	iter = find_if(m_mapFont.begin(), m_mapFont.end(), CTagFinder(pFontTag));

	if (iter == m_mapFont.end())
		return nullptr;

	return iter->second;
}

void CFont_Manager::Free()
{
	for_each(m_mapFont.begin(), m_mapFont.end(), CDeleteMap());
	m_mapFont.clear();
}
