#pragma once
#ifndef __LOGO_H___
#include "Scene.h"
USING(Engine)
class CLogo final : public CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLogo() = default;
	virtual HRESULT Initialize_Scene() override;
	virtual HRESULT Awake_Scene() override;
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(const _float& fTimeDeleta) override;
	virtual _uint LateUpdate_Scene(const _float& fTimeDeleta) override;
	virtual void Render_Scene() override;

private:
	virtual void Free() override;
public:
	static CLogo* Create(LPDIRECT3DDEVICE9 pDevice);
};

#define __LOGO_H___
#endif
