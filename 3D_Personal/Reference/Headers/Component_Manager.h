#pragma once
#ifndef __COMPONENTMANAGER_H__
#include "Base.h"

#include "Transform.h"

BEGIN(Engine)
class ENGINE_DLL CComponent_Manager : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
	typedef unordered_map<const _tchar*, CComponent*> COMPMAP;
public:
	explicit CComponent_Manager();
	virtual ~CComponent_Manager() = default;

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
public:

private:
	HRESULT Ready_Resourece(LPDIRECT3DDEVICE9 pDevice, const _tchar* pCompTag, const eResourcesID& eCompID , const CComponent* pComp);
	CComponent*	Clone(const _tchar* pCompTag, const eResourcesID& eResourcesID);

	HRESULT ExisitCheck_Comp(const _tchar* pCompTag, const eResourcesID& eResourceID);
	HRESULT FindCheck_Comp(COMPMAP::iterator& iter , const eResourcesID& eResourceID);

private:
	COMPMAP m_mapComponets[(_uint)eResourcesID::End];
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
