#pragma once


// CObjectTab ��ȭ �����Դϴ�.

class CDeploymentTab : public CDialog
{
	DECLARE_DYNAMIC(CDeploymentTab)

public:
	CDeploymentTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeploymentTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DEPLOYMENTTAB
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
