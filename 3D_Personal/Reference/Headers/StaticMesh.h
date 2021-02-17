#pragma once
#ifndef __STATICMESH_H__
#include "Mesh.h"
BEGIN(Engine)
class ENGINE_DLL CStaticMesh : public CMesh
{
private:
	explicit CStaticMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CStaticMesh(const CStaticMesh& other);
	virtual ~CStaticMesh() = default;

public:
	const _vec3*		Get_VtxPos() { return m_pVtxPos; }
	_ulong&				Get_VtxStride() { return m_dwStride; }
	_ulong&				Get_VtxCnt() { return m_dwVtxCnt; }
	// CMesh을(를) 통해 상속됨
	virtual CComponent * Clone() override;

	virtual HRESULT		Ready_Meshes(const _tchar* pFilePath, const _tchar* pFileName)override;
	virtual void		Render_Meshes()override;


	LPD3DXMESH			Get_Mesh() { return m_pMesh; }
	LPD3DXMESH			Get_OriMesh() { return m_pOriMesh; }
	static CStaticMesh*	Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath, const _tchar* pFileName);
private:
	virtual void		Free();

private:
	LPD3DXMESH			m_pOriMesh;		// 최초의 로드 시점에 생성한 메쉬 컴객체
	LPD3DXMESH			m_pMesh;		// 노말정보가 삽입된 수정한 메쉬 대표 컴객체


	LPD3DXBUFFER		m_pAdjacency;	// 인접한 폴리곤 정보를 보관하기 위한 메모리 버퍼
	LPD3DXBUFFER		m_pSubset;		// 서브셋 정보를 보관하기 위한 컴객체
										// 서브셋 개수 == 재질의 개수 == 텍스처의 개수
	D3DXMATERIAL*		m_pMtrl;		// 메쉬의 재질 정보 + 텍스처의 이름을 저장하는 구조체
	_ulong				m_dwSubsetCnt;	// 서브셋의 개수

	LPDIRECT3DTEXTURE9*	m_ppTextures;	// 동적 배열로 여러장의 텍스처를 보관하기 위한 포인터

	// 콜라이더를 위해서 선언한 변수
	_ulong				m_dwStride;		// 버텍스의 크기를 저장하기 위한 변수
	_vec3*				m_pVtxPos;		// 메쉬가 지닌 정점의 포지션 정보를 보관하기 위한 동적 배열 주소 값
	_ulong				m_dwVtxCnt;		// 메사가 지닌 정점의 개수
	//  [2/9/2021 wades]
	_bool				m_bNoTexture;
};
END
#define __STATICMESH_H__
#endif
