#pragma once
#ifndef __FRAMEMANANGER_H__
#include "Frame.h"

BEGIN(Engine)
class ENGINE_DLL CFrame_Manager : public CBase
{
	DECLARE_SINGLETON(CFrame_Manager)
private:
	explicit CFrame_Manager();
	virtual ~CFrame_Manager();
public:
	_bool				IsFrameLimit(const _tchar* pFrameTag, const _float& fTimeDelta);

public:
	HRESULT				Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);
private:
	CFrame* 			Find_Frame(const _tchar* pFrameTag);
private:
	unordered_map<const _tchar*, CFrame*>		m_mapFrame;

public:
	virtual void Free(void);
};
END
#define  __FRAMEMANANGER_H__
#endif
