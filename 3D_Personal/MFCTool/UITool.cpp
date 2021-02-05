// UITool.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UITool.h"
#include "afxdialogex.h"


// CUITool 대화 상자

IMPLEMENT_DYNAMIC(CUITool, CDialog)

CUITool::CUITool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUITool, pParent)
	, m_XPosEdit(0)
	, m_YPosEdit(0)
{

}

CUITool::~CUITool()
{
	for (UI_PRESET_INFO* pInfo : m_listUIPreset)
		Safe_Delete(pInfo);
	m_listUIPreset.clear();
}

void CUITool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_RadioPreset[0]);
	DDX_Control(pDX, IDC_RADIO2, m_RadioPreset[1]);
	DDX_Control(pDX, IDC_RADIO4, m_RadioPreset[2]);
	DDX_Control(pDX, IDC_LIST3, m_ListBoxPreset);
	DDX_Control(pDX, IDC_PICTURE, m_PicPresetPreview);
	DDX_Text(pDX, IDC_EDIT4, m_XPosEdit);
	DDX_Text(pDX, IDC_EDIT7, m_YPosEdit);
}

void CUITool::RenderPicCtrl()
{
	CGraphic_Device::Get_Instance()->Render_Begin();

	UpdateData(TRUE);
	int iIndex = m_ListBoxPreset.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	auto& iter_find = m_listUIPreset.begin();
	for (int i = 0; i < iIndex; ++i)
		++iter_find;
	UI_PRESET_INFO* pPreset = *iter_find;

	for (int i = 0; i < 4; ++i)
	{
		if (pPreset->layer[i].texObjKey == _T(""))
			break;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(pPreset->layer[i].texObjKey.GetString());
		if (nullptr == pTexInfo)
			break;

		D3DXMATRIX matSacle, matRot, matTrans, matWorld, matParentScale, matParentTrans;
		D3DXMatrixScaling(&matSacle, pPreset->layer[i].xScale, pPreset->layer[i].yScale, 0.f);
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(pPreset->layer[i].angle));
		D3DXMatrixTranslation(&matTrans, pPreset->layer[i].xTrans, pPreset->layer[i].yTrans, 0.f);
		D3DXMatrixScaling(&matParentScale, 6.5f, 5.f, 0.f);	// ㅆ하드코딩
		D3DXMatrixTranslation(&matParentTrans, float(WINCX >> 1),float(WINCY >> 1), 0.f);
		matWorld = matSacle * matRot * matTrans * matParentScale * matParentTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		RECT rc = { pPreset->layer[i].left, pPreset->layer[i].top, pPreset->layer[i].right, pPreset->layer[i].bottom };
		float fCenterX = (float)(rc.right - rc.left) * 0.5f;
		float fCenterY = (float)(rc.bottom - rc.top) * 0.5f;
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	CGraphic_Device::Get_Instance()->Render_End(m_PicPresetPreview.GetSafeHwnd());
}


BEGIN_MESSAGE_MAP(CUITool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUITool::OnBnClickedCreatePreset)
	ON_LBN_SELCHANGE(IDC_LIST3, &CUITool::OnLbnSelchangePresets)
	ON_BN_CLICKED(IDC_BUTTON8, &CUITool::OnBnClickedInsert)
END_MESSAGE_MAP()


// CUITool 메시지 처리기


void CUITool::OnBnClickedCreatePreset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_RadioPreset[0].GetCheck() == BST_CHECKED)
	{
		if (m_UIPresetForm.GetSafeHwnd() == nullptr)
			m_UIPresetForm.Create(IDD_CUIPresetForm);

		m_UIPresetForm.ShowWindow(SW_SHOW);
	}
	else if (m_RadioPreset[1].GetCheck() == BST_CHECKED)
	{
		// + font preset form
	}
	else if (m_RadioPreset[2].GetCheck() == BST_CHECKED)
	{
		// + gauge preset form
	}
}

BOOL CUITool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_RadioPreset[0].SetCheck(TRUE);

	// 이걸 UIPresetForm에서 저장...
	UI_PRESET_INFO* pInfo = new UI_PRESET_INFO;
	pInfo->layer[0].texObjKey = _T("UI_BLACK");
	pInfo->layer[0].left = 0;
	pInfo->layer[0].top = 0;
	pInfo->layer[0].right = 128;
	pInfo->layer[0].bottom = 128;
	pInfo->layer[0].xScale = 1.2f;
	pInfo->layer[0].yScale = 0.3f;
	pInfo->layer[0].angle = -13.f;
	pInfo->layer[0].xTrans = 0.f;
	pInfo->layer[0].yTrans = 0.f;

	pInfo->layer[1].texObjKey = _T("UI_BATTLE");
	pInfo->layer[1].left = 0;
	pInfo->layer[1].top = 1030;
	pInfo->layer[1].right = 54;
	pInfo->layer[1].bottom = 1080;
	pInfo->layer[1].xScale = 0.6f;
	pInfo->layer[1].yScale = 0.6f;
	pInfo->layer[1].angle = -12.f;
	pInfo->layer[1].xTrans = -57.f;
	pInfo->layer[1].yTrans = 15.f;

	pInfo->layer[2].texObjKey = _T("UI_BATTLE");
	pInfo->layer[2].left = 1040;
	pInfo->layer[2].top = 1030;
	pInfo->layer[2].right = 1210;
	pInfo->layer[2].bottom = 1085;
	pInfo->layer[2].xScale = 0.7f;
	pInfo->layer[2].yScale = 0.7f;
	pInfo->layer[2].angle = -12.f;
	pInfo->layer[2].xTrans = 12.f;
	pInfo->layer[2].yTrans = -3.f;

	pInfo->presetName = _T("SWORD");
	
	m_listUIPreset.push_back(pInfo);
	m_ListBoxPreset.AddString(pInfo->presetName);

	//
	pInfo = new UI_PRESET_INFO;
	pInfo->layer[0].texObjKey = _T("UI_BATTLE");
	pInfo->layer[0].left = 55;
	pInfo->layer[0].top = 506;
	pInfo->layer[0].right = 575;
	pInfo->layer[0].bottom = 635;
	pInfo->layer[0].xScale = 0.3f;
	pInfo->layer[0].yScale = 0.3f;
	pInfo->layer[0].angle = 10.f;
	pInfo->layer[0].xTrans = 0.f;
	pInfo->layer[0].yTrans = 0.f;

	pInfo->presetName = _T("Critical");

	m_listUIPreset.push_back(pInfo);
	m_ListBoxPreset.AddString(pInfo->presetName);
	//

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUITool::OnLbnSelchangePresets()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RenderPicCtrl();
}


void CUITool::OnBnClickedInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_ListBoxPreset.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	auto& iter_find = m_listUIPreset.begin();
	for (int i = 0; i < iIndex; ++i)
		++iter_find;
	UI_PRESET_INFO* pPreset = *iter_find;
	
	pPreset->vParentCenterPos = _vec3(m_XPosEdit, m_YPosEdit, 0.f);

}
