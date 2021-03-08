#pragma once
#ifndef __TESTSCENE_H__
#include "Scene.h"
USING(Engine)
class CTestScene : public CScene
{
public:
	explicit CTestScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CTestScene() = default;

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize_Scene() override;
	virtual HRESULT ReInitialize_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(const _float & fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float & fTimeDeleta) override;
	virtual void Render_Scene() override;
private:
	_bool						m_bNaviMeshRender;

private:
	virtual void Free()override;
public:
	static CTestScene* Create(LPDIRECT3DDEVICE9 pDevice);
};
#define __TESTSCENE_H__
#endif
