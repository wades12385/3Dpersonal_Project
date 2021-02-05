#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// UnitData
	CListBox m_ListBoxMob;
	CListBox m_ListBoxAdded;
	CButton m_Radio[3];
	CStatic m_PicUnit;
	int m_iAtkEdit;
	int m_iDefEdit;


	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioNPC();
	afx_msg void OnBnClickedRadioMonster();
	afx_msg void OnBnClickedRadioBoss();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDelete();

	afx_msg void OnLbnSelchangeMob();
	afx_msg void OnLbnSelchangePlace();

	void ChangePickedObjPos(const _vec3& _vPos);

private:
	void InitMapUnit();

};
