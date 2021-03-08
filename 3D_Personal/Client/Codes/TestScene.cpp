#include "stdafx.h"
#include "TestScene.h"
#include "PlayerCore.h"
#include "PlayerCamera.h"
#include "Stage3.h"
#include "NaviMeshObj.h"
#include "Player.h"

#include "ColliBox.h"

#include "Collision_Manager.h"
CTestScene::CTestScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
	, m_bNaviMeshRender(false)
{
}

HRESULT CTestScene::Initialize_Scene()
{
	CGameObject* pObj = CPlayerCore::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_PlayerCore", pObj);
	pObj = CPlayerCamera::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_PlayerCamera", pObj);
	pObj = CStage3::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Stage3", pObj);
	pObj = ColliBox::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_ColliBox", pObj);


	//
	pObj = CPlayer::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Player", pObj);
	
	CNaviMesh_Manager::Get_Instance()->Load(m_pDevice, L"../../Data/NaviMesh/S3_Part1.dat");
	CNaviMesh_Manager::Get_Instance()->Load(m_pDevice, L"../../Data/NaviMesh/S3_Part2.dat");
	CNaviMesh_Manager::Get_Instance()->Load(m_pDevice, L"../../Data/NaviMesh/S3_Part3.dat");

	return S_OK;
}

HRESULT CTestScene::ReInitialize_Scene()
{
	return S_OK;
}

HRESULT CTestScene::Awake_Scene()
{
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Player", L"Layer_Player");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_PlayerCore", L"Layer_PlayerCore");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_PlayerCamera", L"Layer_PlayerCamera");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Stage3", L"Layer_StageMesh");


	CManagement::Get_Instance()->Ready_GameObject(L"Proto_ColliBox", L"Layer_ColBox");


	return S_OK;
}

HRESULT CTestScene::Ready_Scene()
{

	ColliBox* pObj;
	pObj = (ColliBox*)CManagement::Get_Instance()->Get_GameObjet(L"Layer_ColBox");
	pObj->Set_Pos(_vec3(23, -4.f, 0));
	return S_OK;
}

_uint CTestScene::Update_Scene(const _float & fTimeDeleta)
{
	if (KeyDown(DIK_F1))
		m_bNaviMeshRender = !m_bNaviMeshRender;

	return _uint();
}

_uint CTestScene::LateUpdate_Scene(const _float & fTimeDeleta)
{

	CCollision_Manager::CollsisionSphereToBox(
		*CManagement::Get_Instance()->Get_GameObjetList(L"Layer_Player"),
		*CManagement::Get_Instance()->Get_GameObjetList(L"Layer_ColBox"));



	return _uint();
}

void CTestScene::Render_Scene()
{
	if (m_bNaviMeshRender)
		CNaviMesh_Manager::Get_Instance()->Render_Navi();
}

void CTestScene::Free()
{
	CScene::Free();
}

CTestScene * CTestScene::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CTestScene(pDevice);;
}
