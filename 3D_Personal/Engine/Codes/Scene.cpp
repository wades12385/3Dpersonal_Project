#include "Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9  pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(pDevice);
}

HRESULT CScene::Ready_Scene()
{
	return S_OK;
}


void CScene::Free()
{
	SafeRelease(m_pDevice);
}


 
