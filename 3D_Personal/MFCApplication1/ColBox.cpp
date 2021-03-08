#include "stdafx.h"
#include "ColBox.h"



CColBox::CColBox(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
	, m_iNavID(NOT_FOUND)
	, m_eType(eBoxType::End)
	, m_bHide(false)
	, m_bTrigger(false)
	, m_bSelect(false)
{
}

HRESULT CColBox::Ready_Prototype()
{

	return S_OK;
}

HRESULT CColBox::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	m_pCollsion = CCollider::Create(m_pDevice);
	m_pCollsion->Set_BoundType(eBoundType::Box, m_pTrans);
	CGameObject::Add_Component(eComponentID::Collider, m_pCollsion);
	m_eRenderID = eRenderID::Priority;
	return S_OK;
}

HRESULT CColBox::Ready_GameObject()
{
	 
	return S_OK;
}

_uint CColBox::Update_GameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);

	return 0;
}

_uint CColBox::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);

	return 0;
}

HRESULT CColBox::RenderGameObject()
{
	//m_pTrans->UpdateWorld();
	m_pCollsion->Render_Collider(false);//  ¼öÁ¤ 

	return S_OK;
}

CGameObject * CColBox::Clone()
{
	return nullptr;
}

void CColBox::Set_Type(eBoxType::eBoxType eType)
{

}

void CColBox::Set_Select(_bool bSelect)
{
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


	return false;
}

CColBox * CColBox::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CColBox* pIns = new CColBox(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CColBox::Free()
{
	CGameObject::Free();
}
