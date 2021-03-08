#include "stdafx.h"
#include "BoxDeployScene.h"
#include "Stage1Mesh.h"


CBoxDeployScene::CBoxDeployScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}

HRESULT CBoxDeployScene::Initialize_Scene()
{
	//CGameObject* pObj = CStage1Mesh::Create(CManagement::Get_Instance()->Get_Device(), L"StaticMesh_Stage1");
	//CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Stage1", pObj);


	return S_OK;
}


HRESULT CBoxDeployScene::ReInitialize_Scene()
{

	return S_OK;
}


HRESULT CBoxDeployScene::Awake_Scene()
{
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Camera", L"Layer_Camera");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Stage1", L"Layer_Terrain");
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
