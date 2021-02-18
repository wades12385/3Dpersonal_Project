#include "stdafx.h"
#include "BoxDeployScene.h"


CBoxDeployScene::CBoxDeployScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}

HRESULT CBoxDeployScene::Initialize_Scene()
{
	return S_OK;
}

HRESULT CBoxDeployScene::Awake_Scene()
{
	return S_OK;
}

HRESULT CBoxDeployScene::Ready_Scene()
{
	return S_OK;
}

_uint CBoxDeployScene::Update_Scene(const _float & fTimeDeleta)
{
	return 0;
}

_uint CBoxDeployScene::LateUpdate_Scene(const _float & fTimeDeleta)
{

	return _uint();
}

void CBoxDeployScene::Render_Scene()
{

}
CBoxDeployScene * CBoxDeployScene::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return  new CBoxDeployScene(pDevice);;
}

void CBoxDeployScene::Free()
{
	CScene::Free();
}

HRESULT CBoxDeployScene::ReInitialize_Scene()
{
	return S_OK;
}
