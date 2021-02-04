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
	virtual _uint						 UpdateGameObject(const _float& fDeltaTime) PURE;
	virtual _uint						 LateUpdateGameObject(const _float& fDeltaTime) PURE;
	virtual HRESULT						 RenderGameObject() PURE;
public:
	virtual CGameObject*				 Clone()PURE;
	virtual void						 Free() override;


public:
	_bool									IsDelete() { return m_bDelete; };
	_bool									IsEnalble() { return m_bEnable; };
	//SetAble ������ ȣ���
	virtual void							OnEnable();
	virtual void							DisEnable();


public:
	HRESULT									Add_Component(const eComponentID& ComID ,CComponent* const pCom);
	CComponent*								Get_Component(const eComponentID& ComID);
	CComponent*								Get_Transform();
public:
	void									Set_Enalbe(_bool bEnable);
	void									Set_Delete() { m_bDelete = true; }

protected:
	LPDIRECT3DDEVICE9						m_pDevice;
	class CManagement*					    m_pManagement = nullptr;
	_bool									m_bDelete;
	_bool									m_bEnable;
	_int									m_nTag;
	eRenderID								m_eRenderID;
	
	//Component							
	typedef unordered_map<eComponentID, CComponent* > COMPONENTS;
	COMPONENTS	m_mapComponents;
	
};
END

#define __GAMEOBJECT_H__

#endif
/////////////////////////////////////Summary/////////////////////////////////////
	/*
	STATIC DYNAMIC �ΰ��� Ÿ������ ������Ʈ �� ������Ʈ �и�
	Ʈ�������� ������Ʈ �޴� ��Ȳ�̶� �Լ��� �̸� ��������
	�ΰ� �̻����� ������Ʈ ������Ʈ�� �ʿ��ϸ� Update ������ ����� Ʈ�������� Ư���ؼ� ������Ʈ ����
	*/
