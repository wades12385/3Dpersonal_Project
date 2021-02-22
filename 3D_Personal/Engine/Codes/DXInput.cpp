#include "DXInput.h"


USING(Engine)
IMPLEMENT_SINGLETON(CDXInput)
CDXInput::CDXInput()
{
}
HRESULT CDXInput::Ready_DXInput(HINSTANCE hInst, HWND hWnd)
{
	// DInput 컴객체를 생성하는 함수
	FAILED_CHECK(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL));

	// 키보드 객체 생성
	FAILED_CHECK(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr));

	// 생성된 키보드 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 장치에 대한 독점권을 설정해주는 함수, (클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pKeyBoard->Acquire();


	// 마우스 객체 생성
	FAILED_CHECK(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr));

	// 생성된 마우스 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 장치에 대한 독점권을 설정해주는 함수, 클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pMouse->Acquire();

	ZeroMemory(m_byKeyDown ,sizeof(_bool) * 256);
	ZeroMemory(m_byKeyUp, sizeof(_bool) * 256);

	return S_OK;
}
void CDXInput::Update_InputDev()
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}
_bool CDXInput::KeyDown(_ubyte byKey)
{
	if (m_byKeyState[byKey] & 0x80 && (m_byKeyDown[byKey] == false))
	{
		m_byKeyDown[byKey] = true;
		return true;
	}
	else if (!(m_byKeyState[byKey] & 0x80) && m_byKeyDown[byKey])
	{
		m_byKeyDown[byKey] = false;
		return false;
	}

	return false;
}
_bool CDXInput::KeyUp(_ubyte byKey)
{
	if (m_byKeyState[byKey] & 0x80)
	{
		m_byKeyUp[byKey] = true;
		return false;
	}
	else if (m_byKeyUp[byKey] )
	{
		m_byKeyUp[byKey] = false;
		return true;
	}
	return false;
}
_bool CDXInput::KeyPress(_ubyte byKey)
{
	if (m_byKeyState[byKey] & 0x80)
		return true;
	return false;
}
void CDXInput::Free()
{
	SafeRelease(m_pKeyBoard);
	SafeRelease(m_pMouse);
	SafeRelease(m_pInputSDK);
}
