#pragma once
#ifndef __TOOLVIEW_H__
#include "Base.h"
USING(Engine)
class CDirectApp final : public CBase
{
	DECLARE_SINGLETON(CDirectApp)

public:
	explicit CDirectApp();
	virtual ~CDirectApp() = default;

	HRESULT ReadyEngine(HWND hWnd);
	void Running(_float& fTimeDelta);
	void ShowFPS(_float& fTimeDelta);

	virtual void Free()override;

	void Ready_ProtoType();
	CManagement* m_pManagement;
	_int		m_iFPS;
	_float		m_fTime;
	_tchar		m_szFPS[16];
};

#define __TOOLVIEW_H__
#endif
