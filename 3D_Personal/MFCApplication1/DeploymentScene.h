#pragma once
#ifndef __OBJECTDEPLOY_H__
#include "Scene.h"
class CDeploymentScene : public CScene
{
public:
	explicit CDeploymentScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CDeploymentScene();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual _uint Update_Scene(const _float & fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float & fTimeDeleta) override;
	virtual void Render_Scene() override;
};

#define __OBJECTDEPLOY_H__
#endif
