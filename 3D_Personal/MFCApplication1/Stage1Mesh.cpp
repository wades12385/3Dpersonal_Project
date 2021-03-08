#include "stdafx.h"
#include "Stage1Mesh.h"



USING(Engine)
CStage1Mesh::CStage1Mesh(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CStage1Mesh::CStage1Mesh(const CStage1Mesh & other)
	:CGameObject(other)
{
	lstrcpy(m_szMeshTag, other.m_szMeshTag);
}

HRESULT CStage1Mesh::Ready_Prototype()
{
	return S_OK;
}

HRESULT CStage1Mesh::Awake_GameObject()
{
	//Trans
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	//Mesh
	m_pMeshCom = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(m_szMeshTag,
		eResourcesID::StaticMesh);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pMeshCom);

	m_eRenderID = eRenderID::NoAlpha;
	return S_OK;
}

HRESULT CStage1Mesh::Ready_GameObject()
{
	return S_OK;
}

_uint CStage1Mesh::Update_GameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);
	return _uint();
}

_uint CStage1Mesh::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CStage1Mesh::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pMeshCom->Render_Meshes();
	return S_OK;
}

CGameObject * CStage1Mesh::Clone()
{
	return new CStage1Mesh(*this);
}

CStage1Mesh * CStage1Mesh::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pComTag)
{
	CStage1Mesh* pIns = new CStage1Mesh(pDevice);
	pIns->Set_Tag(pComTag);
	pIns->Ready_Prototype();
	return pIns;
}

void CStage1Mesh::Free()
{
	CGameObject::Free();
}
