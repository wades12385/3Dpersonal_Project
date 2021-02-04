#include "Timer.h"

USING(Engine)
CTimer::CTimer()
	:m_fTimeDelta(0.f)
{
}

HRESULT CTimer::Ready_Timer(void)
{
	QueryPerformanceCounter(&m_FrameTime);	
	QueryPerformanceCounter(&m_LastTime);	
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

void CTimer::SetUp_TimeDelta(void)
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}

	m_fTimeDelta = _float(m_FrameTime.QuadPart - m_LastTime.QuadPart) / (_float)m_CpuTick.QuadPart;

	m_LastTime = m_FrameTime;
}

CTimer*  CTimer::Create(void)
{
	CTimer* pInstance = new CTimer();
	pInstance->Ready_Timer();
	return pInstance;
}

void CTimer::Free(void)
{
}
