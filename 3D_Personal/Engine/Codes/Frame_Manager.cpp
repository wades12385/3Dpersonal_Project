#include "Frame_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFrame_Manager)

CFrame_Manager::CFrame_Manager()
{
}

CFrame_Manager::~CFrame_Manager()
{
}

_bool CFrame_Manager::IsFrameLimit(const _tchar * pFrameTag, const _float & fTimeDelta)
{
	CFrame*  pInstance = Find_Frame(pFrameTag);
	NULL_CHECK_RETURN(pInstance, false);
	return pInstance->IsFrameLimit(fTimeDelta);
}

HRESULT CFrame_Manager::Ready_Frame(const _tchar * pFrameTag, const _float & fCallLimit)
{
	CFrame* 	pFrame = Find_Frame(pFrameTag);

	if (nullptr != pFrame)
		return E_FAIL;

	pFrame = CFrame::Create(fCallLimit);
	NULL_CHECK_RETURN(pFrame, E_FAIL);

	m_mapFrame.emplace(pFrameTag, pFrame);

	return S_OK;
}

CFrame* CFrame_Manager::Find_Frame(const _tchar * pFrameTag)
{
	auto	iter = find_if(m_mapFrame.begin(), m_mapFrame.end(), CTagFinder(pFrameTag));

	if (iter == m_mapFrame.end())
		return nullptr;

	return iter->second;
}

void CFrame_Manager::Free(void)
{
	for_each(m_mapFrame.begin(), m_mapFrame.end(), CDeleteMap());
	m_mapFrame.clear();
}
