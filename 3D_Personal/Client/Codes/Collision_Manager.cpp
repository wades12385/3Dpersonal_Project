#include "stdafx.h"
#include "Collision_Manager.h"
#include "Collider.h"


void CCollision_Manager::CollsisionSphereToBox(list<CGameObject*>& pDstObj, list<CGameObject*>& pSrcObj)
{
	vector<CCollider*>	DstCollider;
	vector<CCollider*>	SrcCollider;
	_vec3 vPenetration;

	for (auto& pDstObj : pDstObj)
	{
		CCollider* pDstCollider = (CCollider*)pDstObj->Get_Component(eComponentID::Collider);
		for (auto& pSrcObj : pSrcObj)
		{
			CCollider* pSrcCollider = (CCollider*)pSrcObj->Get_Component(eComponentID::Collider);;

			BOUND tDstBound = pDstCollider->Get_Bound();
			BOUND tSrcBound = pSrcCollider->Get_Bound();
			 
			if (AABBToSphere(tSrcBound, tDstBound, vPenetration))
			{
				static_cast<CTransform*>(pDstObj->Get_Component(eComponentID::Transform))->AddPosition(vPenetration);
			}
		}
	}
}

bool CCollision_Manager::AABBToSphere(BOUND _tAABB, BOUND _tSphere, _vec3 & _vPenetration)
{
	_vec3 vBoxPoint;

	if (_tSphere.vCenter.x <= _tAABB.vCenter.x - _tAABB.fLength * 0.5f)
		vBoxPoint.x = _tAABB.vCenter.x - _tAABB.fLength * 0.5f;
	else if (_tSphere.vCenter.x >= _tAABB.vCenter.x + _tAABB.fLength * 0.5f)
		vBoxPoint.x = _tAABB.vCenter.x + _tAABB.fLength * 0.5f;
	else
		vBoxPoint.x = _tSphere.vCenter.x;

	if (_tSphere.vCenter.y <= _tAABB.vCenter.y - _tAABB.fHeight * 0.5f)
		vBoxPoint.y = _tAABB.vCenter.y - _tAABB.fHeight * 0.5f;
	else if (_tSphere.vCenter.y >= _tAABB.vCenter.y + _tAABB.fHeight * 0.5f)
		vBoxPoint.y = _tAABB.vCenter.y + _tAABB.fHeight * 0.5f;
	else
		vBoxPoint.y = _tSphere.vCenter.y;

	if (_tSphere.vCenter.z <= _tAABB.vCenter.z - _tAABB.fDepth * 0.5f)
		vBoxPoint.z = _tAABB.vCenter.z - _tAABB.fDepth * 0.5f;
	else if (_tSphere.vCenter.z >= _tAABB.vCenter.z + _tAABB.fDepth * 0.5f)
		vBoxPoint.z = _tAABB.vCenter.z + _tAABB.fDepth * 0.5f;
	else
		vBoxPoint.z = _tSphere.vCenter.z;

	D3DXVECTOR3 vCenterToBox = vBoxPoint - _tSphere.vCenter;
	float fLength = D3DXVec3Length(&vCenterToBox);

	if (fLength <= _tSphere.fRadius)
	{
		D3DXVECTOR3 vDir = -vCenterToBox;
		D3DXVec3Normalize(&vDir, &vDir);
		_vPenetration = vDir * (_tSphere.fRadius - fLength);
		return true;
	}
	return false;
}
