#pragma once
#ifndef __BONEHIERARACHY_H__
#include "Engine_Include.h"

BEGIN(Engine)
class CBoneHierarchy : public ID3DXAllocateHierarchy
{
private:
	explicit CBoneHierarchy(LPDIRECT3DDEVICE9 pDevice, const _tchar* pPath);
	virtual ~CBoneHierarchy() = default;
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
private:
	void		Allocate_Name(char** ppName, const char* pFrameName);

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	const _tchar*			m_pPath;

public:
	static CBoneHierarchy*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pPath);
	_ulong					Release(void);
};

END
#define __LAYER__H_
#endif
/*
������Ʈ���� �з�  ���̾� �ױװ��� �������� �з� 
������Ʈ���� �ױװ��� ����ϳ� 1.2.3. 
Get Component�� ����Ʈ�� ���� Ư�� �Ҽ� ������ ����ܰԿ��� ���� �ִµ� 

���ܿ��� Ư���ϴ°� ����Ʈ ��ȯ �ؼ� ȣ�� �� �������� �׿�����Ʈ�� ��������Ʈ ����� �ϰ� 
�׷��� ��������� ���̾�� ������ ����ũ�� ������Ʈ ��

����ó���� ���� �������ΰ�  ���⼭ 


*/