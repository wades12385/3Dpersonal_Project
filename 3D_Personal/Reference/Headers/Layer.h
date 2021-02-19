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
	//Awake 단계에서 추가된 오브젝트들을 awake 콜 한후 기존 레이어에 추가
	HRESULT				LateAwake_Layer();
	HRESULT				Ready_Layer();
	_int				Update_Layer(const _float& fTimeDelta);
	_int				LateUpdate_Layer(const _float& fTimeDelta);

public:
	HRESULT					Add_GameObject(const _tchar* pLayerTag, CGameObject* pGameObject);
	//Awake 단계에서 추가된 오브젝트들이 Ready 전에 awake 한 다음 현 레이어에 추가되는 함수
	HRESULT					LateAdd_GameObject(const _tchar* pLayerTag, CGameObject* pGameObject);
	CComponent* 			Get_Component(const _tchar* pLayerTag,const eComponentID::eComponentID& ComponentID);
	//유니크한 오브젝트 전용
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
오브젝트별로 분류  레이어 테그값을 기준으로 분류 
오브젝트마다 테그값을 줘야하나 1.2.3. 
Get Component가 리스트로 담긴걸 특정 할수 있으면 여기단게에서 쓸수 있는데 

집단에서 특정하는건 리스트 반환 해서 호출 한 구역에서 겜오브젝트의 겟컴포넌트 쓰라고 하고 
그래도 결론적으로 레이어에서 쓸려면 유닉크한 오브젝트 뿐

삭제처리는 각각 개별적인건  여기서 


*/