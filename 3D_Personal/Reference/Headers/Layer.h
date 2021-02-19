#pragma once
#ifndef __LAYER__H_
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)
class CComponent;
class CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer() = default;
	typedef unordered_map<const _tchar*, list<CGameObject*>> GAMEOBJECTS;
public:
	HRESULT				Awake_Layer();
	//Awake �ܰ迡�� �߰��� ������Ʈ���� awake �� ���� ���� ���̾ �߰�
	HRESULT				LateAwake_Layer();
	HRESULT				Ready_Layer();
	_int				Update_Layer(const _float& fTimeDelta);
	_int				LateUpdate_Layer(const _float& fTimeDelta);

public:
	HRESULT					Add_GameObject(const _tchar* pLayerTag, CGameObject* pGameObject);
	//Awake �ܰ迡�� �߰��� ������Ʈ���� Ready ���� awake �� ���� �� ���̾ �߰��Ǵ� �Լ�
	HRESULT					LateAdd_GameObject(const _tchar* pLayerTag, CGameObject* pGameObject);
	CComponent* 			Get_Component(const _tchar* pLayerTag,const eComponentID::eComponentID& ComponentID);
	//����ũ�� ������Ʈ ����
	CGameObject*			Get_GameObject(const _tchar* pLayerTag);
	list<CGameObject*>*		Get_Layer(const _tchar* pLayerTag);
private:
	HRESULT					FindCheck_Layer(GAMEOBJECTS::iterator& rIter);
public:
	static CLayer* Create();
	void   Free();
private:
	GAMEOBJECTS m_mapLayers;
	GAMEOBJECTS m_mapLateLayers;

};

END
#define __LAYER__H_
#endif
/*
������Ʈ���� �з�  ���̾� �ױװ��� �������� �з� 
������Ʈ���� �ױװ��� ����ϳ� 1.2.3. 
Get Component�� ����Ʈ�� ���� Ư�� �Ҽ� ������ ����ܰԿ��� ���� �ִµ� 

���ܿ��� Ư���ϴ°� ����Ʈ ��ȯ �ؼ� ȣ�� �� �������� �׿�����Ʈ�� ��������Ʈ ����� �ϰ� 
�׷��� ��������� ���̾�� ������ ����ũ�� ������Ʈ ��

����ó���� ���� �������ΰ�  ���⼭ 


*/