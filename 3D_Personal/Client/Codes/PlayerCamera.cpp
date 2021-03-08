#include "stdafx.h"
#include "PlayerCamera.h"


CPlayerCamera::CPlayerCamera(LPDIRECT3DDEVICE9 pDevice)
	:CCamera(pDevice)
{
}

CPlayerCamera::CPlayerCamera(const CPlayerCamera & other)
	:CCamera(other)
{
}

HRESULT CPlayerCamera::Ready_Prototype()
{
	return S_OK;
}

HRESULT CPlayerCamera::Awake_GameObject()
{
	m_pTransCom = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTransCom);


	//////////////////////////////////////////////////////////////////////////
	m_fCameraAngle = 45.f;

	m_tCameraDesc.fAspect = WINCX / float(WINCY);
	m_tCameraDesc.fFar = 500.f;
	m_tCameraDesc.fNear = 0.1f;
	m_tCameraDesc.fFovY = D3DXToRadian(90.f);

	m_tCameraDesc.vEye = _vec3(0, 5, -5);
	m_tCameraDesc.vAt = vZero;
	m_tCameraDesc.vUp = _vec3(0, 1, 0);

	D3DXMatrixPerspectiveFovLH(&m_tCameraDesc.matProj, m_tCameraDesc.fFovY,
		m_tCameraDesc.fAspect, m_tCameraDesc.fNear, m_tCameraDesc.fFar);
	if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &m_tCameraDesc.matProj)))
		return E_FAIL;

	m_eRenderID = eRenderID::UI;

	return S_OK;
}

HRESULT CPlayerCamera::Ready_GameObject()
{
	CCamera::Ready_GameObject();

	return S_OK;
}

_uint CPlayerCamera::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CPlayerCamera::LateUpdate_GameObject(const _float & fDeltaTime)
{
//	_matrix matview = m_pTransCom->Get_World();
//	D3DXMatrixInverse(&matview, 0, &matview);
//	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matview)))
//		return E_FAIL;
//



	return CCamera::LateUpdate_GameObject(fDeltaTime);
}

HRESULT CPlayerCamera::RenderGameObject()
{
	return S_OK;
}

void CPlayerCamera::Update_Move(CTransform* ptrans, CCollider* pCollidere)
{

	//반지름 + 스케일의 1.5배 
	 m_fCameraDis = (ptrans->Get_Sacle().x * 1.5f) + pCollidere->Get_Bound().fRadius;
	_matrix matAngle;
	m_tCameraDesc.vAt = ptrans->Get_Position();
	m_tCameraDesc.vEye = - (ptrans->Get_Look() * m_fCameraDis);
	D3DXMatrixRotationAxis(&matAngle, &ptrans->Get_Right(), D3DXToRadian(m_fCameraAngle));
	D3DXVec3TransformNormal(&m_tCameraDesc.vEye, &m_tCameraDesc.vEye, &matAngle);
	//m_tCameraDesc.vEye.y += fCameraH;
	m_tCameraDesc.vEye += ptrans->Get_Position();
}

CPlayerCamera * CPlayerCamera::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayerCamera* pIns = new CPlayerCamera(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

CGameObject * CPlayerCamera::Clone()
{
	return new CPlayerCamera(*this);
}

void CPlayerCamera::Free()
{
	CCamera::Free();
}
