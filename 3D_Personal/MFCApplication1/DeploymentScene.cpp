#include "stdafx.h"
#include "DeploymentScene.h"


CDeploymentScene::CDeploymentScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}


CDeploymentScene::~CDeploymentScene()
{
}

HRESULT CDeploymentScene::Ready_Scene()
{
	return E_NOTIMPL;
}

HRESULT CDeploymentScene::Awake_Scene()
{
	return E_NOTIMPL;
}

_uint CDeploymentScene::Update_Scene(const _float & fTimeDeleta)
{
	return _uint();
}

_uint CDeploymentScene::LateUpdate_Scene(const _float & fTimeDeleta)
{
	return _uint();
}

void CDeploymentScene::Render_Scene()
{
}
