#pragma once

#ifndef __NAVIMODITYTAB_H__
#include "NaviObj.h"
#include "afxcmn.h"
#include "afxwin.h"

// CNaviModifyTab 대화 상자입니다.

class CNaviModifyTab : public CDialog
{
	DECLARE_DYNAMIC(CNaviModifyTab)

public:
	CNaviModifyTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNaviModifyTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAVIMODIFYTAB };
#endif
	CNaviObj*		     m_pNavMesh;
	CStaticMesh*		 m_pStaticMesh;
	_bool				 m_bHideSwitch = false;
	_bool				 m_bNowPeeking = false;
	_int				 m_iPeekVtxIdx;
	_int				 m_iPeekCellIdx;


	BOOL				 m_bVtxModing;
	BOOL				 m_bHide_ComboBox;
	list<CGameObject*>*  m_pListNavMeshObj;
	_int				 m_iNavMeshIdx;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked_ObjLoad();
	afx_msg void OnBnClickedStaticLoad();
	afx_msg void OnBnClickedNavMeshModing();
	afx_msg void OnBnClickedHideBtn();

	afx_msg void OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

//////////////////////////////////////////////////////////////////////////
	void				SetUp_Tree(const CString& strName);
	void				Update_NaviModityTab();
	void				ShowText_Vtx(int idx);
	void				ShowText_Cell();
	void				Update_VtxPosEdit(_vec3 vPos);
	_uint				Get_CellType();
	CNaviObj*		    Find_NavMeshFromLayer();
	void				SetUp_HideOption();
	void				LineID_CheckBoxClear();

	void				Enable_LineOption(const _bool& bEnable);
//////////////////////////////////////////////////////////////////////////
	CString m_cPeekingVtxIdx;
	CString m_cPeekingCellIdx;

	CString m_sPosX;
	CString m_sPosY;
	CString m_sPosZ;

	CString m_sColorR;
	CString m_sColorG;
	CString m_sColorB;

	CSpinButtonCtrl m_spPosX;
	CSpinButtonCtrl m_spPosY;
	CSpinButtonCtrl m_spPosZ;

	CButton			m_PeekingBnt[2];
	CButton			m_CellTypeBnt[eCellType::End];

	CTreeCtrl m_NavTreeCtrl;
	CString m_sNaviID;
	CString m_sSelectNavName;

	// line option group
	CEdit m_edNextNavID;
	CEdit m_edConnectIdx;
	BOOL m_cbLineID[eLineID::End]; 
	CButton m_LineTypeBnt[eCellType::End];

	BOOL m_cbHideCell;
	BOOL m_cbHideVtx;
	BOOL m_cbModifyOption;
	afx_msg void OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedClearTree();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonColorSetUp();
	afx_msg void OnBnClickedDeleteNavMesh();
	afx_msg void OnBnClicked_HideCell();
	afx_msg void OnBnClicked_HideVtx();
	afx_msg void OnBnClicked_LineTypeBase();
	afx_msg void OnBnClicked_LineTypeLeave();
	afx_msg void OnBnClicked_LineTypeConnect();
	afx_msg void OnBnClicked_LineOptionApply();
	afx_msg void OnBnClickedNavMeshSave();
	afx_msg void OnBnClicked_DatLoad();
};

#define __NAVIMODITYTAB_H__
#endif
