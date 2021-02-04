#include "Frame.h"

USING(Engine)
CFrame::CFrame()
	:m_fTime(0.f)
	, m_fLimitFrame(0.f)
{
}

_bool CFrame::IsFrameLimit(const _float & fTimeDeleta)
{
	m_fTime += fTimeDeleta;
	if (m_fTime >= m_fLimitFrame)
	{
		m_fTime = 0.f;
		return true;
	}

	return false;
}

HRESULT CFrame::Ready_Frame(const _float & fLimitFPS)
{
	m_fLimitFrame = 1.f / fLimitFPS;
	return S_OK;
}

void CFrame::Free(void)
{
}

CFrame* CFrame::Create(const _float & dCallLimit)
{
	CFrame*	pInstance = new CFrame();
	pInstance->Ready_Frame(dCallLimit);
	return pInstance;
}

