
// MFCApplication1.h : MFCApplication1 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
#endif

#include "resource.h"       // 주 기호입니다.


USING(Engine)
// CMFCApplicationApp:
// 이 클래스의 구현에 대해서는 MFCApplication1.cpp을 참조하십시오.
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	virtual int Run();
};

extern CMFCApplicationApp theApp;
