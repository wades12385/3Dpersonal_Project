#pragma once
#ifndef __MFCCOLBOXDEPLOY_H__
#include "Scene.h"
USING(Engine)
class CBoxDeployScene : public CScene
{
private:
	explicit CBoxDeployScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CBoxDeployScene() = default;

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize_Scene() override;
	virtual HRESULT ReInitialize_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(const _float & fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float & fTimeDeleta) override;
	virtual void Render_Scene() override;

	static CBoxDeployScene* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free();

};

#define __MFCCOLBOXDEPLOY_H__
#endif
