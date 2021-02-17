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
	// CMesh��(��) ���� ��ӵ�
	virtual CComponent * Clone() override;

	virtual HRESULT		Ready_Meshes(const _tchar* pFilePath, const _tchar* pFileName)override;
	virtual void		Render_Meshes()override;


	LPD3DXMESH			Get_Mesh() { return m_pMesh; }
	LPD3DXMESH			Get_OriMesh() { return m_pOriMesh; }
	static CStaticMesh*	Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath, const _tchar* pFileName);
private:
	virtual void		Free();

private:
	LPD3DXMESH			m_pOriMesh;		// ������ �ε� ������ ������ �޽� �İ�ü
	LPD3DXMESH			m_pMesh;		// �븻������ ���Ե� ������ �޽� ��ǥ �İ�ü


	LPD3DXBUFFER		m_pAdjacency;	// ������ ������ ������ �����ϱ� ���� �޸� ����
	LPD3DXBUFFER		m_pSubset;		// ����� ������ �����ϱ� ���� �İ�ü
										// ����� ���� == ������ ���� == �ؽ�ó�� ����
	D3DXMATERIAL*		m_pMtrl;		// �޽��� ���� ���� + �ؽ�ó�� �̸��� �����ϴ� ����ü
	_ulong				m_dwSubsetCnt;	// ������� ����

	LPDIRECT3DTEXTURE9*	m_ppTextures;	// ���� �迭�� �������� �ؽ�ó�� �����ϱ� ���� ������

	// �ݶ��̴��� ���ؼ� ������ ����
	_ulong				m_dwStride;		// ���ؽ��� ũ�⸦ �����ϱ� ���� ����
	_vec3*				m_pVtxPos;		// �޽��� ���� ������ ������ ������ �����ϱ� ���� ���� �迭 �ּ� ��
	_ulong				m_dwVtxCnt;		// �޻簡 ���� ������ ����
	//  [2/9/2021 wades]
	_bool				m_bNoTexture;
};
END
#define __STATICMESH_H__
#endif
