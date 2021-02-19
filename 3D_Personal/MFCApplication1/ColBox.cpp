#include "stdafx.h"
#include "ColBox.h"



CColBox::CColBox(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
	, m_iNavID(NOT_FOUND)
	, m_eType(eBoxType::End)
{
}

HRESULT CColBox::Ready_Prototype()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	m_pCollsion = (CColliderBox*)CManagement::Get_Instance()->Clone_Resource(L"Collision_Box", eResourcesID::CollisionBox);
	CGameObject::Add_Component(eComponentID::CColliderBox, m_pTrans);
	m_eRenderID = eRenderID::NoAlpha;
	return S_OK;
}

HRESULT CColBox::Awake_GameObject()
{
	return S_OK;
}

HRESULT CColBox::Ready_GameObject()
{
	return S_OK;
}

_uint CColBox::UpdateGameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);

	return 0;
}

_uint CColBox::LateUpdateGameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);

	return 0;
}

HRESULT CColBox::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pCollsion->Render_Collider(&m_pTrans->Get_World());//  ¼öÁ¤ 

	return S_OK;
}

CGameObject * CColBox::Clone()
{
	return nullptr;
}

void CColBox::Set_Pos(const _vec3 & vPos)
{
	NULL_CHECK(m_pTrans);
	m_pTrans->Set_Position(vPos);
}

void CColBox::Set_Scale(const _vec3 & vScale)
{
	NULL_CHECK(m_pTrans);
	m_pTrans->Set_Scale(vScale.x, vScale.y, vScale.z);
}

_bool CColBox::Peeking(_vec3 vRayPos, _vec3 vRayDir)
{
	_matrix matWorld = m_pTrans->Get_World();
	D3DXMatrixInverse(&matWorld,NULL, &matWorld);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);


	const _vec3*    pVtx = m_pCollsion->Get_VtxData();
	const INDEX16* pIndex = m_pCollsion->Get_IdxData();
	float fU, fV, fDis;

	for (int i = 0; i < 12; ++i) //12Æú¸®°ï °¹¼ö 
	{
		if (D3DXIntersectTri(&pVtx[pIndex[i]._0], &pVtx[pIndex[i]._1]
			, &pVtx[pIndex[i]._2], &vRayPos, &vRayDir, &fU, &fV, &fDis))
		{
			return true;
		}
	}

	return false;
}

CColBox * CColBox::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CColBox* pIns = new CColBox(pDevice);
	if (FAILED(pIns->Ready_GameObject()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}
