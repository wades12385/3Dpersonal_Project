
// MFCApplication1.h : MFCApplication1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


USING(Engine)
// CMFCApplicationApp:
// �� Ŭ������ ������ ���ؼ��� MFCApplication1.cpp�� �����Ͻʽÿ�.
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	virtual int Run();
};

extern CMFCApplicationApp theApp;
