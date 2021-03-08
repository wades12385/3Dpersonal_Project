#include "VIBuffer.h"

USING(Engine)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9  pDevice)
	: CResources(pDevice)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
	, m_iVertexSize(0)
	, m_iVertexCount(0)
	, m_iTriCount(0)
	, m_iIdxSize(0)
	, m_dwFVF(0)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & other)
	: CResources(other)
	, m_pVB(other.m_pVB)
	, m_pIB(other.m_pIB)
	, m_iVertexSize(other.m_iVertexSize)
	, m_iVertexCount(other.m_iVertexCount)
	, m_iTriCount(other.m_iTriCount)
	, m_iIdxSize(other.m_iIdxSize)
	, m_dwFVF(other.m_dwFVF)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

HRESULT CVIBuffer::Ready_Component()
{

	FAILED_CHECK(m_pDevice->CreateVertexBuffer(m_iVertexSize * m_iVertexCount,
		0, 
		m_dwFVF,
		D3DPOOL_MANAGED,
		&m_pVB, NULL));

	FAILED_CHECK(m_pDevice->CreateIndexBuffer(m_iIdxSize * m_iTriCount,
		0,m_IdxFmt,D3DPOOL_MANAGED,&m_pIB, NULL));
	return S_OK;
}

HRESULT CVIBuffer::Render_VIBuffer()
{
	//이전 텍스쳐 세팅이 랜더링에 (컬러) 영향줌
	//m_pDevice->SetTexture(0, nullptr);
	m_pDevice->SetFVF(m_dwFVF);
	m_pDevice->SetIndices(m_pIB);

	m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);

	return S_OK;
}

void CVIBuffer::Free()
{
	SafeRelease(m_pIB);
	SafeRelease(m_pVB);
	CComponent::Free();
}
