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
public:
	HRESULT					Ready_SceneLayer(const _int& iScene);
	HRESULT					Add_ProtoType(const _tchar* pProtoTag,  CGameObject* pPrototype);
	CGameObject*			Add_GameObejct(const _int& iScene, const _tchar* pLayerTag, const _tchar* GameObjectTag);
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
};
END

#define __GAMEOBJECTMANAGER_H__
#endif

/*
레이어 클레스를 만들어서 
*/