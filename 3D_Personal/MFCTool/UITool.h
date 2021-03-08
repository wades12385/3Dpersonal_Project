#pragma once
#include "UIPresetForm.h"

// CUITool 대화 상자

class CUITool : public CDialog
{
	DECLARE_DYNAMIC(CUITool)

public:
	CUITool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUITool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUITool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void RenderPicCtrl();

public:
	list<UI_PRESET_INFO*> m_listUIPreset;

	CUIPresetForm m_UIPresetForm;
	afx_msg void OnBnClickedCreatePreset();

	CButton m_RadioPreset[3];
	virtual BOOL OnInitDialog();

	CListBox m_ListBoxPreset;
	CStatic m_PicPresetPreview;
	afx_msg void OnLbnSelchangePresets();
	float m_XPosEdit;
	float m_YPosEdit;
	afx_msg void OnBnClickedInsert();
};
