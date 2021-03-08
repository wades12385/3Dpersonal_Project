#pragma once
#ifndef __OBJECTDEPLOY_H__
#include "Scene.h"
USING(Engine)
class CStaticDeployScene : public CScene
{
public:
	explicit CStaticDeployScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStaticDeployScene() = default;

	virtual HRESULT Initialize_Scene() override;
	virtual HRESULT ReInitialize_Scene() override;
	virtual HRESULT Ready_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual _uint Update_Scene(const _float & fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float & fTimeDeleta) override;
	virtual void Render_Scene() override;

	static CStaticDeployScene* Create(LPDIRECT3DDEVICE9 pDevice);

	virtual void Free() override;
};

#define __OBJECTDEPLOY_H__
#endif
/*
테이블 기반으로 트랜스폼과 옵션값을 가져와서 오브젝트 세팅후 배치 (내비메쉬 깔아서 )







*/