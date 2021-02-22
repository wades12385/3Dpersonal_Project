// ObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DeploymentTab.h"
#include "afxdialogex.h"


// CObjectTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeploymentTab, CDialog)

CDeploymentTab::CDeploymentTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTAB, pParent)
{
}

CDeploymentTab::~CDeploymentTab()
{
}

void CDeploymentTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeploymentTab, CDialog)
END_MESSAGE_MAP()


// CObjectTab 메시지 처리기입니다.
