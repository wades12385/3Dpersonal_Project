#pragma once
#ifndef __TRNSFORM_H__

#include "Component.h"
BEGIN(Engine)
class ENGINE_DLL CTransform : public CComponent
{
public:
	explicit CTransform(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CTransform() = default;

	// CComponent��(��) ���� ��ӵ�
	virtual HRESULT Update_Component(const _float& fTimeDelta = 0.f) override;
	virtual HRESULT Ready_Component() override;

	static	CTransform*				Create(LPDIRECT3DDEVICE9 pDevice);
public:
	//������ �ٶ󺸴� ����
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
	const _vec3						Get_PositionWorld(); // ���彺���̽� ���� ��  ��ġ�� 
	const _vec3						Get_Position(); // ������Ʈ�� ��ġ���Ͱ�  
	const _vec3						Get_Sacle(); // ������Ʈ�� ��ġ���Ͱ�  

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
	// row �� �޾Ƽ� ���� ���� �׳� setter �޾ƿͼ� ����  
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