#include "Resource.h"

USING(Engine)

CResource::CResource(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
{
}

CResource::CResource(const CResource & other)
	: CComponent(other)
{
}
CResource::~CResource()
{
}
void CResource::Free()
{
	CComponent::Free();
}
