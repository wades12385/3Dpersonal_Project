#pragma once
#ifndef __MFCCOLBOXDEPLOY_H__
#include "Scene.h"
USING(Engine)
class CColBoxDeployScene : public CScene
{
private:
	explicit CColBoxDeployScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CColBoxDeployScene() = default;

public:

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(const _float & fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float & fTimeDeleta) override;
	virtual void Render_Scene() override;

	static CColBoxDeployScene* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free();



};

#define __MFCCOLBOXDEPLOY_H__
#endif
