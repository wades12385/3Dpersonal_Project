#include "stdafx.h"
#include "MfcStaticItem.h"
CMfcStaticItem::CMfcStaticItem(LPDIRECT3DDEVICE9 pDevice)
	:CItem(pDevice)
	,m_bSelect(false)
{
}

CMfcStaticItem::CMfcStaticItem(const CMfcStaticItem & other)
	:CItem(other)
{
}

HRESULT CMfcStaticItem::Ready_Prototype()
{
	return S_OK;
}

HRESULT CMfcStaticItem::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	m_pCollider = CCollider::Create(m_pDevice);
	m_pMesh = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(m_tObjDecs.wstrTag.c_str(), 
		eResourcesID::StaticMesh);

	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pMesh);
	CGameObject::Add_Component(eComponentID::Collider, m_pCollider);

	m_eRenderID = eRenderID::NoAlpha;
	m_bSelect = false;
	return S_OK;
}

HRESULT CMfcStaticItem::Ready_GameObject()
{
	
	m_pTrans->Set_Scale(m_tObjDecs.fSacle, m_tObjDecs.fSacle, m_tObjDecs.fSacle);
	m_pTrans->Update_Component();
	m_pCollider->Set_BoundTypeFitMesh(eBoundType::Box, m_pTrans, m_pMesh);
	return S_OK;
}

_uint CMfcStaticItem::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CMfcStaticItem::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CMfcStaticItem::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pMesh->Render_Meshes();
	m_pCollider->Render_Collider(m_bSelect);
	return S_OK;
}

CMfcStaticItem * CMfcStaticItem::Create(LPDIRECT3DDEVICE9 pDevice, const _int& iTableID)
{
	CMfcStaticItem* pIns = new CMfcStaticItem(pDevice);

	pIns->Get_ObjDescMod() = (*CManagement::Get_Instance()->Get_DataTableVector())[iTableID];

	return pIns;
}

CGameObject * CMfcStaticItem::Clone()
{
	return new CMfcStaticItem(*this);
}

void CMfcStaticItem::Set_Sacle(_float fScale)
{
	m_pTrans->Set_Scale(fScale, fScale, fScale);

	_float fPreHeight = m_pCollider->Get_Bound().fHeight * 0.5f;

	m_tObjDecs.fSacle = fScale;
	m_pTrans->Update_Component();

	m_pCollider->Set_BoundTypeFitMesh(eBoundType::Box, m_pTrans, m_pMesh);
	_float fCurHeight = m_pCollider->Get_Bound().fHeight * 0.5f;
	_vec3 vPostiton = m_pTrans->Get_Position();
	vPostiton.y += fCurHeight - fPreHeight;
	m_pTrans->Set_Position(vPostiton);
	m_pTrans->Update_Component();
}

void CMfcStaticItem::Free()
{
	CItem::Free();
}
