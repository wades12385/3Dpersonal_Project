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
오브젝트별로 분류  레이어 테그값을 기준으로 분류 
오브젝트마다 테그값을 줘야하나 1.2.3. 
Get Component가 리스트로 담긴걸 특정 할수 있으면 여기단게에서 쓸수 있는데 

집단에서 특정하는건 리스트 반환 해서 호출 한 구역에서 겜오브젝트의 겟컴포넌트 쓰라고 하고 
그래도 결론적으로 레이어에서 쓸려면 유닉크한 오브젝트 뿐

삭제처리는 각각 개별적인건  여기서 


*/