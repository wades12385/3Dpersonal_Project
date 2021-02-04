#include "Resources.h"


USING(Engine)

CResources::CResources(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
	, m_bClone(false)
{
}

CResources::CResources(const CResources & other)
	: CComponent(other)
	, m_bClone(true)
{
}

HRESULT CResources::Ready_Component()
{
	return S_OK;
}

HRESULT CResources::Update_Component(const _float & fTimeDelta)
{
	return S_OK;
}

void CResources::Free()
{
	CComponent::Free();
}
