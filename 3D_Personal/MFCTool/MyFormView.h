#pragma once
#include "NaviMeshTap.h"

// CMyFormView 대화 상자

class CMyFormView : public CFormView
{
	DECLARE_DYNAMIC(CMyFormView)

public:
	CMyFormView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMyFormView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyFormView };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	CNaviMeshTap m_DiaNaviMesh;
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};
