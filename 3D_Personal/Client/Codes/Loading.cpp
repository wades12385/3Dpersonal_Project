#include "stdafx.h"
#include "Loading.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 pDevice)
	:m_bFinish(false)
	, m_pDevice(pDevice)
{
	m_pDevice->AddRef();
}

HRESULT CLoading::Ready_Loading(const eLoadID::eLoadID&  eLoadID)
{
	InitializeCriticalSection(&m_CrtKey);
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Loading_thread, this, 0, NULL);
	m_eLoadID = eLoadID;

	return S_OK;
}

_uint CLoading::Loading_Test()
{
	lstrcpy(m_szLoading, L"Loading...");
	//Mesh

	CManagement::Get_Instance()->Ready_Mesh(L"Core_1", eResourcesID::StaticMesh,
		L"../../Resources/Mesh/Static/Player/Core/Core_1/", L"Core_1.X");

	CManagement::Get_Instance()->Ready_Mesh(L"StaticMesh_Stage1", 
		eResourcesID::StaticMesh, L"../../Resources/Mesh/Static/Stage/Test/", L"Stage1.X");

	CManagement::Get_Instance()->Ready_Mesh(L"Sphere", eResourcesID::StaticMesh, L"../../Data/", L"Sphere.X");
	CManagement::Get_Instance()->Ready_Mesh(L"Cube", eResourcesID::StaticMesh, L"../../Data/", L"Cube.X");



	lstrcpy(m_szLoading, L"Loading Complete!");
	m_bFinish = true;
	return 0;
}

unsigned int CLoading::Loading_thread(void * pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	_uint iFlag = 0;
	EnterCriticalSection(pLoading->Get_CrtKey());

	switch (pLoading->Get_LoadingID())
	{
	case eLoadID::Test:
		iFlag = pLoading->Loading_Test();
		break;
	}
	_endthreadex(0);

	return 0;
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 pDevice, const eLoadID::eLoadID&  eLoadID)
{
	CLoading* pIns = new CLoading(pDevice);
	if (FAILED(pIns->Ready_Loading(eLoadID)))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_CrtKey);
	SafeRelease(m_pDevice);
}
