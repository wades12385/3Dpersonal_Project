#include "Collider.h"
#include "StaticMesh.h"
#include "Resource_Manager.h"
#include "Transform.h"

USING(Engine)
CCollider::CCollider(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
	, m_pColMesh(nullptr)
{
	ZeroMemory(m_pTexture, sizeof(LPDIRECT3DTEXTURE9)*End);
	ZeroMemory(&m_tBound, sizeof(BOUND));
}

HRESULT CCollider::Ready_Component()
{
	for (_ulong i = 0; i < End; ++i)
	{
		m_pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

		D3DLOCKED_RECT		LockRect;
		ZeroMemory(&LockRect, sizeof(D3DLOCKED_RECT));
		m_pTexture[i]->LockRect(0, &LockRect, NULL, 0);
		*((_ulong*)LockRect.pBits) = D3DXCOLOR(0, 1.f * (1.f - i), 1.f * i, 1.f);
		m_pTexture[i]->UnlockRect(0);
	}

	m_pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pSelectTexture, NULL);
	D3DLOCKED_RECT		LockRect;
	ZeroMemory(&LockRect, sizeof(D3DLOCKED_RECT));
	m_pSelectTexture->LockRect(0, &LockRect, NULL, 0);
	*((_ulong*)LockRect.pBits) = D3DXCOLOR(1.f, 0, 0, 1.f);
	m_pSelectTexture->UnlockRect(0);
	return S_OK;
}



void CCollider::Render_Collider(const _bool& bSelect)
{
	D3DXVECTOR3 vPosition = m_tBound.vCenter + m_pTrans->Get_PositionWorld();
	D3DXMATRIX matScale, matTrans, matWorld;


	if (eBoundType::Box == m_eBoundType)
		D3DXMatrixScaling(&matScale, m_tBound.fLength, m_tBound.fHeight, m_tBound.fDepth);
	else
		D3DXMatrixScaling(&matScale, m_tBound.fRadius, m_tBound.fRadius, m_tBound.fRadius);

	D3DXMatrixTranslation(&matTrans, vPosition.x, vPosition.y, vPosition.z);
	matWorld = matScale * matTrans;
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	if (bSelect)
	{
		m_pDevice->SetTexture(0, m_pSelectTexture);
	}
	else
	{
		if (m_bTriger)
			m_pDevice->SetTexture(0, m_pTexture[Trigger]);
		else
			m_pDevice->SetTexture(0, m_pTexture[Collision]);
	}

	m_pColMesh->Render_Meshes();
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

_bool CCollider::RayPeeking(_vec2 pt)
{
	_vec3	 vViewPortPt,vRayPos,vRayDir, vPos;
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	_matrix matProj, matView,matworld;
	LPD3DXBUFFER ppHits = nullptr;
	DWORD	pCountHit = 0;
	DWORD   dwIndex = 0;
	BOOL	bHit = false;

	m_pDevice->GetViewport(&ViewPort);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);

	// to Proj
	vViewPortPt.x = pt.x / (ViewPort.Width * 0.5f) - 1.f;
	vViewPortPt.y = pt.y / -(ViewPort.Height * 0.5f) + 1.f;
	vViewPortPt.z = 0.1f;


	// To Veiw
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vViewPortPt, &vViewPortPt, &matProj);


	vRayPos = _vec3(0.f, 0.f, 0.f);
	vRayDir = vViewPortPt - vRayPos;

	// To world
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);
	vPos = m_pTrans->Get_PositionWorld();
	D3DXMatrixIdentity(&matworld);

	matworld._11 = m_tBound.fLength;
	matworld._22 = m_tBound.fHeight;
	matworld._33 = m_tBound.fDepth;
	matworld._41 = vPos.x;
	matworld._42 = vPos.y;
	matworld._43 = vPos.z;

	D3DXMatrixInverse(&matworld, NULL, &matworld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matworld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matworld);
	_float	fU, fV, fDist;

	D3DXIntersect(m_pColMesh->Get_Mesh(),
		&vRayPos, &vRayDir, &bHit, &dwIndex, &fU, &fV, &fDist, &ppHits, &pCountHit);

	return bHit == TRUE;
}

