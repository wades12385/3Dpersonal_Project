#pragma once
#ifndef __MAINAPP_H__

#include "Base.h"

USING(Engine)
class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT ReadyMainApp();

public:
	void Running(const _float& fTimeDelta);

private:
	HRESULT ReadyStaticResources();
	void	ShowFPS(const _float& fTimeDelta);
public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	CManagement* m_pManagement;
	LPDIRECT3DDEVICE9 m_pDevice;

	_int		m_iFPS;
	_float		m_fTime;
	_tchar		m_szFPS[64];
};
#define __MAINAPP_H__
#endif