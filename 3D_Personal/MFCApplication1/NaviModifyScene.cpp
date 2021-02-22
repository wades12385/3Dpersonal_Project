#include "stdafx.h"
#include "NaviModifyScene.h"
#include "Stage1Mesh.h"

CNaviModifyScene::CNaviModifyScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}

HRESULT CNaviModifyScene::Initialize_Scene()
{
	CManagement::Get_Instance()->Ready_Mesh(L"StaticMesh_Stage1", eResourcesID::StaticMesh, L"../Data/Mesh/", L"Stage1.X");
	CManagement::Get_Instance()->Ready_Mesh(L"Sphere", eResourcesID::StaticMesh, L"../Data/", L"Sphere.X");

	CGameObject* pObj = CStage1Mesh::Create(CManagement::Get_Instance()->Get_Device(),L"StaticMesh_Stage1");
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Stage1", pObj);

	//Light 
	D3DLIGHT9			tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_SPOT;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Position = _vec3(0, -5, 0);
	tLightInfo.Attenuation0 = 0.00001f;
	Add_Light(CManagement::Get_Instance()->Get_Device(), &tLightInfo, 0);

	CManagement::Get_Instance()->Get_Device()->SetRenderState(D3DRS_LIGHTING, FALSE);


	return S_OK;
}

HRESULT CNaviModifyScene::ReInitialize_Scene()
{
	return S_OK;
}


HRESULT CNaviModifyScene::Awake_Scene()
{

	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Camera", L"Layer_Camera");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Stage1", L"Layer_Terrain");
	return S_OK;
}

HRESULT CNaviModifyScene::Ready_Scene()
{
	return S_OK;
}

_uint CNaviModifyScene::Update_Scene(const _float & fTimeDeleta)
{
	return _uint();
}

_uint CNaviModifyScene::LateUpdate_Scene(const _float & fTimeDeleta)
{
	return _uint();
}

void CNaviModifyScene::Render_Scene()
{
}

CNaviModifyScene * CNaviModifyScene::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return	new CNaviModifyScene(pDevice);
}

void CNaviModifyScene::Free()
{
	CScene::Free();
}

