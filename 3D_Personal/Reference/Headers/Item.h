#pragma once
#ifndef __ITEM_H__
#include "GameObject.h"
BEGIN(Engine)
class ENGINE_DLL CItem : public CGameObject
{
public:
	explicit CItem(LPDIRECT3DDEVICE9 pDevice);
	explicit CItem(const CItem& other);
	virtual ~CItem() = default;

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() PURE;
	virtual HRESULT Awake_GameObject() PURE;
	virtual HRESULT Ready_GameObject() PURE;
	virtual _uint Update_GameObject(const _float & fDeltaTime) PURE;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) PURE;
	virtual HRESULT RenderGameObject() PURE;
public:
	const wstring&			Get_ItemName() { return m_wstrItemName; }
	void					Set_ItemName(const _tchar* pName) { m_wstrItemName = wstring(pName); }
	const OBJDATA&			Get_ObjDesc()	 { return m_tObjDecs; }
	OBJDATA&				Get_ObjDescMod() { return m_tObjDecs; }

	void					Set_Position(const _vec3& vPos);
public:
	virtual CGameObject * Clone() PURE;
protected:
	virtual void Free() override;
protected:
	class CTransform*		m_pTrans = nullptr;
	class CCollider*		m_pCollider = nullptr;
	class CStaticMesh*		m_pMesh = nullptr;
	_bool                   m_bDrop;
	wstring					m_wstrItemName;
	OBJDATA					m_tObjDecs;
};
END
#define __ITEM_H__
#endif
