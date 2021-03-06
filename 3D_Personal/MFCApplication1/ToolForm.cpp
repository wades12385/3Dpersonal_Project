// ToolForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ToolForm.h"
#include "NaviModifyScene.h"
#include "BoxDeployScene.h"
#include "StaticDeployScene.h"
// CToolForm

IMPLEMENT_DYNCREATE(CToolForm, CFormView)

CToolForm::CToolForm()
	: CFormView(IDD_TOOLFORM)
{

}

CToolForm::~CToolForm()
{
}

void CToolForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CToolForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CToolForm::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CToolForm 진단입니다.

#ifdef _DEBUG
void CToolForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolForm 메시지 처리기입니다.


void CToolForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rcFormWnd;
	CRect rcTabClien;

	int TabCY = 20;	//tab Size y 
	m_TabCtrl.InsertItem(0, L"NaviMeshModify");
	m_TabCtrl.InsertItem(1, L"Depolyment");
	m_TabCtrl.InsertItem(2, L"BoxDeploy");

	

	SetScrollSizes(MM_TEXT, CSize(0, 0));

	GetClientRect(&rcFormWnd);
	GetWindowRect(&rcFormWnd);
	::SetRect(&rcFormWnd, 0, 0, rcFormWnd.right - rcFormWnd.left, rcFormWnd.bottom - rcFormWnd.top); // 클라좌표 변환 

	m_TabCtrl.GetClientRect(&rcTabClien);
	m_TabCtrl.SetWindowPos(nullptr, 0, 0, 450, WINCY, SWP_NOZORDER);

	m_NaviModifyTab.Create(IDD_NAVIMODIFYTAB, &m_TabCtrl);
	m_NaviModifyTab.MoveWindow(0, TabCY, 450, WINCY);
	m_NaviModifyTab.ShowWindow(SW_SHOW);

	m_StaticDeployTab.Create(IDD_OBJECTTAB, &m_TabCtrl);
	m_StaticDeployTab.MoveWindow(0, TabCY, 450, WINCY);
	m_StaticDeployTab.ShowWindow(SW_HIDE);

	m_BoxDeployTab.Create(IDD_BOXDEPLOYTAB, &m_TabCtrl);
	m_BoxDeployTab.MoveWindow(0, TabCY, 450, WINCY);
	m_BoxDeployTab.ShowWindow(SW_HIDE);
}

void CToolForm::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iSel = m_TabCtrl.GetCurSel();
	_uint iPreIdx = CManagement::Get_Instance()->Get_SceneID();
	CManagement::Get_Instance()->ClearForScene(iPreIdx);
	switch (iSel)
	{
	case 0:
		m_NaviModifyTab.ShowWindow(SW_SHOW);
		m_StaticDeployTab.ShowWindow(SW_HIDE);
		m_BoxDeployTab.ShowWindow(SW_HIDE);
		CManagement::Get_Instance()->SetUp_ChangeScene(eToolScene::NaviModify,
			CNaviModifyScene::Create(CManagement::Get_Instance()->Get_Device()));
		break;
	case 1:
		m_NaviModifyTab.ShowWindow(SW_HIDE);
		m_StaticDeployTab.ShowWindow(SW_SHOW);
		m_BoxDeployTab.ShowWindow(SW_HIDE);
		CManagement::Get_Instance()->SetUp_ChangeScene(eToolScene::StaticObject,
			CStaticDeployScene::Create(CManagement::Get_Instance()->Get_Device()));
		m_StaticDeployTab.SetUp_Tool();
		break;
	case 2:
		m_NaviModifyTab.ShowWindow(SW_HIDE);
		m_StaticDeployTab.ShowWindow(SW_HIDE);
		m_BoxDeployTab.ShowWindow(SW_SHOW);
			CManagement::Get_Instance()->SetUp_ChangeScene(eToolScene::BoxDeploy,
			CBoxDeployScene::Create(CManagement::Get_Instance()->Get_Device()));
		break;
	}
	// 씬 전환은 하는데 기존 씬의 레이어를 다 릴리즈 해야하나
	*pResult = 0;
}
