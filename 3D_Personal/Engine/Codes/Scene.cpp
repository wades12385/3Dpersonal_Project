#include "Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9  pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(pDevice);
}



void CScene::Free()
{
	SafeRelease(m_pDevice);
}


 
