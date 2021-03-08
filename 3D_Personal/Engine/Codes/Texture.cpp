#include "Texture.h"


USING(Engine)
CTexture::CTexture(LPDIRECT3DDEVICE9 pDevice)
	:CResources(pDevice)
{
}

CTexture::CTexture(const CTexture & other)
	:CResources(other)
{
	m_vecTexture.reserve(other.m_vecTexture.size());
	m_vecTexture = other.m_vecTexture;
	for (auto& iter : m_vecTexture)
		iter->AddRef();

}

HRESULT CTexture::Ready_Texture(const _tchar * pPath, const _uint & iCnt)
{
	m_vecTexture.reserve(iCnt);

	LPDIRECT3DTEXTURE9		pTexture = nullptr;
	for (_uint i = 0; i < iCnt; ++i)
	{
		TCHAR	szFileName[256] = L"";
		wsprintf(szFileName, pPath, i);
		if (FAILED(D3DXCreateTextureFromFile(m_pDevice, szFileName, &pTexture)))
			return E_FAIL;

		m_vecTexture.emplace_back(pTexture);
	}

	return S_OK;
}

void CTexture::Set_Texture(const _uint & iIndex)
{
	if (m_vecTexture.size() < iIndex)
		return;

	// 텍스쳐를 그리기 하는 함수
	m_pDevice->SetTexture(0, m_vecTexture[iIndex]);
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pPath, const _uint & iCnt)
{
	CTexture*		pIns = new CTexture(pDevice);

	if (FAILED(pIns->Ready_Texture(pPath, iCnt)))
		SafeRelease(pIns);

	return pIns;
}

CComponent * CTexture::Clone()
{
	return new CTexture(*this);
}

void CTexture::Free()
{


	for (auto& iter : m_vecTexture)
		SafeRelease(iter);

	m_vecTexture.clear();
	CResources::Free();
}
