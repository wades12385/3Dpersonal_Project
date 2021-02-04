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
	void							GetTransForm(const eTransform& eType,OUT _vec3& vInfo);
	const _matrix				GetWorld();
	const _matrix					GetParent();
	const _vec3					GetRight();
	const _vec3					GetUp();
	const _vec3					GetLook();
	const _vec3					GetPosition();
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
	// 해제시 따로 reset 처리를 해줘야하는데 weak 로 잡아야하나 a
	CTransform*				m_pParent = nullptr;
};
END

#define __TRNSFORM_H__
#endif

