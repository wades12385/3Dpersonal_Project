#include "Mesh.h"


USING(Engine)
CMesh::CMesh(LPDIRECT3DDEVICE9 pDevice)
	:CResources(pDevice)
{
}

CMesh::CMesh(const CMesh & other)
	: CResources(other)
{
}

void CMesh::Free()
{
	CResources::Free();
}

