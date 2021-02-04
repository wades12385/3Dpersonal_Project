
USING(Engine)
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

inline _bool IsPermit_Call(const _tchar * pFrameTag, const _float & fTimeDelta)
{
	return CFrame_Manager::Get_Instance()->IsFrameLimit(pFrameTag,fTimeDelta);
}

inline HRESULT Ready_Frame(const _tchar * pFrameTag, const _float & fCallLimit)
{
	return CFrame_Manager::Get_Instance()->Ready_Frame(pFrameTag,fCallLimit);
}

inline void Release_Engine()
{
	CFrame_Manager::Release_Instance();
	CTime_Manager::Release_Instance();
}
