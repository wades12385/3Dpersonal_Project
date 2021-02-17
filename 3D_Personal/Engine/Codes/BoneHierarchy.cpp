#include "BoneHierarchy.h"

USING(Engine)

Engine::CBoneHierarchy::CBoneHierarchy(LPDIRECT3DDEVICE9 pDevice, const _tchar* pPath)
	:m_pDevice(pDevice)
	,m_pPath(pPath)
{
	m_pDevice->AddRef();
}

STDMETHODIMP Engine::CBoneHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	_ModD3DXFRAME*			pDerivedFrame = new _ModD3DXFRAME;
	ZeroMemory(pDerivedFrame, sizeof(_ModD3DXFRAME));

	Allocate_Name(&pDerivedFrame->Name, Name);

	pDerivedFrame->CombinedMatrix = *D3DXMatrixIdentity(&pDerivedFrame->CombinedMatrix);

	*ppNewFrame = pDerivedFrame;

	return S_OK;
}

STDMETHODIMP Engine::CBoneHierarchy::CreateMeshContainer(THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData, CONST D3DXMATERIAL *pMaterials, 
	CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	_ModD3DXMESHCONTAINER*	pDerivedContainer = new _ModD3DXMESHCONTAINER;
	ZeroMemory(pDerivedContainer, sizeof(_ModD3DXMESHCONTAINER));

	//이름 세팅
	Allocate_Name(&pDerivedContainer->Name, Name);

	//매쉬타입 세팅
	pDerivedContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH	pMesh = pMeshData->pMesh;

	_ulong	dwNumFaces = pMesh->GetNumFaces();	
	pDerivedContainer->pAdjacency = new _ulong[dwNumFaces * 3]; // 메쉬가 지닌 폴리곤의 갯수 크기의 할당
	memcpy(pDerivedContainer->pAdjacency, pAdjacency, sizeof(_ulong) * dwNumFaces * 3); //

	_ulong dwFVF = pMesh->GetFVF();

	//노말확인 
	if (!(dwFVF & D3DFVF_NORMAL))
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF | D3DFVF_NORMAL, m_pDevice, &pDerivedContainer->MeshData.pMesh);
		// 정점의 노말을 계산하여 메쉬 객체에 삽입해주는 함수
		D3DXComputeNormals(pDerivedContainer->MeshData.pMesh, pDerivedContainer->pAdjacency);
	}
	else
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF, m_pDevice, &pDerivedContainer->MeshData.pMesh);
	}

	//최소 머테리얼 갯수 세팅 최소값 1 
	pDerivedContainer->NumMaterials = (NumMaterials == 0 ? 1 : NumMaterials);

	pDerivedContainer->pMaterials = new D3DXMATERIAL[pDerivedContainer->NumMaterials];
	ZeroMemory(pDerivedContainer->pMaterials, sizeof(D3DXMATERIAL) * pDerivedContainer->NumMaterials);

	pDerivedContainer->ppTexture = new LPDIRECT3DTEXTURE9[pDerivedContainer->NumMaterials];
	ZeroMemory(pDerivedContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pDerivedContainer->NumMaterials);


	if (0 != NumMaterials)
	{
		memcpy(pDerivedContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pDerivedContainer->NumMaterials);

		for (_ulong i = 0; i < pDerivedContainer->NumMaterials; ++i)
		{
			_tchar	szFullPath[256] = L"";
			_tchar	szFileName[256] = L"";

			lstrcpy(szFullPath, m_pPath);

			MultiByteToWideChar(CP_ACP, 0, pDerivedContainer->pMaterials[i].pTextureFilename,
				strlen(pDerivedContainer->pMaterials[i].pTextureFilename), szFileName, 256);

			lstrcat(szFullPath, szFileName);


			if (FAILED(D3DXCreateTextureFromFile(m_pDevice, szFullPath, &pDerivedContainer->ppTexture[i])))
			{
				MSG_BOX(L"DynamicMesh Texture Create Failed");
				return E_FAIL;
			}
		}
	}

	//머테리얼 없던 메쉬는  디폴트값으로 설정
	else
	{
		pDerivedContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedContainer->pMaterials[0].MatD3D.Power = 0.f;

		pDerivedContainer->ppTexture[0] = nullptr;
	}

	if (nullptr == pSkinInfo)
		return S_OK;

	pDerivedContainer->pSkinInfo = pSkinInfo;
	pDerivedContainer->pSkinInfo->AddRef();

	//원본매쉬 fvf 복사
	pDerivedContainer->MeshData.pMesh->CloneMeshFVF(pDerivedContainer->MeshData.pMesh->GetOptions(), pDerivedContainer->MeshData.pMesh->GetFVF(),
														m_pDevice, &pDerivedContainer->pOriMesh);

	// 메쉬가 지닌 뼈의 개수를 넣어주고 
	pDerivedContainer->dwNumBones = pDerivedContainer->pSkinInfo->GetNumBones();

	//각각 행렬배열 주소값들 초기화 
	pDerivedContainer->pOffsetMatrix = new _matrix[pDerivedContainer->dwNumBones];
	ZeroMemory(pDerivedContainer->pOffsetMatrix, sizeof(_matrix) * pDerivedContainer->dwNumBones);

	pDerivedContainer->ppCombinedMatrix = new _matrix*[pDerivedContainer->dwNumBones];
	ZeroMemory(pDerivedContainer->ppCombinedMatrix, sizeof(_matrix*) * pDerivedContainer->dwNumBones);

	pDerivedContainer->pRenderingMatrix = new _matrix[pDerivedContainer->dwNumBones];
	ZeroMemory(pDerivedContainer->pRenderingMatrix, sizeof(_matrix) * pDerivedContainer->dwNumBones);

	//skininfo에서 offsetmat 가져옴 
	for (_ulong i = 0; i < pDerivedContainer->dwNumBones; ++i)
		pDerivedContainer->pOffsetMatrix[i] = *pDerivedContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	*ppNewMeshContainer = pDerivedContainer;

	return S_OK;
}

