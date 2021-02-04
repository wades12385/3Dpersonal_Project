#include "Time_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTime_Manager)

CTime_Manager::CTime_Manager()
{
}

_float CTime_Manager::Get_TimeDelta(const _tchar * pTimerTag)
{
	CTimer*	pTimer = Find_Timer(pTimerTag);

	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

void CTime_Manager::Set_TimeDelta(const _tchar * pTimerTag)
{
	CTimer* 	pTimer = Find_Timer(pTimerTag);

	if (nullptr == pTimer)
		return;

	pTimer->SetUp_TimeDelta();
}

HRESULT CTime_Manager::Ready_Timer(const _tchar * pTimerTag)
{
	if (Find_Timer(pTimerTag) != nullptr)
		return E_FAIL;

	CTimer* pTimer = CTimer::Create();
	NULL_CHECK_RETURN(pTimer, E_FAIL);

	m_mapTimers.emplace(pTimerTag, pTimer);
	return S_OK;
}

CTimer* CTime_Manager::Find_Timer(const _tchar * pTimerTag)
{
	auto	iter = find_if(m_mapTimers.begin(), m_mapTimers.end(), CTagFinder(pTimerTag));

	if (iter == m_mapTimers.end())
		return nullptr;

	return (*iter).second;
}

void CTime_Manager::Free()
{
	for_each(m_mapTimers.begin(), m_mapTimers.end(), CDeleteMap());
	m_mapTimers.clear();
}
