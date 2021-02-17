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
	// CMesh��(��) ���� ��ӵ�
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
	���� �̸��� �����ϱ� ���� ������, �ƽ�Ű�ڵ� ������ ���ڿ�(MBCS���)
	�̰ɷ� Ư�� ���� ã�� ã�� �� ������ Ư�� �Ž� ������Ʈ�� ���� �� ���� 
	LPSTR                   Name;					
	���� �ε� ������ ���� ���� ���� �����ϰ� �ִ� ��� (����)
	������ ���� �θ� ���� ���� ������� ����� ���ý����̽����� ���� ���� ���� ���������� ������� ���� �ƴ� 
	D3DXMATRIX              TransformationMatrix;	

	//���� ����� �Ž�(�������� �̷���� �������) ����ü
	LPD3DXMESHCONTAINER     pMeshContainer;

	struct _D3DXFRAME       *pFrameSibling;			// ���� ���� �ּҸ� �����ϴ� ������
	struct _D3DXFRAME       *pFrameFirstChild;		// ù��° �ڽ� ���� �ּҸ� �����ϴ� ������

	//////////////////////////////////D3DXFRAME_Modified////////////////////////////////////////
	 ������ _D3DXFRAME
	// �θ� ���� ������ ���� �� �� �����
	���� ���� ���� ��ȯ ������ ��
	_matrix			CombinedMatrix;

} D3DXFRAME, *LPD3DXFRAME;
*/

/*

 �޽�(����)�� �̷�� ������ҵ��� ���� �����ϴ� ����ü
typedef struct _D3DXMESHCONTAINER
{
	�޽������̳��� �̸��� �����ϱ� ���� ������, �׷��� ���� ������� ����
	LPSTR                   Name;		

	�޽��� ������ �����ϱ� ���� ����ü ���� �޽� �İ�ü�� �����ϰ� �ִ� ����ü
	D3DXMESHDATA            MeshData;	

	�޽��� ���� ������ �����ϴ� �İ�ü
	LPD3DXMATERIAL          pMaterials; 
	
	�޽��� ���� ��Ư�� ����Ʈ �Ǵ� �̺�Ʈ ������ �����ϴ� �İ�ü, �츮�� ������� ����
	LPD3DXEFFECTINSTANCE    pEffects;	
	
	������ ������ �����ϱ� ���� ������,
	(�ؽ�ó�� ���� == ������ ���� == ������� ����)
	DWORD                   NumMaterials;	
	
	������ �������� ù ��° �ּҸ� �����ϴ� ������
	DWORD                  *pAdjacency;	

	��Ű�� �ִϸ��̼� �� �ʿ��� ����� �����ϴ� �Լ����� ���� �İ�ü
	LPD3DXSKININFO          pSkinInfo;	

	���� �޽������̳��� �ּҸ� �����ϴ� ������
	struct _D3DXMESHCONTAINER *pNextMeshContainer;	 

	////////////////////////////////////D3DXMESHCONTAINER_Modified//////////////////////////////////////
	
	�ؽ��� ���
	LPDIRECT3DTEXTURE9*		ppTexture;
	
	���� �ε� ������ ���¸� ������ �ִ� �޽� ��ü(�Һ�)
	-> ��ȯ�� �������� �Ž� ��Ű�� ����� ������ �Ǵϱ� ���� 
	LPD3DXMESH				pOriMesh;	

	_ulong					dwNumBones;	// �޽��� ���� ��� ���� ������ ����

	�ִϸ��̼� ������ ������ ������ ��� ���� Id3dxskininfo�� ���� �����
	_matrix*				pOffsetMatrix;

	//�� ����ü�� ���� �ִ� CombinedMatrix�� �ּҰ����� �����ϴ� ������
	���� �������� ���� ������ ��ȯ����� �����͵��� �迭 
	_matrix**				ppCombinedMatrix;

	 ���������� ����� ���� ����� ����  pFrameOffsetMatrix * (*ppCombinedMatrix)�� �����
	_matrix*				pRenderingMatrix;
} D3DXMESHCONTAINER, *LPD3DXMESHCONTAINER;


/////////////////////////////////////INFO/////////////////////////////////////
*/