#pragma once
#ifndef __GAMEOBJECTMANAGER_H__

#include "Base.h"
#include "Layer.h"
BEGIN(Engine)
class CGameObject;
class CGameObjectManager final : public CBase
{
	DECLARE_SINGLETON(CGameObjectManager)

private:
	explicit CGameObjectManager();
	virtual ~CGameObjectManager() = default;
public:
	HRESULT Add_ProtoType(const _tchar* pProtoTag, shared_ptr<CGameObject> pPrototype);
	shared_ptr<CGameObject> Add_GameObejct(const _int& iScene, const _tchar* pLayerTag, const _tchar* GameObjectTag);
	HRESULT ClearForScene(const _int& iScene);

public:
	_uint UpdateGameObject(const _int& iScene, const _float& fDeltaTime);
	_uint LateUpdateGameObject(const _int& iScene, const _float& fDeltaTime);


public:
	virtual void Free() override;

private:
	typedef unordered_map<const _tchar*, shared_ptr<CGameObject>> PROTOTYPES;
	typedef	unordered_map<_int,shared_ptr<CLayer>> LAYERS;
	PROTOTYPES	m_mapPrototypes; // Proto
	LAYERS	m_mapObjManager; // GameObj
	
};
END

#define __GAMEOBJECTMANAGER_H__
#endif

/*
레이어 클레스를 만들어서 

*/