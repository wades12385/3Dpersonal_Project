#include "Transform.h"

USING(Engine)


CTransform::CTransform(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
{
}


HRESULT CTransform::Ready_Component()
{

	m_vTransDesc[eTransform::Scale ] = _vec3(1, 1, 1);
	m_vTransDesc[eTransform::Rotate] = vZero;
	m_vTransDesc[eTransform::Posision] = vZero;
	m_vTransDesc[eTransform::Revolve] = vZero;


	return S_OK;
}
HRESULT CTransform::Update_Component(const _float & fTimeDelta)
{

	D3DXMatrixIdentity(&m_matWorld);
	_matrix matDesc;

	m_matWorld *= *D3DXMatrixScaling(&matDesc, m_vTransDesc[eTransform::Scale].x, m_vTransDesc[eTransform::Scale].y, m_vTransDesc[eTransform::Scale].z);
	m_matWorld *= *D3DXMatrixRotationX(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Rotate].x));
	m_matWorld *= *D3DXMatrixRotationY(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Rotate].y));
	m_matWorld *= *D3DXMatrixRotationZ(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Rotate].z));
	m_matWorld *= *D3DXMatrixTranslation(&matDesc, m_vTransDesc[eTransform::Posision].x, m_vTransDesc[eTransform::Posision].y, m_vTransDesc[eTransform::Posision].z);
	m_matWorld *= *D3DXMatrixRotationX(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Revolve].x));
	m_matWorld *= *D3DXMatrixRotationY(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Revolve].y));
	m_matWorld *= *D3DXMatrixRotationZ(&matDesc, D3DXToRadian(m_vTransDesc[eTransform::Revolve].z));

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
	m_vTransDesc[eTransform::Posision] += vPos;
}

void CTransform::AddRotate(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[eTransform::Rotate].x += fX;
	m_vTransDesc[eTransform::Rotate].y += fY;
	m_vTransDesc[eTransform::Rotate].z += fZ;
}

void CTransform::AddRotate(const _vec3 & vRot)
{
	m_vTransDesc[eTransform::Rotate] += vRot;
}

void CTransform::AddRevolve(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[eTransform::Revolve].x += fX;
	m_vTransDesc[eTransform::Revolve].y += fY;
	m_vTransDesc[eTransform::Revolve].z += fZ;
}

void CTransform::AddRevolve(const _vec3 & vRev)
{
	m_vTransDesc[eTransform::Revolve] += vRev;
}

void CTransform::UpdateWorld()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void CTransform::GetTransForm(const eTransform::eTransform & eType, OUT _vec3 & vInfo)
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
	m_vTransDesc[eTransform::Scale].x = fX;
	m_vTransDesc[eTransform::Scale].y = fY;
	m_vTransDesc[eTransform::Scale].z = fZ;
}

void CTransform::SetPosition(const _vec3 & vPos)
{
	m_vTransDesc[eTransform::Posision] = vPos;
}

void CTransform::SetRotate(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[eTransform::Rotate].x = fX;
	m_vTransDesc[eTransform::Rotate].y = fY;
	m_vTransDesc[eTransform::Rotate].z = fZ;
}

void CTransform::SetRotate(const _vec3 & vRot)
{
	m_vTransDesc[eTransform::Rotate] = vRot;
}

void CTransform::SetRevolve(const _float & fX, const _float & fY, const _float & fZ)
{
	m_vTransDesc[eTransform::Revolve].x = fX;
	m_vTransDesc[eTransform::Revolve].y = fY;
	m_vTransDesc[eTransform::Revolve].z = fZ;
}

void CTransform::SetRevolve(const _vec3 & vRev)
{
	m_vTransDesc[eTransform::Revolve] = vRev;
}
