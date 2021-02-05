#pragma once


// CNaviMeshTap 대화 상자

class CNaviMeshTap : public CDialog
{
	DECLARE_DYNAMIC(CNaviMeshTap)

public:
	CNaviMeshTap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNaviMeshTap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NaviMeshTap };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	DECLARE_MESSAGE_MAP()
};
