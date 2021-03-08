#include "stdafx.h"
#include "StaticDeployScene.h"
#include "Axis.h"
#include "SizeCheck.h" 
#include "MfcStaticItem.h"
#include "MainFrm.h"
#include "ToolForm.h"
CStaticDeployScene::CStaticDeployScene(LPDIRECT3DDEVICE9 pDevice)
	:CScene(pDevice)
{
}


HRESULT CStaticDeployScene::Initialize_Scene()
{
	CGameObject* pObj = CAxis::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_Axis", pObj);
	pObj = CSizeCheck::Create(m_pDevice);
	CManagement::Get_Instance()->Ready_GameObjectPrototype(L"Proto_SizeCheck", pObj);
	CManagement::Get_Instance()->Ready_Mesh(L"Ame_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Ame_0/", L"Ame_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Ant_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Ant_0/", L"Ant_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Apple_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Apple_0/", L"Apple_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Asagao_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Asagao_0/", L"Asagao_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Asagao_1", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Asagao_1/", L"Asagao_1.x");
	CManagement::Get_Instance()->Ready_Mesh(L"AsagaoPot_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/AsagaoPot_0/", L"AsagaoPot_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Bag_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Bag_0/", L"Bag_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Bag_1", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Bag_1/", L"Bag_1.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Ball_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Ball_0/", L"Ball_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Banana_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Banana_0/", L"Banana_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Banana_1", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Banana_1/", L"Banana_1.x");
	CManagement::Get_Instance()->Ready_Mesh(L"BookStand_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/BookStand_0/", L"BookStand_0.x");
	CManagement::Get_Instance()->Ready_Mesh(L"Car_0", eResourcesID::StaticMesh, L"../Resources/Mesh/Static/Item/Car_0/", L"Car_0.x");




	return S_OK;
}

HRESULT CStaticDeployScene::ReInitialize_Scene()
{
	return S_OK;
}


HRESULT CStaticDeployScene::Awake_Scene()
{
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Camera", L"Layer_Camera");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Stage1", L"Layer_Terrain");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_Axis", L"Layer_Tool1");
	CManagement::Get_Instance()->Ready_GameObject(L"Proto_SizeCheck", L"Layer_Tool2");
	//CManagement::Get_Instance()->Ready_GameObject(L"Proto_StaticItem", L"Layer_StaticItem");


	return S_OK; 
}
HRESULT CStaticDeployScene::Ready_Scene()
{
	return S_OK;
}


_uint CStaticDeployScene::Update_Scene(const _float & fTimeDeleta)
{
	//최근거 삭제 
	if (KeyPress(DIK_LCONTROL))
	{
		if (KeyDown(DIK_Z))
		{
			auto pList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_StaticItem");
			if (pList != nullptr)
			{
				auto iter = pList->rbegin();
				(*iter)->Set_Delete();
				
				CMainFrame* pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();
				CToolForm* pForm = (CToolForm*)(pMain->m_tSplitter.GetPane(0, 0));

				if(iter != pList->rend())
					pForm->m_StaticDeployTab.m_pObjItem = (CMfcStaticItem*)(*++iter);
			}
		}
	}

	return _uint();
}

_uint CStaticDeployScene::LateUpdate_Scene(const _float & fTimeDeleta)
{
	return _uint();
}

void CStaticDeployScene::Render_Scene()
{
}

CStaticDeployScene * CStaticDeployScene::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CStaticDeployScene(pDevice);
}

void CStaticDeployScene::Free()
{
	CScene::Free();
}
