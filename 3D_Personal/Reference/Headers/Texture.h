#pragma once
#ifndef __TEXTURE_H__
#include "Resources.h"
BEGIN(Engine)
class ENGINE_DLL CTexture : public CResources
{
public:
	explicit CTexture(LPDIRECT3DDEVICE9 pDevice);
	explicit CTexture(const CTexture& other);
	virtual ~CTexture() =default;

public:
	HRESULT		Ready_Texture(const _tchar* pPath,const _uint& iCnt);
	void		Set_Texture(const _uint& iIndex = 0);
	//void		Set_Texture(LPD3DXEFFECT& pEffect, const char* pConstantTable, const _uint& iIndex = 0);


private:
	vector<IDirect3DBaseTexture9*>			m_vecTexture;

public:
	static CTexture*		Create(LPDIRECT3DDEVICE9 pDevice,
									const _tchar* pPath,const _uint& iCnt = 1);

	virtual CComponent*		Clone();
	virtual void			Free();
};
END
#define __TEXTURE_H__
#endif
