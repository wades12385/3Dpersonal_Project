#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}

HRESULT CLogo::Ready_Scene()
{
	return S_OK;
}

HRESULT CLogo::Awake_Scene()
{
	return S_OK;
}

_uint CLogo::Update_Scene(const _float& fTimeDeleta)
{
	return 0;
}

_uint CLogo::LateUpdate_Scene(const _float& fTimeDeleta)
{
	return 0;
}

void CLogo::Render_Scene()
{
	return;
}

void CLogo::Free()
{
	CScene::Free();
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo* pIns = new CLogo(pDevice);
	if (FAILED(pIns->Ready_Scene()))
	{
		SafeRelease(pIns);
	}
	return pIns;
}

