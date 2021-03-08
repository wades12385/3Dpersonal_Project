#pragma once
#include "MfcStaticItem.h"
#include "NaviObj.h"
#include "Axis.h"
#include "SizeCheck.h"
#include "afxwin.h"
// CObjectTab 대화 상자입니다.

class CStaticDeploymentTab : public CDialog
{
	DECLARE_DYNAMIC(CStaticDeploymentTab)

public:
	void		SetUp_DataTable();
	void		Update_ObjInfo(_int& iIdx);
	void		SetUp_Tool();
	void		Peeking(const CPoint& vPos);

	void        Create_Obj(const CPoint& vPos);
	void        Delete_Obj(const CPoint& vPos);
	void        Modify_Obj(const CPoint& vPos);
public:
	vector<OBJDATA>*			m_pDataTable;
	_int						m_iTableIdx;
	CMfcStaticItem*				m_pObjItem = nullptr;
	list<CGameObject*>*		    m_plistObj = nullptr;


	CAxis*						m_pAxis = nullptr;
	CSizeCheck*					m_pSize = nullptr;
	CNaviObj*					m_pNavObj = nullptr;
	list<CGameObject*>*		    m_pListNavMeshObj = nullptr;
	_int						m_iSelectNaviIdx;

public:
	CStaticDeploymentTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStaticDeploymentTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_OBJECTTAB
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lcStaticTable;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchange_NaviMesh();
	afx_msg void OnNMClickList_Table(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_sScale;
	CString m_sSize;
	CString m_sObjTag;
	CString m_sWeight;
	CButton m_cbFloating;
	CButton m_cbDecoration;
	CButton m_cbStationary;
	afx_msg void OnBnClicked_TableApply();
	afx_msg void OnBnClicked_NaviLoad();
	CListBox m_lbNaviMeshs;
	CString m_sSelectNaviID;
	CString m_sSelectNaviName;
	CButton m_rbPeektype[eStaticItemPeek::End];
	CString m_sPeekingItem;
	afx_msg void OnEnChange_Sacle();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClicked_SizeCheck();
	CString m_sSizeCheck;
	afx_msg void OnEnChange_SizeText();
	afx_msg void OnDeltaposSpin_SizeCheck(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_sPos[eFloat3::End];
	CEdit m_edPos[eFloat3::End];


	CEdit m_edScale;
	CEdit m_edSizeCheck;
};
