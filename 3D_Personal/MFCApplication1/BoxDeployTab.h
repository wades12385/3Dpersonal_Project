#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "NaviObj.h"
#ifndef __MFCBOXDEPLOYTAB_H__



// CBoxDeployTab 대화 상자입니다.
USING(Engine)
class CBoxDeployTab : public CDialog
{
	DECLARE_DYNAMIC(CBoxDeployTab)

public:
	CBoxDeployTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBoxDeployTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOXDEPLOYTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetUp_Tree(const CString& NavName);
public:
	CNaviObj*			m_pNavMesh;
	list<CGameObject*>*  m_pNavObjList;
	_uint				m_iNavMeshIdx;
public:
	CButton m_rbClickOption[eClickOption::End];
	CButton m_rbCreateOption[eBoxType::End];
	CTreeCtrl m_NavTreeCtrl;
	CString m_sSelectNaviName;
	BOOL m_cbSelected_Navi;
	CString m_sSacle[eFloat3::End];
	CString m_sPos[eFloat3::End];
	CListBox m_lbCollsionList;
	CListBox m_lbTriggerList;

	afx_msg void OnBnClickedButtonNaviLoad();
	afx_msg void OnBnClickedButtonNaviDelete();
	afx_msg void OnBnClickedCreateBox();
	afx_msg void OnBnClickedPeekingBox();
	afx_msg void OnBnClickedClearColBox();
	afx_msg void OnBnClickedSaveColBox();
	afx_msg void OnBnClickedLoadColBox();
	afx_msg void OnBnClickedClearTri();
	afx_msg void OnBnClickedSaveTriBox();
	afx_msg void OnBnClickedLoadTriBox();
	afx_msg void OnDeltaposSpinSacleX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult);

};
#define __MFCBOXDEPLOYTAB_H__
#endif // !__MFCBOXDEPLOYTAB_H__
