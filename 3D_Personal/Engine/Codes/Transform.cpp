#include "Transform.h"

USING(Engine)


CTransform::CTransform(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
{
}


HRESULT CTransform::Ready_Component()
{
	return S_OK;
}
HRESULT CTransform::Update_Component(const _float & fTimeDelta)
{

	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld *= *D3DXMatrixScaling(nullptr, m_vTransDesc[Scale].x, m_vTransDesc[Scale].y, m_vTransDesc[Scale].z);
	m_matWorld *= *D3DXMatrixRotationX(nullptr, D3DXToRadian(m_vTransDesc[Rotate].x));
	m_matWorld *= *D3DXMatrixRotationY(nullptr, D3DXToRadian(m_vTransDesc[Rotate].y));
	m_matWorld *= *D3DXMatrixRotationZ(nullptr, D3DXToRadian(m_vTransDesc[Rotate].z));
	m_matWorld *= *D3DXMatrixTranslation(nullptr, m_vTransDesc[Posision].x, m_vTransDesc[Posision].y, m_vTransDesc[Posision].z);
	m_matWorld *= *D3DXMatrixRotationX(nullptr, D3DXToRadian(m_vTransDesc[Revolve].x));
	m_matWorld *= *D3DXMatrixRotationY(nullptr, D3DXToRadian(m_vTransDesc[Revolve].y));
	m_matWorld *= *D3DXMatrixRotationZ(nullptr, D3DXToRadian(m_vTransDesc[Revolve].z));

	//  나중에 
	//if(m_pParent != nullptr || !m_pParent._Expired())
	//{
	//	_matrix matParent = m_pParent->GetWorld();
	//	m_matWorld *= matParent;
	//}
	return S_OK;
}

void CTransform::Free()
{
	CComponent::Free();
}

CTransform* CTransform::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTransform* pIns = new CTransform(pDevice);
	if (FAILED(pIns->Ready_Component()))
	{
		return nullptr;
	}

	return pIns;
}

void CTransform::AddPosition(const _vec3 & vPos)
{
	m_vTransDesc[Posision] += vPos;
}

void CTransform::AddRotate(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[Rotate].x += fX;
	m_vTransDesc[Rotate].y += fY;
	m_vTransDesc[Rotate].z += fZ;
}

void CTransform::AddRotate(const _vec3 & vRot)
{
	m_vTransDesc[Rotate] += vRot;
}

void CTransform::AddRevolve(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[Revolve].x += fX;
	m_vTransDesc[Revolve].y += fY;
	m_vTransDesc[Revolve].z += fZ;
}

void CTransform::AddRevolve(const _vec3 & vRev)
{
	m_vTransDesc[Revolve] += vRev;
}

void CTransform::UpdateWorld()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void CTransform::GetTransForm(const eTransform & eType, OUT _vec3 & vInfo)
{
	vInfo = m_vTransDesc[eType];
}

const _matrix  CTransform::GetWorld()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_matWorld;
}

const _matrix  CTransform::GetParent()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return _matrix();
}

const _vec3 CTransform::GetRight()
{
	_vec3 vInfo;
	memcpy(&vInfo, &m_matWorld.m[0][0], sizeof(_vec3));
	return vInfo;
}

const _vec3 CTransform::GetUp()
{
	_vec3 vInfo;
	memcpy(&vInfo, &m_matWorld.m[1][0], sizeof(_vec3));
	return vInfo;
}

const _vec3 CTransform::GetLook()
{
	_vec3 vInfo;
	memcpy(&vInfo, &m_matWorld.m[2][0], sizeof(_vec3));
	return vInfo;
}

const _vec3 CTransform::GetPosition()
{
	_vec3 vInfo;
	memcpy(&vInfo, &m_matWorld.m[3][0], sizeof(_vec3));
	return vInfo;
}

void CTransform::SetScale(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[Scale].x = fX;
	m_vTransDesc[Scale].y = fY;
	m_vTransDesc[Scale].z = fZ;
}

void CTransform::SetPosition(const _vec3 & vPos)
{
	m_vTransDesc[Posision] = vPos;
}

void CTransform::SetRotate(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[Rotate].x = fX;
	m_vTransDesc[Rotate].y = fY;
	m_vTransDesc[Rotate].z = fZ;
}

void CTransform::SetRotate(const _vec3 & vRot)
{
	m_vTransDesc[Rotate] = vRot;
}

void CTransform::SetRevolve(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[Revolve].x = fX;
	m_vTransDesc[Revolve].y = fY;
	m_vTransDesc[Revolve].z = fZ;
}

void CTransform::SetRevolve(const _vec3 & vRev)
{
	m_vTransDesc[Revolve] = vRev;
}
