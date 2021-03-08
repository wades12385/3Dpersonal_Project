#include "Item.h"
#include "Collider.h"
#include "Transform.h"
USING(Engine)
CItem::CItem(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
	,m_bDrop(false)
{
}

CItem::CItem(const CItem & other)
	: CGameObject(other)
{
}

void CItem::Set_Position(const _vec3 & vPos)
{
	_float	 fHight;
	if(m_bDrop)
		fHight = m_pCollider->Get_Bound().fDepth * 0.5f;
	else
		fHight = m_pCollider->Get_Bound().fHeight * 0.5f;

	_vec3    vPosition = vPos;
	vPosition.y += fHight;
	m_pTrans->Set_Position(vPosition);
	m_pTrans->Update_Component();
}

void CItem::Free()
{
	CGameObject::Free();
}
