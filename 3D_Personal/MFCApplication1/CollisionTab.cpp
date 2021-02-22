// CollisionTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CollisionTab.h"
#include "afxdialogex.h"


// CCollisionTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCollisionTab, CDialog)

CCollisionTab::CCollisionTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_COLLISIONTAB, pParent)
{

}

CCollisionTab::~CCollisionTab()
{
}

void CCollisionTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCollisionTab, CDialog)
END_MESSAGE_MAP()


// CCollisionTab 메시지 처리기입니다.
