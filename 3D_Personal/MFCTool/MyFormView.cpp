// MyFormView.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyFormView.h"
#include "afxdialogex.h"


// CMyFormView 대화 상자

IMPLEMENT_DYNAMIC(CMyFormView, CFormView)

CMyFormView::CMyFormView(CWnd* pParent /*=nullptr*/)
	: CFormView(IDD_MyFormView)
{

}

CMyFormView::~CMyFormView()
{
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyFormView::OnTcnSelchange)
END_MESSAGE_MAP()


// CMyFormView 메시지 처리기


void CMyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rcFormWnd;
	CRect rcTabClien;

	int TabCY = 20;	//tab Size y 

	m_TabCtrl.InsertItem(0, L"NaviMesh");
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	GetWindowRect(&rcFormWnd);
	::SetRect(&rcFormWnd, 0, 0, rcFormWnd.right - rcFormWnd.left, rcFormWnd.bottom - rcFormWnd.top);
	m_TabCtrl.GetClientRect(&rcTabClien);
	m_TabCtrl.SetWindowPos(nullptr, 10, 0, 500, WINCY, SWP_NOZORDER);
	m_TabCtrl.GetClientRect(&rcTabClien);


	m_DiaNaviMesh.Create(IDD_TILEOPTION, &m_TabCtrl);
	m_DiaNaviMesh.MoveWindow(0, TabCY, rcTabClien.Width(), rcTabClien.Height());
	m_DiaNaviMesh.ShowWindow(SW_SHOW);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyFormView::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_TabCtrl.GetCurSel();
	switch (iSel)
	{
	case 0:
		m_DiaNaviMesh.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
