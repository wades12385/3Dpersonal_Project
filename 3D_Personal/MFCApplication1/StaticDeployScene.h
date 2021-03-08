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
���̺� ������� Ʈ�������� �ɼǰ��� �����ͼ� ������Ʈ ������ ��ġ (����޽� ��Ƽ� )







*/