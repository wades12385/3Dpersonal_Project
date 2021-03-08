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
	virtual HRESULT Update_Component(const _float& fTimeDelta = 0.f) override;
	virtual HRESULT Ready_Component() override;

	static	CTransform*				Create(LPDIRECT3DDEVICE9 pDevice);
public:
	//지점을 바라보는 업뎃
	HRESULT							Update_TargetComponet(const _vec3& vTargetPos);


public:
	void							AddPosition(const _vec3& vPos);
	void							AddRotate(const _float& fX, const _float& fY, const _float& fZ);
	void							AddRotate(const _vec3& vRot);
	void							AddRevolve(const _float& fX, const _float& fY, const _float& fZ);
	void							AddRevolve(const _vec3& vRev);
	void							UpdateWorld();
public:
	//////////////////////////////////////////////////////////////////////////
	void							Get_TransForm(const eTransform::eTransform& eType, OUT _vec3& vInfo);
	const _matrix					Get_World();
	const _matrix					Get_Parent();
	const _vec3						Get_Right();
	const _vec3						Get_Up();
	const _vec3						Get_Look();
	const _vec3						Get_PositionWorld(); // 월드스페이스 적용 후  위치값 
	const _vec3						Get_Position(); // 컴포넌트의 위치백터값  
	const _vec3						Get_Sacle(); // 컴포넌트의 위치백터값  

	//////////////////////////////////////////////////////////////////////////
	void							Set_Scale(const _float& fX, const _float& fY, const _float& fZ);
	void							Set_Position(const _vec3& vPos);
	void							Set_Rotate(const _float& fX, const _float& fY, const _float& fZ);
	void							Set_Rotate(const _vec3& vRot);
	void							Set_Revolve(const _float& fX, const _float& fY, const _float& fZ);
	void							Set_Revolve(const _vec3& vRev);
	void							Set_World(const _matrix& matworld) { m_matWorld = matworld; }
private:
	_vec3							m_vTransDesc[eTransform::End];
	_matrix							m_matWorld;
	// row 로 받아서 쓰지 말고 그냥 setter 받아와서 쓰자  
	CTransform*						m_pParent = nullptr;
private:
	virtual void					Free() override;
};
END

#define __TRNSFORM_H__
#endif

/************************************************************************/
/*  to Quaternion
D3DXQuaternionRotationYawPitchRoll();
D3DXMatrixRotationQuaternion();
	
*/
/************************************************************************/