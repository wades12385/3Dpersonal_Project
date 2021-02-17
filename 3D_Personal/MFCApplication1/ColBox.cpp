#include "stdafx.h"
#include "ColBox.h"



CColBox::CColBox(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

HRESULT CColBox::Ready_Prototype()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
 	m_pCollsion = CColliderBox::CreateToDefault(m_pDevice);
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
	m_pCollsion->Render_Collider(&m_pTrans->GetWorld());//  ¼öÁ¤ 

	return S_OK;
}

CGameObject * CColBox::Clone()
{
	return nullptr;
}

CColBox * CColBox::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pComTag)
{
	CColBox* pIns = new CColBox(pDevice);
	if (FAILED(pIns->Ready_GameObject()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}
