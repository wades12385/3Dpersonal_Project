#include "stdafx.h"
#include "LogoImg.h"



CLogoImg::CLogoImg(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

HRESULT CLogoImg::Ready_Prototype()
{
	return S_OK;
}

HRESULT CLogoImg::Awake_GameObject()
{
	m_pTransCom = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTransCom);
	m_pTexCom = (CTexture*)CManagement::Get_Instance()->Clone_Resource(L"LogoImg", eResourcesID::Texture);
	CGameObject::Add_Component(eComponentID::Texture, m_pTexCom);
	m_pBufferCom = (CRectBuffer*)CManagement::Get_Instance()->Clone_Resource(L"Rect_Buffer", eResourcesID::RectBuffer);
	CGameObject::Add_Component(eComponentID::VIBuffer, m_pBufferCom);


	m_eRenderID = eRenderID::NoAlpha;
	return S_OK;
}

HRESULT CLogoImg::Ready_GameObject()
{
	m_pTransCom->Set_Scale(2.f, 2.f, 1.f);


	m_pTransCom->Update_Component(0.f);
	return S_OK;
}

_uint CLogoImg::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CLogoImg::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CLogoImg::RenderGameObject()
{
	m_pTransCom->UpdateWorld();
	m_pTexCom->Set_Texture();
	m_pBufferCom->Render_VIBuffer();
	return S_OK;
}

CGameObject * CLogoImg::Clone()
{
	return new CLogoImg(*this);
}

CLogoImg * CLogoImg::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogoImg* pIns = new CLogoImg(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CLogoImg::Free()
{
	CGameObject::Free();
}
