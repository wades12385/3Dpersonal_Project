#include "stdafx.h"
#include "Axis.h"



CAxis::CAxis(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
	, m_pDXLine(nullptr)
	, m_vPosition(vZero)
{
}

CAxis::CAxis(const CAxis & other)
	: CGameObject(other)
	, m_bShow(false)
	, m_vPosition(other.m_vPosition)
	,m_pDXLine(other.m_pDXLine)
{
}

HRESULT CAxis::Ready_Prototype()
{

	m_vPosition = vZero;

	return S_OK;
}

HRESULT CAxis::Awake_GameObject()
{
	m_eRenderID = eRenderID::Priority;

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pDXLine)))
		return E_FAIL;

	return S_OK;
}

HRESULT CAxis::Ready_GameObject()
{
	return S_OK;
}

_uint CAxis::Update_GameObject(const _float & fDeltaTime)
{
	return _uint();
}

_uint CAxis::LateUpdate_GameObject(const _float & fDeltaTime)
{

	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return _uint();
}

HRESULT CAxis::RenderGameObject()
{

	_matrix		matWorld, matView, matProj;

	_vec3	  vAxisX[2];
	_vec3	  vAxisY[2];
	_vec3	  vAxisZ[2];

	vAxisX[0] = vZero;
	vAxisY[0] = vZero;
	vAxisZ[0] = vZero;
	vAxisX[1] = _vec3(1, 0, 0);
	vAxisY[1] = _vec3(0, 1, 0);
	vAxisZ[1] = _vec3(0, 0, 1);

	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	

	D3DXMatrixIdentity(&matWorld);
	matWorld._11 = 1.f;
	matWorld._11 = 1.f;
	matWorld._11 = 1.f;
	matWorld._41 = m_vPosition.x;
	matWorld._42 = m_vPosition.y;
	matWorld._43 = m_vPosition.z;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&vAxisX[i], &vAxisX[i], &matWorld);
		D3DXVec3TransformCoord(&vAxisY[i], &vAxisY[i], &matWorld);
		D3DXVec3TransformCoord(&vAxisZ[i], &vAxisZ[i], &matWorld);

		D3DXVec3TransformCoord(&vAxisX[i], &vAxisX[i], &matView);
		D3DXVec3TransformCoord(&vAxisY[i], &vAxisY[i], &matView);
		D3DXVec3TransformCoord(&vAxisZ[i], &vAxisZ[i], &matView);

		if (vAxisX[i].z <= 0.1f)
			vAxisX[i].z = 0.1f;

		if (vAxisY[i].z <= 0.1f)
			vAxisY[i].z = 0.1f;

		if (vAxisZ[i].z <= 0.1f)
			vAxisZ[i].z = 0.1f;

		D3DXVec3TransformCoord(&vAxisX[i], &vAxisX[i], &matProj);
		D3DXVec3TransformCoord(&vAxisY[i], &vAxisY[i], &matProj);
		D3DXVec3TransformCoord(&vAxisZ[i], &vAxisZ[i], &matProj);

	}

	m_pDXLine->SetWidth(10.f);

	m_pDevice->EndScene();
	m_pDevice->BeginScene();

	m_pDXLine->Begin();
	m_pDXLine->DrawTransform(vAxisX, 2, D3DXMatrixIdentity(&matWorld), COLOR_RED);
	m_pDXLine->DrawTransform(vAxisY, 2, D3DXMatrixIdentity(&matWorld), COLOR_BLUE);
	m_pDXLine->DrawTransform(vAxisZ, 2, D3DXMatrixIdentity(&matWorld), COLOR_GREEN);
	m_pDXLine->End();

	return S_OK;
}

CGameObject * CAxis::Clone()
{
	return new CAxis(*this);
}

CAxis * CAxis::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CAxis* pIns = new CAxis(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CAxis::Free()
{
	SafeRelease(m_pDXLine);
	CGameObject::Free();
}
