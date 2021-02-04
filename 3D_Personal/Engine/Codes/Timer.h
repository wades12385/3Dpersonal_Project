#pragma once
#ifndef __TIMER_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CTimer : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer() = default;
public:
	_float		Get_TimeDelta(void) { return m_fTimeDelta; }
public:
	HRESULT		Ready_Timer(void);
	void		SetUp_TimeDelta(void);

private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;
	LARGE_INTEGER		m_CpuTick;

private:
	_float				m_fTimeDelta;

public:
	static	CTimer*		Create(void);
	virtual void		Free(void);
};
END
#define __TIMER_H__
#endif