STDMETHODIMP Engine::CBoneHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	SafeDeleteArray(pFrameToFree->Name);

	if (nullptr != pFrameToFree->pMeshContainer)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (nullptr != pFrameToFree->pFrameSibling)
		DestroyFrame(pFrameToFree->pFrameSibling);

	if (nullptr != pFrameToFree->pFrameFirstChild)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	SafeDelete(pFrameToFree);
	return S_OK;
}

STDMETHODIMP Engine::CBoneHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	_ModD3DXMESHCONTAINER*		pDerivedContainer = (_ModD3DXMESHCONTAINER*)pMeshContainerToFree;

	for (_ulong i = 0; i < pDerivedContainer->NumMaterials; ++i)
		SafeRelease(pDerivedContainer->ppTexture[i]);

	SafeRelease(pDerivedContainer->pSkinInfo);
	SafeRelease(pDerivedContainer->MeshData.pMesh);
	SafeRelease(pDerivedContainer->pOriMesh);

	SafeDeleteArray(pDerivedContainer->pAdjacency);
	SafeDeleteArray(pDerivedContainer->ppTexture);
	SafeDeleteArray(pDerivedContainer->pOffsetMatrix);
	SafeDeleteArray(pDerivedContainer->ppCombinedMatrix);
	SafeDeleteArray(pDerivedContainer->pRenderingMatrix);
	SafeDeleteArray(pDerivedContainer->pMaterials);
	SafeDeleteArray(pDerivedContainer->Name);

	SafeDelete(pDerivedContainer);

	return S_OK;
}

void Engine::CBoneHierarchy::Allocate_Name(char** ppName, const char* pFrameName)
{
	if (nullptr == pFrameName)
		return;

	_uint	iLength = strlen(pFrameName);

	*ppName = new char[iLength + 1];

	strcpy_s(*ppName, iLength + 1, pFrameName);
}

Engine::CBoneHierarchy* Engine::CBoneHierarchy::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pPath)
{
	return new CBoneHierarchy(pGraphicDev, pPath);
}

_ulong Engine::CBoneHierarchy::Release(void)
{
	SafeRelease(m_pDevice);

	delete this;

	return 0;
}
