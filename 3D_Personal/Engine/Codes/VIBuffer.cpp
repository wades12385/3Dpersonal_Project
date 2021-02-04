#include "VIBuffer.h"

USING(Engine)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9  pDevice)
	: CResources(pDevice)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & other)
	: CResources(other)
	, m_pVB(other.m_pVB)
	, m_iVertexSize(other.m_iVertexSize)
	, m_iVertexCount(other.m_iVertexCount)
	, m_iTriCount(other.m_iTriCount)
	, m_iFVF(other.m_iFVF)
{
}

HRESULT CVIBuffer::ReadyComponent()
{
	return S_OK;
}

HRESULT CVIBuffer::Render_VIBuffer()
{

	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	CComponent::Free();
}
