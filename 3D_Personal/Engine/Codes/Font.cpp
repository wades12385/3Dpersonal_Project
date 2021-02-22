#include "Font.h"


USING(Engine)
CFont::CFont(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_pFont(nullptr)
	, m_pSprite(nullptr)
{
	m_pDevice->AddRef();
}

HRESULT CFont::Ready_Font(const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	D3DXFONT_DESC	Font_Desc;
	ZeroMemory(&Font_Desc, sizeof(D3DXFONT_DESC));

	Font_Desc.CharSet = HANGUL_CHARSET;
	lstrcpy(Font_Desc.FaceName, pFontType);
	Font_Desc.Width = iWidth;
	Font_Desc.Height = iHeight;
	Font_Desc.Weight = iWeight;

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &Font_Desc, &m_pFont)))
	{
		MSG_BOX(L"Font Create Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX(L"Sprite Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CFont::Render_Font(const _tchar * pString, const _vec2 * pPos, D3DXCOLOR Color)
{
	RECT	rc{ _long(pPos->x), _long(pPos->y) };

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pFont->DrawTextW(m_pSprite, pString, lstrlen(pString), &rc, DT_NOCLIP, Color);

	m_pSprite->End();
}

CFont * CFont::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	CFont*	pIns = new CFont(pDevice);

	if (FAILED(pIns->Ready_Font(pFontType, iWidth, iHeight, iWeight)))
	{
		MSG_BOX(L"Font Create Failed");
		SafeRelease(pIns);
	}

	return pIns;
}

void CFont::Free()
{
	SafeRelease(m_pFont);
	SafeRelease(m_pSprite);
	SafeRelease(m_pDevice);
}
