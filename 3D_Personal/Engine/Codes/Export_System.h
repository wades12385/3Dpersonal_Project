#ifndef __EXPORT_SYSTEM_H__
#include "Time_Manager.h"
#include "Frame_Manager.h"
BEGIN(Engine)

// Timer
inline _float		Get_TimeDelta(const _tchar* pTimerTag);
inline void			Set_TimeDelta(const _tchar* pTimerTag);
inline	HRESULT		Ready_Timer(const _tchar* pTimerTag);

// Frame
inline _bool		IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
inline HRESULT		Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);

inline void Release_Engine();

#include "Export_System.inl"
END

#define __EXPORT_SYSTEM_H__
#endif
