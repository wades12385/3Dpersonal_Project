#pragma once


// CCollisionTab ��ȭ �����Դϴ�.

class CCollisionTab : public CDialog
{
	DECLARE_DYNAMIC(CCollisionTab)

public:
	CCollisionTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCollisionTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLISIONTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
