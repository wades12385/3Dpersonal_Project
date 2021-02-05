// NaviMeshTap.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCTool.h"
#include "NaviMeshTap.h"
#include "afxdialogex.h"


// CNaviMeshTap 대화 상자

IMPLEMENT_DYNAMIC(CNaviMeshTap, CDialog)

CNaviMeshTap::CNaviMeshTap(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NaviMeshTap, pParent)
{

}

CNaviMeshTap::~CNaviMeshTap()
{
}

void CNaviMeshTap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNaviMeshTap, CDialog)
END_MESSAGE_MAP()


// CNaviMeshTap 메시지 처리기