void CCollider::Set_BoundType(eBoundType::eBoundType eType, CTransform* pTrans)
{
	if (eType == eBoundType::Box)
	{
		if (m_pColMesh == nullptr)
			m_pColMesh = (CStaticMesh*)CResource_Manager::Get_Instance()->Clone(L"Cube", eResourcesID::StaticMesh);
		D3DXComputeBoundingBox(m_pColMesh->Get_VtxPos(), m_pColMesh->Get_VtxCnt(), sizeof(D3DXVECTOR3), &(m_tBound.vMin), &(m_tBound.vMax));
		m_tBound.vCenter = (m_tBound.vMax + m_tBound.vMin) * 0.5f;
		m_tBound.fLength = m_tBound.vMax.x - m_tBound.vMin.x;
		m_tBound.fHeight = m_tBound.vMax.y - m_tBound.vMin.y;
		m_tBound.fDepth = m_tBound.vMax.z - m_tBound.vMin.z;

	}
	else
	{
		if (m_pColMesh == nullptr)
			m_pColMesh = (CStaticMesh*)CResource_Manager::Get_Instance()->Clone(L"Sphere", eResourcesID::StaticMesh);
		D3DXComputeBoundingSphere(m_pColMesh->Get_VtxPos(), m_pColMesh->Get_VtxCnt(), sizeof(D3DXVECTOR3), &(m_tBound.vCenter), &(m_tBound.fRadius));
	}

	m_eBoundType = eType;
	m_pTrans = pTrans;
}

void CCollider::Set_BoundTypeFitMesh(eBoundType::eBoundType eType, CTransform * pTrans, CStaticMesh * pColliMesh)
{
	NULL_CHECK(pColliMesh);

	_vec3* pVtxs = new _vec3[pColliMesh->Get_VtxCnt()];

	_matrix matWorld;

	D3DXMatrixScaling(&matWorld, pTrans->Get_Sacle().x, pTrans->Get_Sacle().y, pTrans->Get_Sacle().z);
	for (_uint i = 0; i < pColliMesh->Get_VtxCnt(); ++i)
		D3DXVec3TransformCoord(&pVtxs[i], &pColliMesh->Get_VtxPos()[i], &matWorld);

	//for (_uint i = 0; i < pColliMesh->Get_VtxCnt(); ++i)
	//	D3DXVec3TransformCoord(&pVtxs[i], &pColliMesh->Get_VtxPos()[i], &pTrans->Get_World());

	if (eBoundType::Box == eType)
	{
		if(m_pColMesh == nullptr)
			m_pColMesh = (CStaticMesh*)CResource_Manager::Get_Instance()->Clone(L"Cube", eResourcesID::StaticMesh);
		D3DXComputeBoundingBox(pVtxs, pColliMesh->Get_VtxCnt(), sizeof(D3DXVECTOR3), &(m_tBound.vMin), &(m_tBound.vMax));
		m_tBound.vCenter = (m_tBound.vMax + m_tBound.vMin) * 0.5f;
		m_tBound.fLength = m_tBound.vMax.x - m_tBound.vMin.x;
		m_tBound.fHeight = m_tBound.vMax.y - m_tBound.vMin.y;
		m_tBound.fDepth = m_tBound.vMax.z - m_tBound.vMin.z;
	}
	else
	{
		if (m_pColMesh == nullptr)
			m_pColMesh = (CStaticMesh*)CResource_Manager::Get_Instance()->Clone(L"Sphere", eResourcesID::StaticMesh);
		D3DXComputeBoundingSphere(pVtxs, pColliMesh->Get_VtxCnt(), sizeof(D3DXVECTOR3), &(m_tBound.vCenter), &(m_tBound.fRadius));
	}
	SafeDeleteArray(pVtxs);
	m_eBoundType = eType;
	m_pTrans = pTrans;
}

BOUND CCollider::Get_Bound()
{
	BOUND tBound;

	if (eBoundType::Box == m_eBoundType)
	{
		tBound = m_tBound;

		tBound.vCenter = m_tBound.vCenter + m_pTrans->Get_Position();
		tBound.vMin += m_pTrans->Get_Position();
		tBound.vMax += m_pTrans->Get_Position();
	}
	else
	{
		tBound = m_tBound;
		tBound.vCenter = m_pTrans->Get_Position();
	}



	return tBound;
}

void CCollider::Set_BoundSize(const _float & fRadius)
{
	if (m_eBoundType != eBoundType::Sphere)
		return;

	m_tBound.fRadius = fRadius * 0.0268f;
}

void CCollider::Set_BoundSize(const _vec3 vScale)
{
	if (m_eBoundType != eBoundType::Box)
		return;

	m_tBound.fLength = vScale.x;
	m_tBound.fHeight = vScale.y;
	m_tBound.fDepth = vScale.z;
}

CCollider * CCollider::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CCollider* pIns = new CCollider(pDevice);
	if (FAILED(pIns->Ready_Component()))
	{
		SafeRelease(pIns);
		return nullptr;
	}

	return pIns;
}

void CCollider::Free()
{

	for (int i = 0; i < 2; ++i)
		SafeRelease(m_pTexture[i]);

	SafeRelease(m_pSelectTexture);
	SafeRelease(m_pColMesh);


	CComponent::Free();
}

HRESULT CCollider::Update_Component(const _float & fTimeDelta )
{
	return S_OK;
}
