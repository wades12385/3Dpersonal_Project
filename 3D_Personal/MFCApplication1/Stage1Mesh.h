#pragma once
#ifndef __TOOLSTAGE1_H__
#include "Gameobject.h"
BEGIN(Engine)
class CStage1Mesh : public CGameObject
{
private:
	explicit CStage1Mesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CStage1Mesh(const CStage1Mesh& other);
	virtual ~CStage1Mesh() = default; 
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT		  Ready_Prototype() override;
	virtual HRESULT		  Awake_GameObject() override;
	virtual HRESULT		  Ready_GameObject() override;
	virtual _uint		  Update_GameObject(const _float & fDeltaTime) override;
	virtual _uint		  LateUpdate_GameObject(const _float & fDeltaTime) override;
	virtual HRESULT		  RenderGameObject() override;
	virtual CGameObject*  Clone() override;

	void	Set_Tag(const _tchar* pTag) { lstrcpy(m_szMeshTag, pTag); };

	static CStage1Mesh* Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pComTag);
	Engine::CStaticMesh*		m_pMeshCom = nullptr;
	Engine::CTransform*			m_pTrans = nullptr;
	TCHAR m_szMeshTag[MAX_PATH];

	virtual void Free();
};
END
#define __TOOLSTAGE1_H__
#endif
