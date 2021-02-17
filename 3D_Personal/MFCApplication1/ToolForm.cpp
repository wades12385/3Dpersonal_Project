// ToolForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ToolForm.h"
#include "NaviModifyScene.h"


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


// CToolForm �����Դϴ�.

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


// CToolForm �޽��� ó�����Դϴ�.


void CToolForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CRect rcFormWnd;
	CRect rcTabClien;

	int TabCY = 20;	//tab Size y 

	m_TabCtrl.InsertItem(0, L"NaviMeshModify");
	m_TabCtrl.InsertItem(1, L"Depolyment");
	m_TabCtrl.InsertItem(2, L"CollisionBox");


	SetScrollSizes(MM_TEXT, CSize(0, 0));

	GetClientRect(&rcFormWnd);
	GetWindowRect(&rcFormWnd);
	::SetRect(&rcFormWnd, 0, 0, rcFormWnd.right - rcFormWnd.left, rcFormWnd.bottom - rcFormWnd.top); // Ŭ����ǥ ��ȯ 


	m_TabCtrl.GetClientRect(&rcTabClien);
	m_TabCtrl.SetWindowPos(nullptr, 0, 0, 450, WINCY, SWP_NOZORDER);

	m_NaviModifyTab.Create(IDD_NAVIMODIFYTAB, &m_TabCtrl);
	m_NaviModifyTab.MoveWindow(0, TabCY, 450, WINCY);
	m_NaviModifyTab.ShowWindow(SW_SHOW);

	m_DeploymentTab.Create(IDD_OBJECTTAB, &m_TabCtrl);
	m_DeploymentTab.MoveWindow(0, TabCY, 450, WINCY);
	m_DeploymentTab.ShowWindow(SW_HIDE);


	m_CollisionTab.Create(IDD_OBJECTTAB, &m_TabCtrl);
	m_CollisionTab.MoveWindow(0, TabCY, 450, WINCY);
	m_CollisionTab.ShowWindow(SW_HIDE);
	

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CToolForm::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iSel = m_TabCtrl.GetCurSel();
	switch (iSel)
	{
	case 0:
		m_NaviModifyTab.ShowWindow(SW_SHOW);
		m_DeploymentTab.ShowWindow(SW_HIDE);
		m_CollisionTab.ShowWindow(SW_HIDE);

		CManagement::Get_Instance()->SetUpCurrentScene(eToolScene::NaviModify,
			CNaviModifyScene::Create(CManagement::Get_Instance()->Get_Device()));

		break;
	case 1:
		m_NaviModifyTab.ShowWindow(SW_HIDE);
		m_DeploymentTab.ShowWindow(SW_SHOW);
		m_CollisionTab.ShowWindow(SW_HIDE);

		break;
	case 2:
		m_NaviModifyTab.ShowWindow(SW_HIDE);
		m_DeploymentTab.ShowWindow(SW_HIDE);
		m_CollisionTab.ShowWindow(SW_SHOW);
			CManagement::Get_Instance()->SetUpCurrentScene(eToolScene::NaviModify,
			CNaviModifyScene::Create(CManagement::Get_Instance()->Get_Device()));

		break;
	}

	// �� ��ȯ�� �ϴµ� ���� ���� ���̾ �� ������ �ؾ��ϳ�
	*pResult = 0;
}
