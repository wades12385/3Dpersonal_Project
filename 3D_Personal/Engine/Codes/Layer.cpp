#include "Layer.h"

USING(Engine)

CLayer::CLayer()
{
}

HRESULT CLayer::Awake_Layer()
{
	for (auto& pair : m_mapLayers)
	{
		for (auto& Obj : pair.second)
		{
			if (FAILED(Obj->Awake_GameObject()))
			{
				MSG_BOX(L"Faild Obj Awake");
				return E_FAIL;
			}
		}

	}
	//  [2/7/2021 wades] 
	LateAwake();
	return S_OK;
}

HRESULT CLayer::Ready_Layer()
{
	for (auto& pair : m_mapLayers)
	{
		for (auto& Obj : pair.second)
		{
			if (FAILED(Obj->Ready_GameObject()))
			{
				MSG_BOX(L"Faild Obj Start");
				return E_FAIL;
			}
		}

	}
	return S_OK;
}

_int CLayer::Update_Layer(const _float & fTimeDelta)
{
	for (auto& pair : m_mapLayers)
	{
		auto  ObjList_iter = pair.second.begin();

		for (; ObjList_iter != pair.second.end(); )
		{
			if ((*ObjList_iter)->IsDelete())
			{
				SafeRelease(*ObjList_iter);
				ObjList_iter = pair.second.erase(ObjList_iter);
				continue;
			}
			if ((*ObjList_iter)->IsEnalble() == false)
			{
				++ObjList_iter;
				continue;
			}

			 (*ObjList_iter)->UpdateGameObject(fTimeDelta);
			 ++ObjList_iter;
		}

	}
	return 0;
}

_int CLayer::LateUpdate_Layer(const _float & fTimeDelta)
{
	for (auto& pair : m_mapLayers)
	{
		auto  ObjList_iter = pair.second.begin();
		for (; ObjList_iter != pair.second.end(); )
		{
			if ((*ObjList_iter)->IsEnalble() == false)
			{
				++ObjList_iter;
				continue;
			}
			(*ObjList_iter)->LateUpdateGameObject(fTimeDelta);
			++ObjList_iter;
		}
	}

	return _int();
}

HRESULT CLayer::Add_GameObject(const _tchar * pLayerTag, CGameObject* pGameObject)
{
	auto Iter_find = find_if(m_mapLayers.begin(), m_mapLayers.end(), CTagFinder(pLayerTag));

	if (FAILED(FindCheck_Layer(Iter_find)))
	{
		Iter_find = m_mapLayers.emplace(pLayerTag, list<CGameObject*>()).first;
	}
	
	//주소 중복체크 검사 ..음 

	Iter_find->second.emplace_back(pGameObject);

	return S_OK;
}

HRESULT CLayer::LateAdd_GameObject(const _tchar * pLayerTag, CGameObject * pGameObject)
{
	auto Iter_find = find_if(m_mapLateLayers.begin(), m_mapLateLayers.end(), CTagFinder(pLayerTag));

	if (FAILED(FindCheck_Layer(Iter_find)))
	{
		Iter_find = m_mapLayers.emplace(pLayerTag, list<CGameObject*>()).first;
	}

	Iter_find->second.emplace_back(pGameObject);

	return S_OK;
}

//유니크한 오브젝트 전용
CComponent*  CLayer::Get_Component(const _tchar * pLayerTag, const eComponentID::eComponentID & ComponentID)
{
	auto Iter_find = find_if(m_mapLayers.begin(), m_mapLayers.end(), CTagFinder(pLayerTag));

	if (FAILED(FindCheck_Layer(Iter_find)))
	{
		MSG_BOX(L"Not exist Layer");
		return nullptr;
	}
	else if ((*Iter_find).second.empty())
	{
		MSG_BOX(L"empty Layer");
		return nullptr;
	}

	return Iter_find->second.front()->Get_Component(ComponentID);
}
//유니크한 오브젝트 전용
CGameObject * CLayer::Get_GameObject(const _tchar * pLayerTag)
{
	auto Iter_find = find_if(m_mapLayers.begin(), m_mapLayers.end(), CTagFinder(pLayerTag));

	if (FAILED(FindCheck_Layer(Iter_find)))
	{
		MSG_BOX(L"Not exist Layer");
		return nullptr;
	}
	else if ((*Iter_find).second.empty())
	{
		MSG_BOX(L"empty Layer");
		return nullptr;
	}

	return Iter_find->second.front();
}

list<CGameObject*>* CLayer::Get_Layer(const _tchar * pLayerTag)
{
	auto Iter_find = find_if(m_mapLayers.begin(), m_mapLayers.end(), CTagFinder(pLayerTag));

	if (FAILED(FindCheck_Layer(Iter_find)))
	{
		MSG_BOX(L"Not exist Layer");
		return nullptr;
	}

	return &Iter_find->second;
}

//Awake 단계에서 추가된 오브젝트들이 Ready 전에 awake 한 다음 기존 레이어에 추가되는 함수
HRESULT CLayer::LateAwake()
{
	for (auto& pair : m_mapLateLayers)
	{
		for (auto& Obj : pair.second)
		{
			if (FAILED(Obj->Awake_GameObject()))
			{
				MSG_BOX(L"Faild Obj LateAwake");
				return E_FAIL;
			}
			//  [2/7/2021 wades] 기존 레이어로 이동
			auto layer_find  = find_if(m_mapLayers.begin(), m_mapLayers.end(), CTagFinder(pair.first));
			layer_find->second.emplace_back(Obj);
		}

	}

	m_mapLateLayers.clear();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////

HRESULT CLayer::FindCheck_Layer(GAMEOBJECTS::iterator & rIter)
{
	if (rIter == m_mapLayers.end())
		return E_FAIL;

	return S_OK;
}



CLayer* CLayer::Create()
{
	CLayer* pIns = new CLayer;
	return pIns;
}

void CLayer::Free()
{
	for (auto& pair : m_mapLayers)
	{
		for (auto& pObj : pair.second)
		{
			SafeRelease(pObj);
		}
		pair.second.clear();
	}
	m_mapLayers.clear();
}
