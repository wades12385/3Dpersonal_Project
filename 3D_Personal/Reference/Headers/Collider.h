#pragma once
#ifndef __COLLIDERBOX_H__
#include "VIBuffer.h"
BEGIN(Engine)

class CTransform;
class CStaticMesh;
class ENGINE_DLL CCollider : public CComponent
{
	enum COLTYPE{ Collision , Trigger , End };
private:
	explicit CCollider(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCollider() = default;
	// CVIBuffer을(를) 통해 상속됨
public:
	virtual HRESULT Ready_Component() override;
	void	Render_Collider(const _bool& bSelect = false);

	_bool			RayPeeking(_vec2 pt);
public:
	//초기값 세팅
	void			Set_BoundType(eBoundType::eBoundType eType, CTransform* pTrans);
	void			Set_BoundTypeFitMesh(eBoundType::eBoundType eType, CTransform* pTransclass, CStaticMesh* pColliMesh);
	BOUND			Get_Bound();
	//스케일이나 회전 적용뒤 바운딩 갱신용
	void			Set_BoundSize(const _float& fRadius);
	void			Set_BoundSize(const _vec3 vScale);
	void			Set_Trigger() { m_bTriger = true; }
	void			Set_Collision() { m_bTriger = false; }

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pDevice);
//////////////////////////////////////////////////////////////////////////
private:
	virtual void			Free();
private:
	eBoundType::eBoundType	m_eBoundType;
	CStaticMesh*			m_pColMesh;
	CTransform*				m_pTrans;
	_bool					m_bTriger;
	_bool					m_bStand;
	LPDIRECT3DTEXTURE9		m_pTexture[End];
	LPDIRECT3DTEXTURE9		m_pSelectTexture;
	BOUND					m_tBound;


	// CComponent을(를) 통해 상속됨
	virtual HRESULT Update_Component(const _float & fTimeDelta = 0.f) override;
};
END
#define __COLLIDERBOX_H__
#endif
