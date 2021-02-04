#pragma once

#ifndef __ENGINE_STRUCT_H__

BEGIN(Engine)

// ¼öÁ¤  [1/18/2021 Administrator]

//Test
typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;
}VTX_TEXTURE;

const _uint FVF_VTX_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct tagVertexTex
{
	_vec3		vPosition;		// 12
	_vec3		vNormal;		// 12
	_vec2		vTexUV;			// 8

}VTXTEX;

const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

typedef struct INDEX16
{
	_ushort		_0;
	_ushort		_1;
	_ushort		_2;

}INDEX16;

typedef struct INDEX32
{
	_ulong		_0;
	_ulong		_1;
	_ulong		_2;

}INDEX32;
END

#define __ENGINE_STRUCT_H__
#endif