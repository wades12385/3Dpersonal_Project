#include "stdafx.h"
#include "ColliBox.h"



ColliBox::ColliBox(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

ColliBox::ColliBox(const ColliBox & other)
	: CGameObject(other)
{
}


HRESULT ColliBox::Ready_Prototype()
{
	return S_OK;
}

HRESULT ColliBox::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	m_pCollider = CCollider::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Collider, m_pCollider);

	//////////////////////////////////////////////////////////////////////////


	m_eRenderID = eRenderID::NoAlpha;
	return S_OK;
}

HRESULT ColliBox::Ready_GameObject()
{
	m_pTrans->Update_Component();
	m_pCollider->Set_BoundType(eBoundType::Box, m_pTrans);
	return S_OK;
}

_uint ColliBox::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint ColliBox::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT ColliBox::RenderGameObject()
{
	m_pCollider->Render_Collider();
	return S_OK;
}

CGameObject * ColliBox::Clone()
{
	return new ColliBox(*this);
}

void ColliBox::Set_Pos(const _vec3 & vPos)
{
	m_pTrans->Set_Position(vPos);
}

void ColliBox::Set_Scale(const _vec3 & vScale)
{

}

ColliBox * ColliBox::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new ColliBox(pDevice);
}

void ColliBox::Free()
{
	CGameObject::Free();
}
