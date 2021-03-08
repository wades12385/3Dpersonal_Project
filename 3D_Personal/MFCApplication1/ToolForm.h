#pragma once
#include "afxcmn.h"
#include "NaviModifyTab.h"
#include "staticDeploymentTab.h"
#include "BoxDeployTab.h"
// CToolForm 폼 뷰입니다.

class CToolForm : public CFormView
{
	DECLARE_DYNCREATE(CToolForm)

protected:
	CToolForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CToolForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	CStaticDeploymentTab m_StaticDeployTab;
	CNaviModifyTab m_NaviModifyTab;
	CBoxDeployTab  m_BoxDeployTab;
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};


