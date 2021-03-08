
// MFCApplication1View.cpp : CMFCApplicationView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplicationView ����/�Ҹ�

CMFCApplicationView::CMFCApplicationView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}
CMFCApplicationView::~CMFCApplicationView()
{
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationView �׸���

void CMFCApplicationView::OnDraw(CDC* /*pDC*/)
{
	CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CMFCApplicationView �μ�

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCApplicationView ����

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView �޽��� ó����


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
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); // Ŭ����ǥ ��ȯ 
	
	DWORD dwWidth = rcMain.right - rcView.right;
	DWORD dwHeight = rcMain.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + dwWidth, WINCY + dwHeight, SWP_NOZORDER);
	
	pMain->GetClientRect(&rcMain);
	SetWindowPos(nullptr, 458, 0, WINCX , WINCY , SWP_NOZORDER);

	GetClientRect(&rcView);
	GetWindowRect(&rcView2);
	::SetRect(&rcView, 0, 0, rcView.right - rcView.left, rcView.bottom - rcView.top); // Ŭ����ǥ ��ȯ 



	CToolForm* pForm = (CToolForm*)(pMain->m_tSplitter.GetPane(0, 0));
	m_pNaviModiTab = &pForm->m_NaviModifyTab;
	m_pBoxDeployTab = &pForm->m_BoxDeployTab;
	m_pStaticDeployTab = &pForm->m_StaticDeployTab;
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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


