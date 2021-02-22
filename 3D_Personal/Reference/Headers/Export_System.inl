


//Timer
inline _float Get_TimeDelta(const _tchar * pTimerTag)
{
	return CTime_Manager::Get_Instance()->Get_TimeDelta(pTimerTag);
}

inline void Set_TimeDelta(const _tchar * pTimerTag)
{
	CTime_Manager::Get_Instance()->Set_TimeDelta(pTimerTag);
}

inline HRESULT Ready_Timer(const _tchar * pTimerTag)
{
	return CTime_Manager::Get_Instance()->Ready_Timer(pTimerTag);
}

//Frame
inline _bool IsPermit_Call(const _tchar * pFrameTag, const _float & fTimeDelta)
{
	return CFrame_Manager::Get_Instance()->IsFrameLimit(pFrameTag,fTimeDelta);
}

inline HRESULT Ready_Frame(const _tchar * pFrameTag, const _float & fCallLimit)
{
	return CFrame_Manager::Get_Instance()->Ready_Frame(pFrameTag,fCallLimit);
}


//font

inline HRESULT Ready_Font(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFontTag, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	return CFont_Manager::Get_Instance()->Ready_Font(pDevice, pFontTag, pFontType, iWidth, iHeight, iWeight);
}

inline void Render_Font(const _tchar * pFontTag, const _tchar * pString, const _vec2 * pPos, D3DXCOLOR Color)
{
	CFont_Manager::Get_Instance()->Render_Font(pFontTag, pString, pPos, Color);
}

//Input

inline _bool KeyDown(_ubyte byKey)
{
	return CDXInput::Get_Instance()->KeyDown(byKey);
}

inline _bool KeyUp(_ubyte byKey)
{
	return  CDXInput::Get_Instance()->KeyUp(byKey);
}

inline _bool KeyPress(_ubyte byKey)
{
	return CDXInput::Get_Instance()->KeyPress(byKey);
}

inline _byte Get_DIMouseState(MOUSEKEYSTATE eMouse)
{
	return CDXInput::Get_Instance()->Get_DIMouseState(eMouse);
}

inline _long Get_DIMouseMove(MOUSEMOVESTATE eMouseState)
{
	return CDXInput::Get_Instance()->Get_DIMouseMove(eMouseState);
}

inline HRESULT Ready_DXInput(HINSTANCE hInst, HWND hWnd)
{
	return CDXInput::Get_Instance()->Ready_DXInput(hInst, hWnd);
}

inline void Update_InputDev(void)
{
	return CDXInput::Get_Instance()->Update_InputDev();
}

inline HRESULT Add_Light(LPDIRECT3DDEVICE9 pDevice, const D3DLIGHT9 * pLightInfo, const _uint & iIndex)
{
	return  CLight_Manager::Get_Instance()->Add_Light(pDevice, pLightInfo, iIndex);;
}

inline void Release_Engine()
{ 
	CLight_Manager::Get_Instance()->Release_Instance(); 
	CDXInput::Get_Instance()->Release_Instance();
	CFont_Manager::Get_Instance()->Release_Instance();
	CFrame_Manager::Release_Instance();
	CTime_Manager::Release_Instance();
}
