#include "stdafx.h"
#include "PlayerCore.h"




CPlayerCore::CPlayerCore(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CPlayerCore::CPlayerCore(const CPlayerCore & other)
	:CGameObject(other)
{
}

HRESULT CPlayerCore::Ready_Prototype()
{
	return S_OK;
}

HRESULT CPlayerCore::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	//m_pColliter = CColliderBox::CreateToMesh(m_pDevice,);
	//CGameObject::Add_Component(eComponentID::CColliderBox, m_pCollider);
	m_pStaticMesh = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(L"Core_1", eResourcesID::StaticMesh);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pStaticMesh);

	//////////////////////////////////////////////////////////////////////////
	m_pTrans->Set_Scale(10, 10, 10);
	m_pTrans->Update_Component();
	m_fMoveSpeed = 2.f;
	m_fRotSpeed = 180.f;
	m_eRenderID = eRenderID::NoAlpha;
	D3DXMatrixIdentity(&m_matRot);

	return S_OK;
}

HRESULT CPlayerCore::Ready_GameObject()
{
	m_pTrans->UpdateWorld();
	return S_OK;
}

_uint CPlayerCore::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CPlayerCore::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CPlayerCore::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pStaticMesh->Render_Meshes();
	return S_OK;
}

void CPlayerCore::Update_CoreTrans(const _vec3& vAxis, const _float& fAngle)
{

	_matrix matScale, matRot, matTrans , matworld;

	_vec3 vScale = m_pTrans->Get_Sacle();
	_vec3 vPos = m_pTrans->Get_Position();
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationAxis(&matRot, &vAxis, D3DXToRadian(fAngle));
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

	m_matRot *= matRot;
	matworld = matScale * m_matRot * matTrans;
	m_pTrans->Set_World(matworld);
}

CPlayerCore * CPlayerCore::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayerCore* pIns = new CPlayerCore(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

CGameObject * CPlayerCore::Clone()
{
	return new CPlayerCore(*this);
}

void CPlayerCore::Free()
{
	CGameObject::Free();
}
