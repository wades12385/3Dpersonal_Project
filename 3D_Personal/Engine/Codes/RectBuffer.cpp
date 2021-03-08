#include "RectBuffer.h"


USING(Engine)
CRectBuffer::CRectBuffer(LPDIRECT3DDEVICE9 pDevice)
	:CVIBuffer(pDevice)
{
}

CRectBuffer::CRectBuffer(const CRectBuffer & other)
	:CVIBuffer(other)
{
}

HRESULT CRectBuffer::Ready_Component()
{
	m_iVertexSize = sizeof(VTX_TEXTURE);
	m_iVertexCount = 4;
	m_iTriCount = 2;
	m_dwFVF = FVF_VTX_TEXTURE;
	m_iIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::Ready_Component());
	VTX_TEXTURE*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	pVertex[0].vPosition = _vec3(-0.5f, 0.5f, 0.f);
	pVertex[0].vUV = _vec2(0.f, 0.f);

	pVertex[1].vPosition = _vec3(0.5f, 0.5f, 0.f);
	pVertex[1].vUV = _vec2(1.f, 0.f);

	pVertex[2].vPosition = _vec3(0.5f, -0.5f, 0.f);
	pVertex[2].vUV = _vec2(1.f, 1.f);

	pVertex[3].vPosition = _vec3(-0.5f, -0.5f, 0.f);
	pVertex[3].vUV = _vec2(0.f, 1.f);
	m_pVB->Unlock();


	INDEX16*		pIndex = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

CComponent * CRectBuffer::Clone()
{
	return new CRectBuffer(*this);
}

CRectBuffer * CRectBuffer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CRectBuffer*		pIns = new CRectBuffer(pDevice);

	if (FAILED(pIns->Ready_Component()))
		SafeRelease(pIns);

	return pIns;
}

void CRectBuffer::Free()
{
	CVIBuffer::Free();
}
