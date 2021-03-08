#pragma once
#ifndef __NAVIMESHOBJ_H__

#include "GameObject.h"
USING(Engine)
class CNaviMeshObj : public CGameObject
{
private:
	explicit CNaviMeshObj(LPDIRECT3DDEVICE9 pDevice);
	explicit CNaviMeshObj(const CNaviMeshObj& other);
	virtual ~CNaviMeshObj() = default;
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;

	void Set_NaviTage(const _tchar* pTag);

	static CNaviMeshObj*  Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject*  Clone() override;
private:
	CNaviMesh*	m_pNaviMeshCom = nullptr;
	_tchar		m_szBuffer[MAX_PATH];
	_bool		m_bShow = false;
private:
	virtual void Free() override;
};

#endif // !__NAVIMESHOBJ_H__
