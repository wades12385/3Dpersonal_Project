#pragma once
#ifndef __NAVIMESH_H__
#include "Mesh.h"
#include "Cell.h"
BEGIN(Engine)
class ENGINE_DLL CNaviMesh : public CMesh
{
private:
	explicit CNaviMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CNaviMesh(const CNaviMesh& rhs);
	virtual ~CNaviMesh() = default;

public:
	HRESULT					Ready_NavigationMesh();
	virtual void			Render_Meshes() override;

	_vec3					Move_OnNaviMesh(const _vec3* pTargetPos, const _vec3* pTargetDir);
private:
	HRESULT					Link_Cell();
public:
	void					Set_CellIndex(const _ulong& iIndex) { m_dwIndex = iIndex; }
public:
	static CNaviMesh*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent *	Clone() override;
private:
	virtual void			Free();
private:
	vector<CCell*>			m_vecCell;
	_ulong					m_dwIndex;

//////////////////////////////////////////////////////////////////////////
public:
	virtual HRESULT			Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName) override;
};
END
#define __NAVIMESH_H__
#endif
