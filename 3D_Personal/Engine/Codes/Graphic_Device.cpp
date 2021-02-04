#include "Graphic_Device.h"

USING(Engine)

IMPLEMENT_SINGLETON(CGraphic_Device)

// 스레드 플래그 추가해야함  [2/3/2021 Administrator]

CGraphic_Device::CGraphic_Device()
	: m_pSDK(nullptr)
	, m_pDevice(nullptr)
{
}

HRESULT CGraphic_Device::Ready_Graphic_Device(HWND hWnd, _uint iWinCX, _uint iWinCY, eWinMode eDisplayMode)
{
	D3DCAPS9 DeviceCaps; 
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9)); 

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION); 

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX(L"GetDevice Caps Failed");
		return E_FAIL;
	}
	DWORD vp = 0; 
	if (DeviceCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING ;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; 

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); 
	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality= 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = (BOOL)eDisplayMode;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX(L"GraphicDevice Creating Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CGraphic_Device::Render_Begine(D3DXCOLOR Color)
{
	m_pDevice->Clear(0,
		nullptr,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		Color,1.f,0);

	m_pDevice->BeginScene();

}

void CGraphic_Device::Render_End(HWND hTargetHwnd)
{
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, hTargetHwnd, NULL);
}

void CGraphic_Device::Free()
{
	if (SafeRelease(m_pDevice))
	{
		MSG_BOX(L"Failed To Release m_pDevice");
	}

	if(SafeRelease(m_pSDK))
	{
		MSG_BOX(L"Failed To Releasing m_pSDK");
	}
}
