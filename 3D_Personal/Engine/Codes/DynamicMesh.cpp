#include "DynamicMesh.h"


USING(Engine)

CDynamicMesh::CDynamicMesh(LPDIRECT3DDEVICE9 pDevice)
	:CMesh(pDevice)
	, m_pRootBone(nullptr)
	, m_pBoneHierachy(nullptr)
{
}

CDynamicMesh::CDynamicMesh(const CDynamicMesh & other)
	: CMesh(other)
	, m_pRootBone(other.m_pRootBone)
	, m_pBoneHierachy(other.m_pBoneHierachy)
	, m_MeshContainer(other.m_MeshContainer)
{
	m_pAniCtrl = CAniCtrl::Create(*other.m_pAniCtrl);
}



HRESULT CDynamicMesh::Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName)
{
	_tchar		szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	m_pBoneHierachy = CBoneHierarchy::Create(m_pDevice, pFilePath);
	NULL_CHECK_RETURN(m_pBoneHierachy, E_FAIL);

	LPD3DXANIMATIONCONTROLLER	 pAniCtrl = nullptr;

	if (FAILED(D3DXLoadMeshHierarchyFromX(szFullPath,
		D3DXMESH_MANAGED,
		m_pDevice,
		m_pBoneHierachy, // HierarchyLoader
		NULL,
		&m_pRootBone,
		&pAniCtrl)))	// AniCtrl
		return E_FAIL;

	m_pAniCtrl = CAniCtrl::Create(pAniCtrl);
	NULL_CHECK_RETURN(m_pAniCtrl, E_FAIL);

	SafeRelease(pAniCtrl);

	_matrix matTemp;

	//초기화용 업뎃
	Update_FrameMatrices((_ModD3DXFRAME*)m_pRootBone, D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f)));

	Set_FrameMatricesPointer((_ModD3DXFRAME*)m_pRootBone);

	return S_OK;
}

void CDynamicMesh::Render_Meshes()
{
	for (auto& iter : m_MeshContainer)
	{
		_ModD3DXMESHCONTAINER*		pDerivedContainer = iter;

		for (_ulong i = 0; i < pDerivedContainer->dwNumBones; ++i)
		{
			pDerivedContainer->pRenderingMatrix[i] = pDerivedContainer->pOffsetMatrix[i] *
														*pDerivedContainer->ppCombinedMatrix[i];
		}

		void*		pSrcVtx = nullptr;
		void*		pDestVtx = nullptr;

		pDerivedContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pDerivedContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// 소프트 웨어 스키닝을 수행하는 함수(스키닝 뿐 아니라 애니메이션 변경 시,
		// 뼈대들과 정점 정보들의 변경을 동시에 수행)
		pDerivedContainer->pSkinInfo->UpdateSkinnedMesh(pDerivedContainer->pRenderingMatrix, 
			NULL, pSrcVtx, pDestVtx);

		// 1인자 : 뼈의 최종적인 변환 상태
		// 2인자 : 원래대로 돌려놓기 위한 상태 행렬(본래는 1인자의 역행렬을 구해서 넣어줘야 하지만 안 넣어줘도 상관없음)
		// 3인자 : 변하지 않는 원본 메쉬의 정점 정보
		// 4인자 : 변환된 메쉬의 정점 정보

		//Render call
		for (_ulong i = 0; i < pDerivedContainer->NumMaterials; ++i)
		{
			m_pDevice->SetTexture(0, pDerivedContainer->ppTexture[i]);
			pDerivedContainer->MeshData.pMesh->DrawSubset(i);
		}

		pDerivedContainer->pOriMesh->UnlockVertexBuffer();
		pDerivedContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void CDynamicMesh::Set_AnimationIndex(const _uint & iIndex)
{
	m_pAniCtrl->Set_AnimationIndex(iIndex);
}

void CDynamicMesh::Play_Animation(const _float & fTimeDelta)
{
	m_pAniCtrl->Play_Animation(fTimeDelta);

	_matrix matTemp;
	Update_FrameMatrices((_ModD3DXFRAME*)m_pRootBone, D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f)));
}

void CDynamicMesh::Update_FrameMatrices(_ModD3DXFRAME* pFrame, const _matrix * pParentMatrix)
{
	if (nullptr == pFrame)
		return;

	pFrame->CombinedMatrix = pFrame->TransformationMatrix * (*pParentMatrix);

	if (nullptr != pFrame->pFrameSibling)
		Update_FrameMatrices((_ModD3DXFRAME*)pFrame->pFrameSibling, pParentMatrix);

	if (nullptr != pFrame->pFrameFirstChild)
		Update_FrameMatrices((_ModD3DXFRAME*)pFrame->pFrameFirstChild, &pFrame->CombinedMatrix);
}

//확장한 구조체 정보값 세팅
void CDynamicMesh::Set_FrameMatricesPointer(_ModD3DXFRAME * pFrame)
{
	if (nullptr != pFrame->pMeshContainer)
	{
		_ModD3DXMESHCONTAINER*		pDerivedContainer = (_ModD3DXMESHCONTAINER*)pFrame->pMeshContainer;

		for (_ulong i = 0; i < pDerivedContainer->dwNumBones; ++i)
		{
			const char*		pBoneName = pDerivedContainer->pSkinInfo->GetBoneName(i);
			_ModD3DXFRAME* pDerivedFrame = (_ModD3DXFRAME*)D3DXFrameFind(m_pRootBone, pBoneName);

			// 뼈들이 가지고 있는 CombinedTransformationMatrix의 주소값을 차례대로 보관
			pDerivedContainer->ppCombinedMatrix[i] = &pDerivedFrame->CombinedMatrix;
		}

		m_MeshContainer.push_back(pDerivedContainer);
	}

	if (nullptr != pFrame->pFrameSibling)
		Set_FrameMatricesPointer((_ModD3DXFRAME*)pFrame->pFrameSibling);

	if (nullptr != pFrame->pFrameFirstChild)
		Set_FrameMatricesPointer((_ModD3DXFRAME*)pFrame->pFrameFirstChild);
}

const _ModD3DXFRAME * CDynamicMesh::Get_FrameByName(const char * pFrameName)
{
	return (_ModD3DXFRAME*)D3DXFrameFind(m_pRootBone, pFrameName);
}

_bool CDynamicMesh::Is_AnimationSetEnd(void)
{
	return m_pAniCtrl->Is_AnimationSetEnd();
}

CDynamicMesh * CDynamicMesh::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath, const _tchar * pFileName)
{
	CDynamicMesh*	pIns = new CDynamicMesh(pDevice);

	if (FAILED(pIns->Ready_Meshes(pFilePath, pFileName)))
		SafeRelease(pIns);

	return pIns;
}

CComponent * CDynamicMesh::Clone()
{
	return new CDynamicMesh(*this);
}

void CDynamicMesh::Free()
{
	if (false == m_bClone)
	{
		m_pBoneHierachy->DestroyFrame(m_pRootBone);
		SafeRelease(m_pBoneHierachy);
	}

	SafeRelease(m_pAniCtrl);

	m_MeshContainer.clear();

	CMesh::Free();
}