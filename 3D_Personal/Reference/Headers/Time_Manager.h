#pragma once
#ifndef __TIME_MANAGER_H__
#include "Timer.h"
BEGIN(Engine)
class ENGINE_DLL CTime_Manager final : public CBase
{
	DECLARE_SINGLETON(CTime_Manager)
private:
	explicit CTime_Manager();
	virtual ~CTime_Manager() = default;

public:
	_float					Get_TimeDelta(const _tchar* pTimerTag);
	void					Set_TimeDelta(const _tchar* pTimerTag);

	HRESULT					Ready_Timer(const _tchar* pTimerTag);
	CTimer*					Find_Timer(const _tchar* pTimerTag);
	
private:
	unordered_map<const _tchar*, CTimer*> m_mapTimers;
	virtual void Free() override;
};
END

#define __TIME_MANAGER_H__
#endif