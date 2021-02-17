#pragma once
#ifndef __DYNAMICMESH_H__	
#include "Mesh.h"
#include "BoneHierarchy.h"
#include "AniCtrl.h"

BEGIN(Engine)
class  ENGINE_DLL CDynamicMesh : public CMesh
{
private:
	explicit CDynamicMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CDynamicMesh(const CDynamicMesh& other);
	virtual ~CDynamicMesh() = default;
public:
	// CMesh을(를) 통해 상속됨
	virtual HRESULT			Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName) override;
	virtual void			Render_Meshes() override;
public:
	void					Set_AnimationIndex(const _uint& iIndex);
	void					Play_Animation(const _float& fTimeDelta);
private:
	void					Update_FrameMatrices(_ModD3DXFRAME* pFrame, const _matrix* pParentMatrix);
	void					Set_FrameMatricesPointer(_ModD3DXFRAME* pFrame);
public:
	const _ModD3DXFRAME*		Get_FrameByName(const char* pFrameName);
	_bool					Is_AnimationSetEnd(void);



private:
	D3DXFRAME*						m_pRootBone;
	CBoneHierarchy*						m_pBoneHierachy;
	CAniCtrl*							m_pAniCtrl;

	list<_ModD3DXMESHCONTAINER*>		m_MeshContainer;
public:
	static CDynamicMesh*	Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath, const _tchar* pFileName);
	virtual CComponent *	Clone() override;
private:
	virtual void Free()override;
};
END
#define __DYNAMICMESH_H__
#endif



/////////////////////////////////////INFO/////////////////////////////////////

/*
typedef struct _D3DXFRAME
{
	뼈의 이름을 저장하기 위한 포인터, 아스키코드 형태의 문자열(MBCS기반)
	이걸로 특정 뼈을 찾을 찾을 수 있으며 특정 매쉬 오브젝트를 붙일 수 있음 
	LPSTR                   Name;					
	최초 로드 시점에 뼈의 상태 값을 보관하고 있는 행렬 (로컬)
	각각의 본은 부모 뼈에 대해 상대적인 행렬을 로컬스페이스상의 값을 갖고 있음 원점값이지 월드상의 값이 아님 
	D3DXMATRIX              TransformationMatrix;	

	//본에 연결된 매쉬(파츠들이 이루어진 구성요소) 구조체
	LPD3DXMESHCONTAINER     pMeshContainer;

	struct _D3DXFRAME       *pFrameSibling;			// 형제 뼈의 주소를 보관하는 포인터
	struct _D3DXFRAME       *pFrameFirstChild;		// 첫번째 자식 뼈의 주소를 보관하는 포인터

	//////////////////////////////////D3DXFRAME_Modified////////////////////////////////////////
	 수정본 _D3DXFRAME
	// 부모 뼈와 곱셈을 끝낸 후 값 저장용
	본의 실제 월드 변환 정보를 들어감
	_matrix			CombinedMatrix;

} D3DXFRAME, *LPD3DXFRAME;
*/

/*

 메쉬(파츠)를 이루는 구성요소들의 값을 저장하는 구조체
typedef struct _D3DXMESHCONTAINER
{
	메쉬컨테이너의 이름을 저장하기 위한 포인터, 그러나 거의 사용하지 않음
	LPSTR                   Name;		

	메쉬의 종류를 결정하기 위한 열거체 값과 메쉬 컴객체를 보관하고 있는 구조체
	D3DXMESHDATA            MeshData;	

	메쉬의 재질 정보를 보관하는 컴객체
	LPD3DXMATERIAL          pMaterials; 
	
	메쉬가 지닌 독특한 이펙트 또는 이벤트 정보를 보관하는 컴객체, 우리는 사용하지 못함
	LPD3DXEFFECTINSTANCE    pEffects;	
	
	재질의 개수를 저장하기 위한 포인터,
	(텍스처의 개수 == 재질의 개수 == 서브셋의 개수)
	DWORD                   NumMaterials;	
	
	인접한 폴리곤의 첫 번째 주소를 보관하는 포인터
	DWORD                  *pAdjacency;	

	스키닝 애니메이션 시 필요한 기능을 제공하는 함수들을 지닌 컴객체
	LPD3DXSKININFO          pSkinInfo;	

	다음 메쉬컨테이너의 주소를 보관하는 포인터
	struct _D3DXMESHCONTAINER *pNextMeshContainer;	 

	////////////////////////////////////D3DXMESHCONTAINER_Modified//////////////////////////////////////
	
	텍스쳐 목록
	LPDIRECT3DTEXTURE9*		ppTexture;
	
	최초 로드 시점의 상태를 가지고 있는 메쉬 객체(불변)
	-> 변환이 적용전의 매쉬 스키닝 계산의 기준이 되니깐 보관 
	LPD3DXMESH				pOriMesh;	

	_ulong					dwNumBones;	// 메쉬가 지닌 모든 뼈의 개수를 보관

	애니메이션 정보를 포함한 최초의 행렬 상태 Id3dxskininfo로 부터 얻어짐
	_matrix*				pOffsetMatrix;

	//뼈 구조체가 갖고 있는 CombinedMatrix의 주소값들을 보관하는 포인터
	계층 구조내에 각각 본들의 변환행렬을 포인터들의 배열 
	_matrix**				ppCombinedMatrix;

	 최종적으로 출력을 위한 행렬의 상태  pFrameOffsetMatrix * (*ppCombinedMatrix)의 결과물
	_matrix*				pRenderingMatrix;
} D3DXMESHCONTAINER, *LPD3DXMESHCONTAINER;


/////////////////////////////////////INFO/////////////////////////////////////
*/