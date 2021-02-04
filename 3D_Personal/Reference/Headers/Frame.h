#pragma once
#ifndef __FRAME_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CFrame : public CBase
{
private:
	explicit CFrame();
	virtual ~CFrame() = default;
public:
	_bool			IsFrameLimit(const _float& fTimeDeleta);
	HRESULT			Ready_Frame(const _float& fLimitFPS);
private:
	_float				m_fLimitFrame;
	_float				m_fTime;
	virtual void		Free(void);
public:
	static CFrame*		Create(const _float& dCallLimit);
};
END
#define  __FRAME_H__
#endif
