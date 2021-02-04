#pragma once
#ifndef __COMPONENTMANAGER_H__
#include "Base.h"

//Comp
#include "Transform.h"

//Resources
#include "Resources.h" // ���߿� �߰��ϸ� ����

BEGIN(Engine)
class ENGINE_DLL CResource_Manager : public CBase
{
	DECLARE_SINGLETON(CResource_Manager)
	typedef unordered_map<const _tchar*, CResources*> RESOURCEMAP;
public:
	explicit CResource_Manager();
	virtual ~CResource_Manager() = default;

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
public:

private:
	HRESULT Ready_Resourece(LPDIRECT3DDEVICE9 pDevice, const _tchar* pCompTag, const eResourcesID& eCompID , const CComponent* pComp);
	CComponent*	Clone(const _tchar* pCompTag, const eResourcesID& eResourcesID);

	HRESULT ExisitCheck_Comp(const _tchar* pCompTag, const eResourcesID& eResourceID);
	HRESULT FindCheck_Comp(RESOURCEMAP::iterator& iter , const eResourcesID& eResourceID);
private:
	RESOURCEMAP m_mapResouces[(_uint)eResourcesID::End];
};
END
#define __COMPONENTMANAGER_H__
#endif // !__COMPONENTMANAGER_H__


/*
// �Ž��� ���������� �Ŵ��� ���ο��� 
���ҽ��� �з��� �ϱ�� ����� ��� �� �̿� ������Ʈ�� �ٸ� �Լ��� �׳� ���� �ؼ� ����Ұ��� 



client������ 

obj ���ο��� �Ŵ��� ȣ��� ������Ʈ �����ؼ� ��������  ���Ҵ��� �������� �ܴ̿� �����ؼ� 


boj�� add ������Ʈ�� ������ �ߺ���� üũ �ϰ� 
���ʿ� ������Ʈ�� ���۷��� üũ��  �����ε� 

������Ʈ�� ������ �̻� �������� ������ �����̸� ��ü�̰� 
�Ź� getter�� �޾ƿ´ٰ� �ϸ� �޾ƿ��� ������Ʈ�� ����� ������ ��۸� ������ �ƴϰ� 

��� �����ؼ� ��Դ°ų� Ʈ�������� Parent �� �����ε� 

�׷� Ʈ���� ���� �з�Ʈ�� ����� ��õ ������ ���ؼ� Ʈ�������� ���� �������� �Ź� ���°ɷ� 


*/
