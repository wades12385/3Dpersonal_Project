#pragma once
#ifndef __PLAYERCORE_H__

#include "GameObject.h"
USING(Engine)
class CPlayerCore : public CGameObject
{
private:
	explicit CPlayerCore(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlayerCore(const CPlayerCore& other);
	virtual ~CPlayerCore() =default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_Prototype() override;
	virtual HRESULT Awake_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _uint Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
public:
	CTransform*				Get_trans() { return m_pTrans; }
	CStaticMesh*			Get_Mesh() { return m_pStaticMesh; }
	void					Update_CoreTrans(const _vec3& vAxis , const _float& fAngle);

private:

public:
	static	CPlayerCore*  Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone() override;

private:
	CTransform* m_pTrans = nullptr;
	CStaticMesh* m_pStaticMesh = nullptr;
	//Test용
	class CNaviMesh* m_pNaviMeshCom = nullptr;
	_float		m_fMoveSpeed;
	_float		m_fRotSpeed;
	_matrix		m_matRot;
private:
	virtual void Free() override;
};

#define __PLAYERCORE_H__
#endif // !__PLAYERCORE_H__

/*
대략적으로 코어 최대 정점 길이가 10배 했을시 0.2 0.4

*/
