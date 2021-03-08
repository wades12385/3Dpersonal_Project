#pragma once
#ifndef __COLISION_MANAGER_H__
#include "Base.h"
#include "GameObject.h"
USING(Engine)
class CCollision_Manager 
{
public:
	static void		CollsisionSphereToBox(list<CGameObject*>& pDstObj, list<CGameObject*>& pSrcObj);
	static bool    AABBToSphere(BOUND _tAABB, BOUND _tSphere, _vec3& _vPenetration);

};
#define __COLISION_MANAGER_H__
#endif
