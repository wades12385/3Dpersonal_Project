#pragma once
#ifndef __DXINPUT_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CDXInput : public CBase
{
	DECLARE_SINGLETON(CDXInput)
public:
	explicit CDXInput();
	virtual ~CDXInput()= default;
public:
	HRESULT Ready_DXInput(HINSTANCE hInst, HWND hWnd);
	void	Update_InputDev();

public:
	_byte	Get_DIKeyState(_ubyte byKeyID) { return m_byKeyState[byKeyID]; }
	_byte	Get_DIMouseState(MOUSEKEYSTATE eMouse) { return m_tMouseState.rgbButtons[eMouse]; }
	_long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState) { return *(((_long*)&m_tMouseState) + eMouseState); }
	_bool	KeyDown(_ubyte byKey);
	_bool	KeyUp(_ubyte byKey);
	_bool	KeyPress(_ubyte byKey);
private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse = nullptr;

	_byte					m_byKeyState[256];
	_bool					m_byKeyDown[256];
	_bool					m_byKeyUp[256];

	DIMOUSESTATE			m_tMouseState;

private:
	virtual void Free() override;
};
END
#define __DXINPUT_H__
#endif
