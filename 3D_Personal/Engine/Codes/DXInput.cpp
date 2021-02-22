#include "DXInput.h"


USING(Engine)
IMPLEMENT_SINGLETON(CDXInput)
CDXInput::CDXInput()
{
}
HRESULT CDXInput::Ready_DXInput(HINSTANCE hInst, HWND hWnd)
{
	// DInput �İ�ü�� �����ϴ� �Լ�
	FAILED_CHECK(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL));

	// Ű���� ��ü ����
	FAILED_CHECK(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr));

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	FAILED_CHECK(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr));

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
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
