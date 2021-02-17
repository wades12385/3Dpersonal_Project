#pragma once
#ifndef __TRNSFORM_H__

#include "Component.h"
BEGIN(Engine)
class ENGINE_DLL CTransform : public CComponent
{
public:
	explicit CTransform(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CTransform() = default;

	// CComponent을(를) 통해 상속됨
	virtual HRESULT Update_Component(const _float& fTimeDelta) override;
	virtual HRESULT Ready_Component() override;

	static	CTransform*				Create(LPDIRECT3DDEVICE9 pDevice);
private:
	virtual void					Free() override;
public:
	void							AddPosition(const _vec3& vPos);
	void							AddRotate(const _float& fX, const _float& fY, const _float& fZ);
	void							AddRotate(const _vec3& vRot);
	void							AddRevolve(const _float& fX, const _float& fY, const _float& fZ);
	void							AddRevolve(const _vec3& vRev);

	void							UpdateWorld();
public:
	//////////////////////////////////////////////////////////////////////////
	void							GetTransForm(const eTransform::eTransform& eType,OUT _vec3& vInfo);
	const _matrix					GetWorld();
	const _matrix					GetParent();
	const _vec3						GetRight();
	const _vec3						GetUp();
	const _vec3						GetLook();
	const _vec3						GetPosition();
	//////////////////////////////////////////////////////////////////////////
	void							SetScale(const _float& fX, const _float& fY, const _float& fZ);
	void							SetPosition(const _vec3& vPos);
	void							SetRotate(const _float& fX, const _float& fY, const _float& fZ);
	void							SetRotate(const _vec3& vRot);
	void							SetRevolve(const _float& fX, const _float& fY, const _float& fZ);
	void							SetRevolve(const _vec3& vRev);
private:
	_vec3							m_vTransDesc[eTransform::End];
	_matrix							m_matWorld;
	// row 로 받아서 쓰지 말고 그냥 setter 받아와서 쓰자  
	CTransform*						m_pParent = nullptr;
};
END

#define __TRNSFORM_H__
#endif

