#pragma once

#ifndef __ENGINE_STRUCT_H__
BEGIN(Engine)
// ����  [1/18/2021 Administrator]

//Test
typedef struct VertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;
}VTX_TEXTURE;

const _ulong FVF_VTX_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct VertexColor
{
	D3DXVECTOR3 vPosition;
	_ulong		dwColor;
}VTX_COLOR;

const _ulong FVF_VTX_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct CubeTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vUV;
}VTXCUBE;

const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);	

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
	// �θ� ���� ������ ���� �� �� �����
	_matrix			CombinedMatrix;	

}_ModD3DXFRAME;

typedef	struct D3DXMESHCONTAINER_Modified : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*		ppTexture;
	LPD3DXMESH				pOriMesh;	// ���� �ε� ������ ���¸� ������ �ִ� �޽� ��ü(�Һ�)

	_ulong					dwNumBones;	// �޽��� ���� ��� ���� ������ ����

	_matrix*				pOffsetMatrix;// �ִϸ��̼� ������ ������ ������ ��� ���� 

	// �� ����ü�� ���� �ִ� CombinedMatrix�� �ּҰ����� �����ϴ� ������
	_matrix**				ppCombinedMatrix;

	// ���������� ����� ���� ����� ����  pFrameOffsetMatrix * (*ppCombinedMatrix)�� �����
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


typedef struct CellVertexIdx
{
	_uint _A;
	_uint _B;
	_uint _C;
}CELLVTXIDX;

typedef struct LinkCell
{
	LinkCell()
		:iNaviID(NOT_FOUND)
		,iCellIdx(NOT_FOUND)
	{ }
	LinkCell(const _int& ID , const _int& IDX)
		:iNaviID(ID)
		, iCellIdx(IDX)
	{
	}
	_int	iNaviID;
	_int	iCellIdx;
}LINKCELL;


typedef struct tagBound
{
	_vec3		vMin;
	_vec3		vMax;
	_vec3		vCenter;
	float		fRadius;
	float		fLength;
	float		fHeight;
	float		fDepth;
}BOUND, *LPBOUND;


typedef struct tagObjetDataTable
{
	tagObjetDataTable()
		:iItemID(NOT_FOUND)
		,wstrTag(L"")
		,fSacle(1.f)
		,fSize(0.f)
		,fWeight(0.f)
		, bDecoration(false)
		, bFloating(false)
		, bStationary(false)
	{
	}
	_int				iItemID;
	std::wstring		wstrTag;
	_float				fSacle;
	_float				fSize;
	_float				fWeight;
	_bool				bDecoration;
	_bool				bFloating;
	_bool				bStationary;
}OBJDATA;

#define __ENGINE_STRUCT_H__ 
#endif