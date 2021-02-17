#pragma once
#ifndef __COMPONENTMANAGER_H__
#include "Base.h"

//Comp
#include "Transform.h"
#include "ColliderBox.h"
//Resources
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "NaviMesh.h"
#include "Texture.h"


BEGIN(Engine)
class ENGINE_DLL CResource_Manager : public CBase
{
	DECLARE_SINGLETON(CResource_Manager)
	typedef unordered_map<const _tchar*, CResources*> RESOURCEMAP;
public:
	explicit CResource_Manager();
	virtual ~CResource_Manager() = default;

public:
	HRESULT			Ready_Resourece(LPDIRECT3DDEVICE9 pDevice, const _tchar* pCompTag, const eResourcesID::eResourcesID& eCompID , const CComponent* pComp);
	CComponent*		Clone(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourcesID);

	HRESULT			Ready_Buffer(LPDIRECT3DDEVICE9 pDevice, const _tchar* pBufferTag , const eResourcesID::eResourcesID& eResourcesID);
	//�̰� ��Ʈ��� �޾Ƽ� �� �д� �������� �߰��� �ϴ��� 
	HRESULT			Ready_Texture(LPDIRECT3DDEVICE9 pDevice, const _tchar* pTextureTag, const _tchar* pPath, const _uint& iCnt = 1);



	HRESULT			Ready_Mesh(LPDIRECT3DDEVICE9 pDevice, const _tchar* pMeshTag, eResourcesID::eResourcesID eType, const _tchar* pFilePath, const _tchar* pFileName);
	HRESULT			Load_Mesh(LPDIRECT3DDEVICE9 pDevice, const _tchar* pMeshTag, const _tchar* pFilePath);

	HRESULT			overlapCheck_Comp(const _tchar* pCompTag, const eResourcesID::eResourcesID& eResourceID, RESOURCEMAP::iterator& iter);
	HRESULT			FindCheck_Comp(RESOURCEMAP::iterator& iter, const eResourcesID::eResourcesID& eResourceID);
private:
	virtual void Free() override;
private:
	RESOURCEMAP m_mapResouces[eResourcesID::End];
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
