#pragma once
#ifndef __MESH_H__
#include "Resources.h"
BEGIN(Engine)
class ENGINE_DLL CMesh abstract : public CResources
{
protected:
	explicit CMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CMesh(const CMesh& other);
	virtual ~CMesh() = default;
protected:
	virtual HRESULT		Ready_Meshes(const _tchar* pFilePath, const _tchar* pFileName)PURE;
	virtual void		Render_Meshes()PURE;
protected:
	virtual void Free();
};
END

#define __MESH_H__
#endif
