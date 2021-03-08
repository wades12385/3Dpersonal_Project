#include "GameObject.h"
#include "Management.h"
#include "Component.h"
USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	,m_bDelete(false)
	,m_bEnable(true)
	,m_iNavID(NOT_FOUND)
	,m_iNaviCellIdx(NOT_FOUND)
{
	SafeAddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject & other)
	: m_pDevice(other.m_pDevice)
	, m_bDelete(other.m_bDelete)
	, m_bEnable(other.m_bEnable)
	, m_iNavID(other.m_iNavID)
	, m_iNaviCellIdx(other.m_iNaviCellIdx)

{
	SafeAddRef(m_pDevice);
}

HRESULT CGameObject::Ready_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Awake_GameObject()
{
	return S_OK;
}

HRESULT CGameObject::Ready_GameObject()
{
	return S_OK;
}

_uint CGameObject::Update_GameObject(const _float& fDeltaTime)
{
	for (auto& pair : m_mapComponents)
	{
		pair.second->Update_Component(fDeltaTime);
	}

	return _uint();
}

_uint CGameObject::LateUpdate_GameObject(const _float& fDeltaTime)
{
	return _uint();
}

HRESULT CGameObject::RenderGameObject()
{
	return S_OK;
}


void CGameObject::OnEnable()
{
}

void CGameObject::DisEnable()
{
}

HRESULT CGameObject::Add_Component(const eComponentID::eComponentID & ComID,  CComponent* const pCom)
{
	auto& Comp_iterfind = m_mapComponents.find(ComID);

	if (Comp_iterfind != m_mapComponents.end())
	{
		TCHAR szBuf[128] = TEXT("");
		swprintf(szBuf, 128, TEXT("Failed to add component. Com ID:%d is already exist."), ComID);
		MSG_BOX(szBuf);
		return E_FAIL;
	}

	m_mapComponents.emplace(ComID, pCom);

	return S_OK;
}

CComponent*	 CGameObject::Get_Component(const eComponentID::eComponentID & ComID)
{
	auto& Comp_iterfind = m_mapComponents.find(ComID);

	if (Comp_iterfind == m_mapComponents.end())
	{
		TCHAR szBuf[128] = TEXT("");
		swprintf(szBuf, 128, TEXT("Failed to find component. Com ID:%d "), ComID);
		MSG_BOX(szBuf);
		return nullptr;
	}

	return Comp_iterfind->second;
}

CTransform*	 CGameObject::Get_Transform()
{
	auto& Comp_iterfind = m_mapComponents.find(eComponentID::Transform);
	if (Comp_iterfind != m_mapComponents.end())
	{
		MSG_BOX(L"Failed to find Transfornm component.");
		return nullptr;
	}

	return (CTransform*)Comp_iterfind->second;
}

void CGameObject::Set_Enalbe(_bool bEnable)
{
	if (m_bEnable == bEnable)
		return;

	m_bEnable = bEnable;

	if (m_bEnable)
		OnEnable();
	else
		DisEnable();
}

void CGameObject::Free()
{
	SafeRelease(m_pDevice);
	for (auto& pair : m_mapComponents)
	{
		SafeRelease(pair.second);
	}
	m_mapComponents.clear();
}
