#pragma once
#ifndef __RENDERER_H__
#include "Base.h"
BEGIN(Engine)

/* 렌더링 그룹화 해서 할거임 */
class CGameObject;
class CRenderer final : public CBase
{
private:
	explicit CRenderer(const LPDIRECT3DDEVICE9 pDevice);
	virtual ~CRenderer() = default;

public:
	HRESULT Add_Renderer(eRenderID eID, CGameObject* pGameObject);
	HRESULT Render(HWND hWnd = nullptr);

private:
	HRESULT RenderPriority();
	HRESULT RenderNoAlpha();
	HRESULT RenderAlpha();
	HRESULT RenderUI();
public:
	static CRenderer* Create(const LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	typedef list<CGameObject*> GAMEOBJECTS;
	LPDIRECT3DDEVICE9	m_pDevice;
	GAMEOBJECTS	m_GameObjects[(_uint)eRenderID::End];
};
END

#define __RENDERER_H__
#endif