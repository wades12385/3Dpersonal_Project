#include "stdafx.h"
#include "ToolCamera.h"


CToolCamera::CToolCamera(LPDIRECT3DDEVICE9 pDevice)
	:CCamera(pDevice)
	,m_bFix(false)
{
}

CToolCamera::CToolCamera(const CToolCamera & other)
	:CCamera(other)
	,m_bFix(other.m_bFix)
	,m_fSpeed(other.m_fSpeed)
	,m_fAngleSpeed(other.m_fAngleSpeed)
{
}

HRESULT CToolCamera::Ready_Prototype()
{
	m_tCameraDesc.fAspect = _float(WINCX) / WINCY;
	m_tCameraDesc.fFar = 500.f;
	m_tCameraDesc.fNear = 0.1f;
	m_tCameraDesc.vEye = _vec3(0, 5, -5);
	m_tCameraDesc.vAt = vZero;
	m_tCameraDesc.vUp = _vec3(0, 1, 0);
	m_tCameraDesc.fFovY = D3DXToRadian(90);
	m_fSpeed = 12.f;
	m_fAngleSpeed = 10.f;
	return S_OK;
}

HRESULT CToolCamera::Awake_GameObject()
{
	return S_OK;
}

HRESULT CToolCamera::Ready_GameObject()
{
	CCamera::Ready_GameObject();
	return S_OK;
}

_uint CToolCamera::Update_GameObject(const _float & fDeltaTime)
{
	Move(fDeltaTime);
	return _uint();
}

_uint CToolCamera::LateUpdate_GameObject(const _float & fDeltaTime)
{

	return CCamera::LateUpdate_GameObject(fDeltaTime);
}


HRESULT CToolCamera::RenderGameObject()
{
	return S_OK;
}

CToolCamera * CToolCamera::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CToolCamera* pIns = new CToolCamera(pDevice);
	pIns->Ready_Prototype();
	return pIns;
}

CGameObject * CToolCamera::Clone()
{
	return new CToolCamera(*this);
}

void CToolCamera::Move(const _float fDeltaTime)
{
	_matrix		matCamWorld;
	D3DXMatrixInverse(&matCamWorld, NULL, &m_tCameraDesc.matView);

	if (KeyDown(DIK_LSHIFT))
		m_bFix = !m_bFix;

	if (!m_bFix)
		return;

	if (KeyPress(DIK_W))
	{
		_vec3	vLook;
		memcpy(&vLook, &matCamWorld.m[2][0], sizeof(_vec3));

		_vec3	vLength = *D3DXVec3Normalize(&vLook, &vLook) * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye += vLength;
		m_tCameraDesc.vAt += vLength;
	}

	if (KeyPress(DIK_S))
	{
		_vec3	vLook;
		memcpy(&vLook, &matCamWorld.m[2][0], sizeof(_vec3));

		_vec3	vLength = *D3DXVec3Normalize(&vLook, &vLook) * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye -= vLength;
		m_tCameraDesc.vAt -= vLength;
	}

	if (KeyPress(DIK_D))
	{
		_vec3	vRight;
		memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

		_vec3	vLength = *D3DXVec3Normalize(&vRight, &vRight) * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye += vLength;
		m_tCameraDesc.vAt += vLength;
	}

	if (KeyPress(DIK_A))
	{
		_vec3	vRight;
		memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

		_vec3	vLength = *D3DXVec3Normalize(&vRight, &vRight) * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye -= vLength;
		m_tCameraDesc.vAt -= vLength;
	}

	//

	if (KeyPress(DIK_R))
	{
		_vec3	vLength =  _vec3(0,1,0) * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye += vLength;
		m_tCameraDesc.vAt += vLength;
	}
	if (KeyPress(DIK_F))
	{
		_vec3	vLength = _vec3(0, 1, 0)  * m_fSpeed * fDeltaTime;

		m_tCameraDesc.vEye -= vLength;
		m_tCameraDesc.vAt -= vLength;
	}
	_long	dwMouseMove = 0;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
	{
		_vec3		vRight;
		memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

		_vec3		vLook = m_tCameraDesc.vAt - m_tCameraDesc.vEye;

		_matrix		matRot;
		D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(dwMouseMove / m_fAngleSpeed));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_tCameraDesc.vAt = m_tCameraDesc.vEye + vLook;
	}

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
	{
		_vec3		vUp = _vec3(0.f, 1.f, 0.f);
		_vec3		vLook = m_tCameraDesc.vAt - m_tCameraDesc.vEye;
		_matrix		matRot;
		D3DXMatrixRotationAxis(&matRot, &vUp, D3DXToRadian(dwMouseMove / m_fAngleSpeed));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_tCameraDesc.vAt = m_tCameraDesc.vEye + vLook;
	}

	POINT	ptMouse{ WINCX >> 1, WINCY >> 1 };
	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

void CToolCamera::Free()
{
	CCamera::Free();
}

