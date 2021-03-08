#pragma once
#ifndef __STAGE3_H__
#include "GameObject.h"
USING(Engine)
class CStage3 : public CGameObject
{
private:
	explicit CStage3(LPDIRECT3DDEVICE9 pDevice);
	explicit CStage3(const CStage3& other);
	virtual ~CStage3() = default;
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT		  Ready_Prototype() override;
	virtual HRESULT		  Awake_GameObject() override;
	virtual HRESULT		  Ready_GameObject() override;
	virtual _uint		  Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint		  LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT		  RenderGameObject() override;
	virtual CGameObject*  Clone() override;

	static CStage3*				Create(LPDIRECT3DDEVICE9 pDevice);
private:
	CStaticMesh*		m_pMeshCom = nullptr;
	CTransform*			m_pTrans = nullptr;
	
private:
	virtual void Free() override;
};
#define __STAGE3_H__
#endif
