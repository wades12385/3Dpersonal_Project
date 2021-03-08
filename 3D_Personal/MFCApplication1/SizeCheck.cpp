#include "stdafx.h"
#include "SizeCheck.h"



CSizeCheck::CSizeCheck(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CSizeCheck::CSizeCheck(const CSizeCheck & other)
	:CGameObject(other)
{
}

HRESULT CSizeCheck::Ready_Prototype()
{
	return S_OK;
}

HRESULT CSizeCheck::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	m_pCollider = CCollider::Create(m_pDevice);
	m_pTrans->Update_Component();
	m_pCollider->Set_BoundType(eBoundType::Sphere, m_pTrans);
	CGameObject::Add_Component(eComponentID::Collider, m_pCollider);

	m_bHide = false;
	m_fSize = 1.f;
	m_pCollider->Set_BoundSize(m_fSize);
	m_eRenderID = eRenderID::NoAlpha;
	return S_OK;
}

HRESULT CSizeCheck::Ready_GameObject()
{
	return S_OK;
}

_uint CSizeCheck::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CSizeCheck::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CSizeCheck::RenderGameObject()
{
	if(m_bHide == false)
		m_pCollider->Render_Collider();
	return S_OK;
}

CGameObject * CSizeCheck::Clone()
{
	return new CSizeCheck(*this);
}

CSizeCheck* CSizeCheck::Create(LPDIRECT3DDEVICE9 pDevice)
{
	
	return new CSizeCheck(pDevice);
}

void CSizeCheck::Set_ColliderSize(_float fSize)
{
	m_fSize = fSize; 
	m_pCollider->Set_BoundSize(m_fSize);
}

void CSizeCheck::Free()
{
	CGameObject::Free();
}
