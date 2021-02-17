#pragma once
#ifndef __COLLIDERBOX_H__
#include "VIBuffer.h"
BEGIN(Engine)
class ENGINE_DLL CColliderBox : public CVIBuffer
{
	enum COLTYPE{ True , False , End };
private:
	explicit CColliderBox(LPDIRECT3DDEVICE9 pDevice);
	explicit CColliderBox(const CColliderBox& other);
	virtual ~CColliderBox() = default;
	// CVIBuffer을(를) 통해 상속됨
public:
	virtual HRESULT Ready_Component() override;
	HRESULT	Ready_CreateToMesh(const _vec3* pVtxs, const _ulong& dwVtxCnt, const _ulong& dwStride);
	HRESULT	Ready_CreateToDefault();
	void	Render_Collider(const _matrix* pColliderMatrix);
public:
	virtual CComponent * Clone() override;
	static CColliderBox* CreateToMesh(LPDIRECT3DDEVICE9 pDevice, const _vec3* pVtxs, const _ulong& dwVtxCnt,const _ulong& dwStride);
	static CColliderBox* CreateToDefault(LPDIRECT3DDEVICE9 pDevice);
public:
	const	_vec3*		Get_Min() { return &m_vMin; }
	const	_vec3*		Get_Max() { return &m_vMax; }
	const _matrix*		Get_CollMatrix() { return &m_matColMatrix; }
	const	_vec3*		Get_VtxData(){ return m_pVtxData; }
	const	INDEX16*		Get_IdxData() { return m_pIdxData; }


	void				Set_CollMatrix(const _matrix& matCol) { m_matColMatrix = matCol;}
private:
	virtual void		Free();
private:
	_vec3					m_vMin, m_vMax;
	_bool					m_bCollision;
	LPDIRECT3DTEXTURE9		m_pTexture[End];
	_matrix					m_matColMatrix;
	_vec3*					m_pVtxData; // 상호작용 로컬 vtx값
	INDEX16*				m_pIdxData;

};
END
#define __COLLIDERBOX_H__
#endif
