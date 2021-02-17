#include "ColliderBox.h"


USING(Engine)
CColliderBox::CColliderBox(LPDIRECT3DDEVICE9 pDevice)
	:CVIBuffer(pDevice)
	,m_vMin(vZero)
	,m_vMax(vZero)
	,m_bCollision(false)
	, m_pIdxData(nullptr)
	,m_pVtxData(nullptr)
{
	D3DXMatrixIdentity(&m_matColMatrix);
	ZeroMemory(m_pTexture, sizeof(LPDIRECT3DTEXTURE9)*End);
}

CColliderBox::CColliderBox(const CColliderBox & other)
	:CVIBuffer(other)
	,m_vMax(other.m_vMax)
	,m_vMin(other.m_vMin)
	,m_bCollision(false)
	,m_matColMatrix(other.m_matColMatrix)
	, m_pIdxData(nullptr)
	, m_pVtxData(nullptr)
{
	for (_ulong i = 0; i < End; ++i)
	{
		m_pTexture[i] = other.m_pTexture[i];
		m_pTexture[i]->AddRef();
	}

}

HRESULT CColliderBox::Ready_Component()
{
	return S_OK;
}

HRESULT CColliderBox::Ready_CreateToMesh(const _vec3* pVtxs, const _ulong& dwVtxCnt, const _ulong& dwStride)
{
	D3DXComputeBoundingBox(pVtxs, dwVtxCnt, sizeof(_vec3), &m_vMin, &m_vMax);
	// D3DXComputeBoundingSphere();
	// D3DXCreateBox();

	
	m_iVertexCount = 8;
	m_iTriCount = 12;
	m_iVertexSize = sizeof(VTXCUBE);
	m_iIdxSize = sizeof(INDEX16);
	m_dwFVF = FVF_CUBE;
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::Ready_Component(), E_FAIL);

	VTXCUBE*		pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	// 전면
	pVertex[0].vPosition = _vec3(m_vMin.x, m_vMax.y, m_vMin.z);
	pVertex[0].vUV = pVertex[0].vPosition;

	pVertex[1].vPosition = _vec3(m_vMax.x, m_vMax.y, m_vMin.z);
	pVertex[1].vUV = pVertex[1].vPosition;

	pVertex[2].vPosition = _vec3(m_vMax.x, m_vMin.y, m_vMin.z);
	pVertex[2].vUV = pVertex[2].vPosition;

	pVertex[3].vPosition = _vec3(m_vMin.x, m_vMin.y, m_vMin.z);
	pVertex[3].vUV = pVertex[3].vPosition;

	// 후면
	pVertex[4].vPosition = _vec3(m_vMin.x, m_vMax.y, m_vMax.z);
	pVertex[4].vUV = pVertex[4].vPosition;

	pVertex[5].vPosition = _vec3(m_vMax.x, m_vMax.y, m_vMax.z);
	pVertex[5].vUV = pVertex[5].vPosition;

	pVertex[6].vPosition = _vec3(m_vMax.x, m_vMin.y, m_vMax.z);
	pVertex[6].vUV = pVertex[6].vPosition;

	pVertex[7].vPosition = _vec3(m_vMin.x, m_vMin.y, m_vMax.z);
	pVertex[7].vUV = pVertex[7].vPosition;

	m_pVtxData = new _vec3[m_iVertexCount];
	for (int i = 0; i < m_iVertexCount; ++i)
		m_pVtxData[i] = pVertex[i].vPosition;

	m_pVB->Unlock();



	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIdxData = new INDEX16[m_iTriCount];
	memcpy(m_pIdxData, pIndex, sizeof(INDEX16) * m_iTriCount);


	m_pIB->Unlock();

	for (_ulong i = 0; i < End; ++i)
	{
		m_pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

		D3DLOCKED_RECT		LockRect;
		ZeroMemory(&LockRect, sizeof(D3DLOCKED_RECT));
		m_pTexture[i]->LockRect(0, &LockRect, NULL, 0);
		*((_ulong*)LockRect.pBits) = D3DXCOLOR(1.f * i, 1.f * (1.f - i), 0.f, 1.f);
		m_pTexture[i]->UnlockRect(0);
	}

	return S_OK;
}

