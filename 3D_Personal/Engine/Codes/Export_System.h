#ifndef __EXPORT_SYSTEM_H__
#include "Engine_Define.h"
#include "Time_Manager.h"
#include "Frame_Manager.h"
#include "Font_Manager.h"
#include "DXInput.h"
#include "Light_Manager.h"

BEGIN(Engine)
// Timer
inline _float		Get_TimeDelta(const _tchar* pTimerTag);
inline void			Set_TimeDelta(const _tchar* pTimerTag);
inline	HRESULT		Ready_Timer(const _tchar* pTimerTag);

// Frame
inline _bool		IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
inline HRESULT		Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);

//Font
inline HRESULT		Ready_Font(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
inline void			Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color);

// DInput
inline _bool		KeyDown(_ubyte byKey);
inline _bool		KeyUp(_ubyte byKey);
inline _bool		KeyPress(_ubyte byKey);
 
inline _byte		Get_DIMouseState(MOUSEKEYSTATE eMouse);
inline _long		Get_DIMouseMove(MOUSEMOVESTATE eMouseState);

inline	HRESULT		Ready_DXInput(HINSTANCE hInst, HWND hWnd);
inline	void		Update_InputDev(void);

//lgiht
inline HRESULT  Add_Light(LPDIRECT3DDEVICE9 pDevice, const D3DLIGHT9* pLightInfo, const _uint& iIndex);

inline void Release_Engine();

#include "Export_System.inl"

END

#define __EXPORT_SYSTEM_H__
#endif
