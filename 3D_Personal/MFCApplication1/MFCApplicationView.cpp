
// MFCApplication1View.cpp : CMFCApplicationView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"
#include "DirectApp.h"
#include "MainFrm.h"
#include "NaviModifyTab.h"
#include "ToolForm.h"
#include "StaticDeploymentTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CView)
HWND g_hWnd;
BEGIN_MESSAGE_MAP(CMFCApplicationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplicationView 생성/소멸

CMFCApplicationView::CMFCApplicationView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}
CMFCApplicationView::~CMFCApplicationView()
{
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationView 그리기

void CMFCApplicationView::OnDraw(CDC* /*pDC*/)
{
	CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CMFCApplicationView 인쇄

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplicationView 진단

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView 메시지 처리기


void CMFCApplicationView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDirectApp::Get_Instance()->ReadyEngine(m_hWnd);

	CMainFrame* pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	RECT rcMain = {};
	RECT rcView = {};
	RECT rcView2 = {};

	pMain->GetWindowRect(&rcMain);
	GetClientRect(&rcView);
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); // 클라좌표 변환 
	
	DWORD dwWidth = rcMain.right - rcView.right;
	DWORD dwHeight = rcMain.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + dwWidth, WINCY + dwHeight, SWP_NOZORDER);
	
	pMain->GetClientRect(&rcMain);
	SetWindowPos(nullptr, 458, 0, WINCX , WINCY , SWP_NOZORDER);

	GetClientRect(&rcView);
	GetWindowRect(&rcView2);
	::SetRect(&rcView, 0, 0, rcView.right - rcView.left, rcView.bottom - rcView.top); // 클라좌표 변환 



	CToolForm* pForm = (CToolForm*)(pMain->m_tSplitter.GetPane(0, 0));
	m_pNaviModiTab = &pForm->m_NaviModifyTab;
	m_pBoxDeployTab = &pForm->m_BoxDeployTab;
	m_pStaticDeployTab = &pForm->m_StaticDeployTab;
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{


	int iIdx = NOT_FOUND;
	CMainFrame* pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CToolForm* pForm = (CToolForm*)(pMain->m_tSplitter.GetPane(0, 0));
	iIdx = pForm->m_TabCtrl.GetCurSel();

	switch (iIdx)
	{
	case 0:
		if (m_pNaviModiTab->m_bVtxModing == false)
			return;
		m_pNaviModiTab->Peeking(point);
		break;
	case 1:
		if (m_pStaticDeployTab->m_rbPeektype[eStaticItemPeek::None].GetCheck())
			return;
		m_pStaticDeployTab->Peeking(point);
		break;
	case 2:
		m_pBoxDeployTab->Peeking(point);
	default:
		break;
	}

}


