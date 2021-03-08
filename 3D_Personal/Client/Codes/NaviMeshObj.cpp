#include "stdafx.h"
#include "NaviMeshObj.h"



CNaviMeshObj::CNaviMeshObj(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CNaviMeshObj::CNaviMeshObj(const CNaviMeshObj & other)
	: CGameObject(other)
{
}

HRESULT CNaviMeshObj::Ready_Prototype()
{
	return S_OK;
}

HRESULT CNaviMeshObj::Awake_GameObject()
{
	m_pNaviMeshCom = (CNaviMesh*)CManagement::Get_Instance()->Clone_Resource(m_szBuffer, eResourcesID::NaviMesh);
	CGameObject::Add_Component(eComponentID::NaviMesh, m_pNaviMeshCom);

	m_eRenderID = eRenderID::NoAlpha;

	return S_OK;
}

HRESULT CNaviMeshObj::Ready_GameObject()
{
	return S_OK;
}

_uint CNaviMeshObj::Update_GameObject(const _float & fDeltaTime)
{
	if (KeyDown(DIK_F1))
		m_bShow = !m_bShow;

	return _uint();
}

_uint CNaviMeshObj::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CNaviMeshObj::RenderGameObject()
{
	if (m_bShow == false)
		return S_OK;
	m_pDevice->SetTexture(0, nullptr);
	m_pNaviMeshCom->Render_Meshes();
	return S_OK;
}

void CNaviMeshObj::Set_NaviTage(const _tchar * pTag)
{
	lstrcpy(m_szBuffer, pTag);
}

CNaviMeshObj * CNaviMeshObj::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CNaviMeshObj(pDevice);
}

CGameObject * CNaviMeshObj::Clone()
{
	return new CNaviMeshObj(*this);
}

void CNaviMeshObj::Free()
{
	CGameObject::Free();
}
