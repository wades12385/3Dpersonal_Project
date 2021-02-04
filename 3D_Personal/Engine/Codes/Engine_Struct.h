#pragma once

#ifndef __ENGINE_STRUCT_H__

BEGIN(Engine)

// 수정  [1/18/2021 Administrator]

//Test
typedef struct VertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;
}VTX_TEXTURE;

const _uint FVF_VTX_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct VertexTex
{
	_vec3		vPosition;		// 12
	_vec3		vNormal;		// 12
	_vec2		vTexUV;			// 8

}VTXTEX;

const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

typedef struct Index16
{
	_ushort		_0;
	_ushort		_1;
	_ushort		_2;

}INDEX16;

typedef struct Index32
{
	_ulong		_0;
	_ulong		_1;
	_ulong		_2;

}INDEX32;
END

typedef	struct D3DXFRAME_Modified : public D3DXFRAME
{
	// 부모 뼈와 곱셈을 끝낸 후 값 저장용
	_matrix			CombinedMatrix;	

}_ModD3DXFRAME;

typedef	struct D3DXMESHCONTAINER_Modified : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*		ppTexture;
	LPD3DXMESH				pOriMesh;	// 최초 로드 시점의 상태를 가지고 있는 메쉬 객체(불변)

	_ulong					dwNumBones;	// 메쉬가 지닌 모든 뼈의 개수를 보관

	_matrix*				pOffsetMatrix;// 애니메이션 정보를 포함한 최초의 행렬 상태 

	// 뼈 구조체가 갖고 있는 CombinedMatrix의 주소값들을 보관하는 포인터
	_matrix**				ppCombinedMatrix;

	// 최종적으로 출력을 위한 행렬의 상태  pFrameOffsetMatrix * (*ppCombinedMatrix)의 결과물
	_matrix*				pRenderingMatrix;

}_ModD3DXMESHCONTAINER;

//  [2/5/2021 wades]

typedef struct CameraDesc
{
	_vec3	 vEye;
	_vec3	 vAt;
	_vec3	 vUp;

	float	fFovY;	// Degree
	float	fAspect;
	float	fNear;
	float	fFar;

	_matrix	matView;
	_matrix matProj;
}CAMERA_DESC;
#define __ENGINE_STRUCT_H__
#endif