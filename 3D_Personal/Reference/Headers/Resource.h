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

	// CComponent��(��) ���� ��ӵ�
	virtual HRESULT ReadyComponent() override;
	virtual void Free() override;
};
END
#define __RESOURCES_H__
#endif

/*
�׳� ������Ʈ �Ŵ����� ��ġ�� ���������� ������ �и��ؼ� ����ϴ°ɷ� 
���� Ŭ������ �Ѱ� �� ���� �ʿ䰡 ������ 

*/