HRESULT CColliderBox::Ready_CreateToDefault()
{

	m_iVertexCount = 8;
	m_iTriCount = 12;
	m_iVertexSize = sizeof(VTXCUBE);
	m_iIdxSize = sizeof(INDEX16);
	m_dwFVF = FVF_CUBE;
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::Ready_Component(), E_FAIL);

	VTXCUBE*		pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, NULL);

	// 전면
	pVertex[0].vPosition = _vec3(-0.5f, 0.5f, -0.5f);
	pVertex[0].vUV = pVertex[0].vPosition;

	pVertex[1].vPosition = _vec3(0.5f, 0.5f, -0.5f);
	pVertex[1].vUV = pVertex[1].vPosition;

	pVertex[2].vPosition = _vec3(0.5f, -0.5f, -0.5f);
	pVertex[2].vUV = pVertex[2].vPosition;

	pVertex[3].vPosition = _vec3(-0.5f, -0.5f, -0.5f);
	pVertex[3].vUV = pVertex[3].vPosition;

	// 후면
	pVertex[4].vPosition = _vec3(-0.5f, 0.5f, 0.5f);
	pVertex[4].vUV = pVertex[4].vPosition;

	pVertex[5].vPosition = _vec3(0.5f, 0.5f, 0.5f);
	pVertex[5].vUV = pVertex[5].vPosition;

	pVertex[6].vPosition = _vec3(0.5f, -0.5f, 0.5f);
	pVertex[6].vUV = pVertex[6].vPosition;

	pVertex[7].vPosition = _vec3(-0.5f, -0.5f, 0.5f);
	pVertex[7].vUV = pVertex[7].vPosition;

	m_pVtxData = new _vec3[m_iVertexCount];
	for (int i = 0; i < m_iVertexCount; ++i)
		m_pVtxData[i] = pVertex[i].vPosition;

	m_pVB->Unlock();

	m_vMax = _vec3(0.5f, 0.5f, 0.5f);
	m_vMin = _vec3(-0.5f, -0.5f, -0.5f);



	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();


	for (_ulong i = 0; i < End; ++i)
	{
		m_pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

		D3DLOCKED_RECT		LockRect;
		ZeroMemory(&LockRect, sizeof(D3DLOCKED_RECT));
		m_pTexture[i]->LockRect(0, &LockRect, NULL, 0);
		*((_ulong*)LockRect.pBits) = D3DXCOLOR(1.f * i, 1.f * (1.f - i), 0.f, 1.f);
		m_pTexture[i]->UnlockRect(0);
	}

	return S_OK;
}

void CColliderBox::Render_Collider(const _matrix * pColliderMatrix)
{
	m_pDevice->SetTransform(D3DTS_WORLD, pColliderMatrix);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	if(m_bCollision)
		m_pDevice->SetTexture(0, m_pTexture[true]);
	else
		m_pDevice->SetTexture(0, m_pTexture[false]);

	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VTXCUBE));
	m_pDevice->SetFVF(FVF_CUBE);
	m_pDevice->SetIndices(m_pIB);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


CComponent * CColliderBox::Clone()
{
	return new CColliderBox(*this);
}

CColliderBox * CColliderBox::CreateToMesh(LPDIRECT3DDEVICE9 pDevice, const _vec3 * pVtxs, const _ulong & dwVtxCnt, const _ulong & dwStride)
{
	CColliderBox* pIns = new CColliderBox(pDevice);

	if (FAILED(pIns->Ready_CreateToMesh(pVtxs, dwVtxCnt, dwStride)))
	{
		SafeRelease(pIns);
		return nullptr;
	}

	return pIns;
}

CColliderBox * CColliderBox::CreateToDefault(LPDIRECT3DDEVICE9 pDevice)
{
	CColliderBox* pIns = new CColliderBox(pDevice);

	if (FAILED(pIns->Ready_CreateToDefault()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CColliderBox::Free()
{
	CVIBuffer::Free();
	SafeDeleteArray(m_pVtxData);
	SafeDeleteArray(m_pIdxData);

	for (_ulong i = 0; i < End; ++i)
		SafeRelease(m_pTexture[i]);
}