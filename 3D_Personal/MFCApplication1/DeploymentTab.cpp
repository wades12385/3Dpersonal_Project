// ObjectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DeploymentTab.h"
#include "afxdialogex.h"


// CObjectTab ��ȭ �����Դϴ�.

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


// CObjectTab �޽��� ó�����Դϴ�.
