#pragma once
#ifndef __RECTBUFFER_H__
#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CRectBuffer : public CVIBuffer
{
private:
	explicit CRectBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CRectBuffer(const CRectBuffer& other);
	virtual ~CRectBuffer() = default;

public:
	// CVIBuffer��(��) ���� ��ӵ�
	virtual HRESULT Ready_Component() override;
	virtual CComponent * Clone() override;

	static CRectBuffer* Create(LPDIRECT3DDEVICE9 pDevice);
private:
	virtual void Free() override;
};
END
#define __RECTBUFFER_H__
#endif
