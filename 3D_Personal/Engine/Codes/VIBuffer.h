#pragma once
#ifndef __VIBUFFER_H__

#include "Resources.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CResources
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer(const CVIBuffer& other);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT ReadyComponent()PURE;
	virtual HRESULT Render_VIBuffer() PURE;

	virtual CComponent* Clone() PURE;
public:
	virtual void Free() override;
protected:
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	LPDIRECT3DVERTEXBUFFER9		m_pVB ;
	_uint					    m_iVertexSize = 0;
	_uint					    m_iVertexCount = 0;
	_uint					    m_iTriCount = 0;
	_uint					    m_iFVF = 0;
};
END

#define __VIBUFFER_H__
#endif

