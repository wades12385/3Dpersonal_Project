#pragma once
#ifndef __RESOURCES_H__
#include "Component.h"

BEGIN(Engine)
class CResource : public CComponent
{
public:
	explicit CResource(LPDIRECT3DDEVICE9 pDevice);
	explicit CResource(const CResource& other);
	virtual ~CResource() = default;

	// CComponent을(를) 통해 상속됨
	virtual HRESULT ReadyComponent() override;
	virtual void Free() override;
};
END
#define __RESOURCES_H__
#endif

/*
그냥 컴포넌트 매니저로 통치고 내부적으로 개념을 분리해서 사용하는걸로 
굳이 클레스를 한겹 더 씌울 필요가 있을까 

*/