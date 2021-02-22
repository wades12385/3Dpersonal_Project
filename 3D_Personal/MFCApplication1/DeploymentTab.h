#pragma once


// CObjectTab 대화 상자입니다.

class CDeploymentTab : public CDialog
{
	DECLARE_DYNAMIC(CDeploymentTab)

public:
	CDeploymentTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDeploymentTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DEPLOYMENTTAB
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
