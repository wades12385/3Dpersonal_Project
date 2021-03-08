#pragma once
#ifndef __LOADING_H__
#include "Base.h"
class CLoading : public CBase
{
public:
	explicit CLoading(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLoading() = default;
public:
	HRESULT Ready_Loading(const eLoadID::eLoadID& eLoadID);
	_uint	Loading_Test();

public:
	CRITICAL_SECTION*	Get_CrtKey() { return &m_CrtKey; }
	_bool				Get_Finish()  { return m_bFinish; }
	const eLoadID::eLoadID& 				Get_LoadingID() { return m_eLoadID; }
	const _tchar*		Get_String(void) const { return m_szLoading; }

public:
	static unsigned int CALLBACK Loading_thread(void* pArg);
	static CLoading* Create(LPDIRECT3DDEVICE9 pDevice,const eLoadID::eLoadID& eLoadID);
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_CrtKey;
	eLoadID::eLoadID	m_eLoadID;
	_bool				m_bFinish;
	_tchar				m_szLoading[256];
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;

private:
	virtual void Free() override;
};
#define __LOADING_H__
#endif
