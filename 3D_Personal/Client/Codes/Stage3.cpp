#include "stdafx.h"
#include "Stage3.h"


CStage3::CStage3(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CStage3::CStage3(const CStage3 & other)
	:CGameObject(other)
{
}

HRESULT CStage3::Ready_Prototype()
{
	return S_OK;
}

HRESULT CStage3::Awake_GameObject()
{
	//Trans
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	//Mesh
	m_pMeshCom = (CStaticMesh*)CManagement::Get_Instance()->Clone_Resource(L"StaticMesh_Stage1",
		eResourcesID::StaticMesh);
	CGameObject::Add_Component(eComponentID::StaticMesh, m_pMeshCom);
	m_eRenderID = eRenderID::NoAlpha;

	return S_OK;
}

HRESULT CStage3::Ready_GameObject()
{
	return S_OK;
}

_uint CStage3::Update_GameObject(const _float & fDeltaTime)
{
	m_pTrans->Update_Component(fDeltaTime);

	return _uint();
}

_uint CStage3::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CStage3::RenderGameObject()
{
	m_pTrans->UpdateWorld();
	m_pMeshCom->Render_Meshes();
	return S_OK;
}

CGameObject * CStage3::Clone()
{
	return new CStage3(*this);

}

CStage3 * CStage3::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage3* pIns = new CStage3(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CStage3::Free()
{
	CGameObject::Free();
}
