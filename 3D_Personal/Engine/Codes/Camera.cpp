#include "Camera.h"


USING(Engine)
CCamera::CCamera(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
	ZeroMemory(&m_tCameraDesc, sizeof(CAMERA_DESC));
	D3DXMatrixIdentity(&m_tCameraDesc.matView);
	D3DXMatrixIdentity(&m_tCameraDesc.matProj);
}

CCamera::CCamera(const CCamera & _rOther)
	:CGameObject(_rOther)
	, m_tCameraDesc(_rOther.m_tCameraDesc)
{
}
HRESULT CCamera::Ready_GameObject()
{
	D3DXMatrixLookAtLH(&m_tCameraDesc.matView, &m_tCameraDesc.vEye,
		&m_tCameraDesc.vAt, &m_tCameraDesc.vUp);

	D3DXMatrixPerspectiveFovLH(&m_tCameraDesc.matProj, m_tCameraDesc.fFovY,
		m_tCameraDesc.fAspect, m_tCameraDesc.fNear, m_tCameraDesc.fFar);

	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &m_tCameraDesc.matView)))
		return 0;

	if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &m_tCameraDesc.matProj)))
		return 0;

	return S_OK;
}
_uint CCamera::LateUpdate_GameObject(const _float & fDeltaTime)
{
	D3DXMatrixLookAtLH(&m_tCameraDesc.matView, &m_tCameraDesc.vEye,
		&m_tCameraDesc.vAt, &m_tCameraDesc.vUp);

	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &m_tCameraDesc.matView)))
		return 0;

	return 0;
}

void CCamera::Free()
{
	CGameObject::Free();
}



