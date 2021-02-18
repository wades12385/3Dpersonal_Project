// BoxDeployTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BoxDeployTab.h"
#include "afxdialogex.h"


// CBoxDeployTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBoxDeployTab, CDialog)

CBoxDeployTab::CBoxDeployTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOXDEPLOYTAB, pParent)
	, m_sSelectNaviName(_T(""))
	, m_cbSelected_Navi(FALSE)

{

}

CBoxDeployTab::~CBoxDeployTab()
{
}

void CBoxDeployTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_NavTreeCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_sSelectNaviName);
	DDX_Check(pDX, IDC_CHECK1, m_cbSelected_Navi);
	DDX_Control(pDX, IDC_RADIO1, m_rbClickOption[eClickOption::Create]);
	DDX_Control(pDX, IDC_RADIO2, m_rbClickOption[eClickOption::Peeking]);
	DDX_Control(pDX, IDC_RADIO3, m_rbCreateOption[eBoxType::Collision]);
	DDX_Control(pDX, IDC_RADIO4, m_rbCreateOption[eBoxType::Trigger]);
	DDX_Text(pDX, IDC_EDIT3, m_sSacle[eFloat3::X]);
	DDX_Text(pDX, IDC_EDIT10, m_sSacle[eFloat3::Y]);
	DDX_Text(pDX, IDC_EDIT11, m_sSacle[eFloat3::Z]);
	DDX_Text(pDX, IDC_EDIT20, m_sPos[eFloat3::X]);
	DDX_Text(pDX, IDC_EDIT21, m_sPos[eFloat3::Y]);
	DDX_Text(pDX, IDC_EDIT22, m_sPos[eFloat3::Z]);

	DDX_Control(pDX, IDC_LIST1, m_lbCollsionList);
	DDX_Control(pDX, IDC_LIST2, m_lbTriggerList);
}




BEGIN_MESSAGE_MAP(CBoxDeployTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON9, &CBoxDeployTab::OnBnClickedButtonNaviLoad)
	ON_BN_CLICKED(IDC_BUTTON13, &CBoxDeployTab::OnBnClickedButtonNaviDelete)
	ON_BN_CLICKED(IDC_RADIO1, &CBoxDeployTab::OnBnClickedCreateBox)
	ON_BN_CLICKED(IDC_RADIO2, &CBoxDeployTab::OnBnClickedPeekingBox)
	ON_BN_CLICKED(IDC_BUTTON3, &CBoxDeployTab::OnBnClickedClearColBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CBoxDeployTab::OnBnClickedSaveColBox)
	ON_BN_CLICKED(IDC_BUTTON2, &CBoxDeployTab::OnBnClickedLoadColBox)
	ON_BN_CLICKED(IDC_BUTTON10, &CBoxDeployTab::OnBnClickedClearTri)
	ON_BN_CLICKED(IDC_BUTTON11, &CBoxDeployTab::OnBnClickedSaveTriBox)
	ON_BN_CLICKED(IDC_BUTTON12, &CBoxDeployTab::OnBnClickedLoadTriBox)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CBoxDeployTab::OnDeltaposSpinSacleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &CBoxDeployTab::OnDeltaposSpinScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, &CBoxDeployTab::OnDeltaposSpinScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CBoxDeployTab::OnDeltaposSpinPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN13, &CBoxDeployTab::OnDeltaposSpinPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, &CBoxDeployTab::OnDeltaposSpinPosZ)
END_MESSAGE_MAP()


// CBoxDeployTab 메시지 처리기입니다.

void CBoxDeployTab::SetUp_Tree(const CString & NavName)
{
	if (m_pNavMesh == nullptr)
		return;
	CString NaviMeshRoot, ObjEntry;


	HTREEITEM root, NaviMesh, Vtx;
	root = m_NavTreeCtrl.GetRootItem();
	NaviMesh = m_NavTreeCtrl.InsertItem(NavName, 0, 0, root, TVI_LAST);
	UpdateData(FALSE);
}



void CBoxDeployTab::OnBnClickedButtonNaviLoad()
{
	
	CFileDialog Dlg(TRUE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) |*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		CString strFileName = Dlg.GetFileName();

		//추가하고  
		CManagement::Get_Instance()->Load_NavMesh(strFileName, strFilePath);

		//load로 obj 만든건 load 값 검사해서 다른 로직으로 
		m_pNavMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device(), strFileName);

		CManagement::Get_Instance()->Add_InstantGameObject(m_pNavMesh, L"Layer_NaviMesh");
		m_pNavObjList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");
		CManagement::Get_Instance()->Get_GameObjet(L"Layer_NaviMesh");

		SetUp_Tree(Dlg.GetFileTitle());
	}
}


void CBoxDeployTab::OnBnClickedButtonNaviDelete()
{
	if (m_pNavObjList == nullptr || m_iNavMeshIdx == NOT_FOUND)
		return;

	// changed Tree에서 셋업한 pNavMesh 
	m_pNavMesh->Set_Delete();

	// Tree Delete
	HTREEITEM hLoop = m_NavTreeCtrl.GetRootItem(); // loot
	hLoop = m_NavTreeCtrl.GetChildItem(hLoop);
	_uint iIdx = 0;
	// Tree Clear
	while (hLoop != nullptr)
	{
		if (iIdx == m_iNavMeshIdx)
		{
			m_NavTreeCtrl.DeleteItem(hLoop);
			m_iNavMeshIdx = NOT_FOUND;
			break;
		}
		hLoop = m_NavTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
		++iIdx;
	}

}

//
//DDX_Control(pDX, IDC_RADIO1, m_rbClickOption[eClickOption::Create]);
//DDX_Control(pDX, IDC_RADIO2, m_rbClickOption[eClickOption::Peeking]);
//DDX_Control(pDX, IDC_RADIO3, m_rbCreateOption[eBoxType::Collision]);
//DDX_Control(pDX, IDC_RADIO4, m_rbCreateOption[eBoxType::Trigger]);
//DDX_Text(pDX, IDC_EDIT3, m_sSacle[eFloat3::X]);
//DDX_Text(pDX, IDC_EDIT10, m_sSacle[eFloat3::Y]);
//DDX_Text(pDX, IDC_EDIT11, m_sSacle[eFloat3::Z]);
//DDX_Text(pDX, IDC_EDIT20, m_sPos[eFloat3::X]);
//DDX_Text(pDX, IDC_EDIT21, m_sPos[eFloat3::Y]);
//DDX_Text(pDX, IDC_EDIT22, m_sPos[eFloat3::Z]);

void CBoxDeployTab::OnBnClickedCreateBox()
{
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT20)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT21)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT22)->EnableWindow(FALSE);

	//spin

	GetDlgItem(IDC_SPIN2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN10)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN11)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN13)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN12)->EnableWindow(FALSE);

}


void CBoxDeployTab::OnBnClickedPeekingBox()
{

	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);

	m_rbCreateOption[eBoxType::Collision].SetCheck(FALSE);
	m_rbCreateOption[eBoxType::Trigger].SetCheck(FALSE);


	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT20)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT21)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT22)->EnableWindow(TRUE);

	//spin

	GetDlgItem(IDC_SPIN2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN10)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN11)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN13)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN12)->EnableWindow(TRUE);


}


void CBoxDeployTab::OnBnClickedClearColBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedSaveColBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedLoadColBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedClearTri()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedSaveTriBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedLoadTriBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnDeltaposSpinSacleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
