#pragma once
#ifndef __GAMEOBJECTMANAGER_H__

#include "Base.h"
#include "Layer.h"
BEGIN(Engine)
class CGameObject;
class CGameObject_Manager final : public CBase
{
	typedef unordered_map<const _tchar*, CGameObject*> PROTOTYPES;
	typedef	unordered_map<_int, CLayer*> LAYERS;
	DECLARE_SINGLETON(CGameObject_Manager)
private:
	explicit CGameObject_Manager();
	virtual ~CGameObject_Manager() = default;

public:
	HRESULT					Awake_GameObject(const _int& iScene);
	HRESULT					Ready_GameObject(const _int& iScene);
	_uint					UpdateGameObject(const _int& iScene, const _float& fDeltaTime);
	_uint					LateUpdateGameObject(const _int& iScene, const _float& fDeltaTime);
	//Add	: Ready Awake �� ��ġ�� �ٷ� �߰��� ( �� �������϶� )
	//Direct Instance
	void					Add_InstanceGameObject(const _int& iScene, CGameObject* pGameObj, const _tchar * pLayerTag);
	//clone Instance
	CGameObject*			Add_InstanceGameObject(const _int& iScene, const _tchar* pProtoTag, const _tchar * pLayerTag);

public:
	//Ready : Ready Awake �� ���߿� �̷�� ���̾ �߰�  ( �� �ʱ�ȭ �ܰ�)
	HRESULT					Ready_ProtoType(const _tchar* pProtoTag,  CGameObject* pPrototype);
	HRESULT					Ready_SceneLayer(const _int& iScene);
	CGameObject*			Ready_GameObejct(const _int& iScene, const _tchar* pLayerTag, const _tchar* ProtoTag);
	//Awake �޼��忡�� ������Ʈ �߰� �ҋ��� �̰ɷ� 
	CGameObject*			LateReady_GameObejct(const _int& iScene, const _tchar* pLayerTag, const _tchar* GameObjectTag);

	HRESULT					ClearForScene(const _int& iScene);
public:
	CGameObject*			Get_GameObject(const _int& iScene, const _tchar* pLayerTag);
	list<CGameObject*>*		Get_Layer(const _int& iScene, const _tchar* pLayerTag);
public:
	virtual void Free() override;

private:
	HRESULT FindCheck_Obj(LAYERS::iterator& rIter);
	HRESULT FindCheck_Proto(PROTOTYPES::iterator& rIter);
private:
	PROTOTYPES	m_mapPrototypes; // Proto
	LAYERS		m_mapObjManager; // GameObj
	_bool		m_bChangeScene; 
};
END

#define __GAMEOBJECTMANAGER_H__
#endif

/*
���̾� Ŭ������ ���� 
*/