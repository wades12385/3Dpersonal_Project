
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MFCTool.h"

#include "MainFrm.h"

#include "MFCToolView.h"
#include "MyFormView.h"


#ifdef _DEBUG 
#define new DEBUG_NEW
#endif
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// View를 MainFrame이 생성될때 바로 깔아버리는게 아니라 스플릿 윈도우를 깔고 그 안에 view를 깔것. 

	m_tMainSplitter.CreateStatic(this, 1, 2); 

	m_tMainSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyFormView), CSize(500, 300), pContext);
	m_tMainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMFCToolView), CSize(800, 110), pContext);
	m_tMainSplitter.SetColumnInfo(0, 500, 10);

	//g_hWnd = ((CMFCToolView*)m_tMainSplitter.GetPane(0, 1))->m_hWnd;
	return CFrameWnd::OnCreateClient(lpcs, pContext);
	//return TRUE;
}
