#pragma once
#ifndef __GAMEOBJECT_H__
#include "Base.h"
BEGIN(Engine)
class CComponent;
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);
	explicit CGameObject(const CGameObject& other);
	virtual ~CGameObject() = default;	

public:
	virtual HRESULT						 Ready_Prototype() PURE;
	virtual HRESULT						 Awake_GameObject() PURE;
	virtual HRESULT						 Ready_GameObject() PURE;
	virtual _uint						 Update_GameObject(const _float& fDeltaTime) PURE;
	virtual _uint						 LateUpdate_GameObject(const _float& fDeltaTime) PURE;
	virtual HRESULT						 RenderGameObject() PURE;
public:
	virtual CGameObject*				 Clone()PURE;
	virtual void						 Free() override;


public:
	_bool									IsDelete() { return m_bDelete; };
	_bool									IsEnalble() { return m_bEnable; };
	//SetAble 설정시 호출용
	virtual void							OnEnable();
	virtual void							DisEnable();


public:
	CComponent*								Get_Component(const eComponentID::eComponentID& ComID);
	class CTransform*								Get_Transform();
	void									Set_Enalbe(_bool bEnable);
	void									Set_Delete() { m_bDelete = true; }
protected:
	HRESULT									Add_Component(const eComponentID::eComponentID& ComID ,CComponent* const pCom);

protected:
	LPDIRECT3DDEVICE9						m_pDevice;
	//class CManagement*					    m_pManagement = nullptr;
	_bool									m_bDelete;
	_bool									m_bEnable;
	_int									m_nTag;
	eRenderID								m_eRenderID;

	_int									m_iNavID;
	_int									m_iNaviCellIdx;

	//Culling
	_int									m_iSectionID;
	//Component							
	typedef unordered_map<eComponentID::eComponentID, CComponent* > COMPONENTS;
	COMPONENTS	m_mapComponents;
	
};
END

#define __GAMEOBJECT_H__

#endif
/////////////////////////////////////Summary/////////////////////////////////////
	/*
	STATIC DYNAMIC 두가지 타입으로 업데이트 할 컴포넌트 분리
	트렌스폼만 업데이트 받는 상황이라 함수만 미리 만들어놓음
	두개 이상으로 업데이트 컴포넌트가 필요하면 Update 돌리고 현재는 트렌스폼만 특정해서 업데이트 돌림




	*/
