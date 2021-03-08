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
	void				SetUp_Tree(const CString& strName ,const CNaviObj* pMesh);
	void				ShowText_Vtx(int idx);
	void				ShowText_Cell(int idx);
	void				Update_VtxPosEdit(_vec3 vPos);
	//체크한 셀옵션 버튼 인덱스 반환 
	CNaviObj*		    Find_NavMeshFromLayer();
	void				SetUp_HideOption();
	void				Peeking(const CPoint& point);

	void				Enable_LineOption(const _bool& bEnable);
	void				Enable_LineOption_Connect(const _bool& bEnable);

	void				Enable_CellOption(const _bool& bEnable);
	void				Enable_CellOption_Connect(const _bool& bEnable);

	void				Update_CellLinkListBox(const _int& iCellIdx);
	void				Update_LineLinkListBox(const _int& iCellIdx , const eLineID::eLineID& eLineID);

	void				ReSet_LineBtn();
	void				ReSet_LineTypeBtn();


	void				Setup_LineOfLink(CCell* pCell,const _int& iLineID); // listbox 내용을 lineLink백터 컨테이너로 
//////////////////////////////////////////////////////////////////////////
	CString m_sPeeking_VtxIdx;
	CString m_sPeeking_CellIdx;

	CString m_sPosX;
	CString m_sPosY;
	CString m_sPosZ;

	CString m_sColorR;
	CString m_sColorG;
	CString m_sColorB;

	CSpinButtonCtrl m_spPosX;
	CSpinButtonCtrl m_spPosY;
	CSpinButtonCtrl m_spPosZ;

	CButton			m_PeekingBnt[ePeekingMod::End];

	CTreeCtrl m_NavTreeCtrl;
	CString m_sNaviID;
	CString m_sSelectNavName;
	//Cell option Group
	CListBox m_lbCellLink;
	CString m_sCellOptionID;
	CString m_sCellOptionIdx;

	// line option group
	CButton m_rbLine[eLineID::End];
	CButton m_rbLineType[eCellType::End];
	CListBox m_lbLineLink;
	CString m_sLineOptionID;
	CString m_sLineOptionIdx;

	BOOL m_cbHideCell;
	BOOL m_cbHideVtx;
	afx_msg void OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedClearTree();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedNaviMeshOption();
	afx_msg void OnBnClickedDeleteNavMesh();
	afx_msg void OnBnClicked_HideCell();
	afx_msg void OnBnClicked_HideVtx();
	afx_msg void OnBnClickedLineOption_AddLinkCell();
	afx_msg void OnBnClickedNavMeshSave();
	afx_msg void OnBnClicked_DatLoad();
	afx_msg void OnBnClicked_LineOptionApply();
	afx_msg void OnBnClickedCellTypeBase();
	afx_msg void OnBnClickedCellTypeConnect();
	
	afx_msg void OnBnClickedCellOption_AddLinkCell();
	afx_msg void OnBnClickedCellOption_DeleteLinkCell();
	afx_msg void OnBnClickedCellOption_Clear();
	afx_msg void OnBnClickedLineOption_DeleteLinkCell();
	afx_msg void OnBnClickedLineOption_Clear();
	afx_msg void OnBnClicked_LineAB();
	afx_msg void OnBnClicked_LineBC();
	afx_msg void OnBnClicked_Line_CA();
	afx_msg void OnBnClicked_LineTypeBase();
	afx_msg void OnBnClicked_LineTypeLeave();
	afx_msg void OnBnClicked_LineTypeConnect();
};

#define __NAVIMODITYTAB_H__
#endif
