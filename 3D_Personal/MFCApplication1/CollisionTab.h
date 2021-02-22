#pragma once


// CCollisionTab 대화 상자입니다.

class CCollisionTab : public CDialog
{
	DECLARE_DYNAMIC(CCollisionTab)

public:
	CCollisionTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCollisionTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLISIONTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
