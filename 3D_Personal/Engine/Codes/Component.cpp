#include "Component.h"

USING(Engine)

CComponent::CComponent(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(m_pDevice);
}

CComponent::CComponent(const CComponent & other)
	: m_pDevice(other.m_pDevice)
{
	SafeAddRef(m_pDevice);
}


void CComponent::Free()
{
	SafeRelease(m_pDevice);
}
