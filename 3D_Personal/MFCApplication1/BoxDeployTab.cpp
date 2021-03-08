// BoxDeployTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BoxDeployTab.h"
#include "afxdialogex.h"
#include "ColBox.h"


// CBoxDeployTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBoxDeployTab, CDialog)

CBoxDeployTab::CBoxDeployTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOXDEPLOYTAB, pParent)
	, m_sSelectNaviName(_T(""))
	, m_sTriBoxNavID(_T(""))
	, m_pBox(nullptr)
	, m_sSelectNavID(_T(""))
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

	DDX_Control(pDX, IDC_RADIO9, m_rbPeekBoxType[eBoxType::Collision]);
	DDX_Control(pDX, IDC_RADIO10, m_rbPeekBoxType[eBoxType::Trigger]);

	DDX_Text(pDX, IDC_EDIT19, m_sTriBoxNavID);
	DDX_Text(pDX, IDC_EDIT8, m_sSelectNavID);
	DDX_Control(pDX, IDC_CHECK2, m_cbPeekAble);
}




BEGIN_MESSAGE_MAP(CBoxDeployTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON9, &CBoxDeployTab::OnBnClickedButtonNaviLoad)
	ON_BN_CLICKED(IDC_BUTTON13, &CBoxDeployTab::OnBnClickedButtonNaviDelete)
	ON_BN_CLICKED(IDC_RADIO1, &CBoxDeployTab::OnBnClicked_EnableCreateBox)
	ON_BN_CLICKED(IDC_RADIO2, &CBoxDeployTab::OnBnClicked_EnablePeekingBox)
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
	ON_BN_CLICKED(IDC_RADIO9, &CBoxDeployTab::OnBnClickedPeekTypeCol)
	ON_BN_CLICKED(IDC_RADIO10, &CBoxDeployTab::OnBnClickedPeekTypeTri)
	ON_BN_CLICKED(IDC_BUTTON4, &CBoxDeployTab::OnBnClickedTriBoxIDApply)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CBoxDeployTab::OnTvnSelchangedNavTree)
	ON_BN_CLICKED(IDC_BUTTON21, &CBoxDeployTab::OnBnClicked_DeleteTriBox)
END_MESSAGE_MAP()


// CBoxDeployTab 메시지 처리기입니다.

void CBoxDeployTab::SetUp_Tree(const CString & NavName)
{
	HTREEITEM root;
	root = m_NavTreeCtrl.GetRootItem();
	m_NavTreeCtrl.InsertItem(NavName, 0, 0, TVI_ROOT, TVI_LAST);
	cout << m_NavTreeCtrl.GetCount() << endl;

	UpdateData(FALSE);
}

void CBoxDeployTab::Peeking(const CPoint & point)
{
	if (m_cbPeekAble.GetCheck() == false)
		return;

	if (m_rbClickOption[eClickOption::Create].GetCheck())
	{
		Peeking_Create(_vec2((float)point.x, (float)point.y));
	}
	else
	{
		Peeking_Box(_vec2((float)point.x, (float)point.y));
	}
}

void CBoxDeployTab::Peeking_Create(const _vec2 & vPt)
{
	NULL_CHECK(m_pNavMesh)

	_int temp;
	_vec3 vPeekingPos;
	if (m_pNavMesh->Cell_Peeking(vPt, temp, vPeekingPos))
	{
		CString str;
		
		CColBox* pBox = CColBox::Create(CManagement::Get_Instance()->Get_Device());
		if (m_rbCreateOption[eBoxType::Collision].GetCheck())
		{
			pBox->Set_Type(eBoxType::Collision);
			CManagement::Get_Instance()->Add_InstantGameObject(pBox, L"Layer_ColBox");
			m_pColBoxList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_ColBox");
			Add_ColBox();
		}
		else
		{
			pBox->Set_Type(eBoxType::Trigger);
			CManagement::Get_Instance()->Add_InstantGameObject(pBox, L"Layer_TriBox");
			m_pTriBoxList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_TriBox");
			Add_TriBox();
		}

		pBox->m_pTrans->Set_Position(vPeekingPos);

		if (m_pBox != nullptr)
		{
			m_pBox->Set_Select(false);
		}
		m_pBox = pBox;
		m_pBox->Set_Select(true);
	}
}

//Peeking box 
void CBoxDeployTab::Peeking_Box(const _vec2 & vPt)
{
	if (m_rbClickOption[eClickOption::Peeking].GetCheck() == false )
		return;

	//박스리스트를 받고 피킹메서드 콜  성공시 인덱스와 포인터 out
	auto& SearchPeekingBox = [&](list<CGameObject*>* pList, _int& iBoxIdx,const CColBox* pBox) {
		iBoxIdx = 0;
		for (auto& pBox : *pList)
		{
			if (static_cast<CColBox*>(pBox)->m_pCollsion->RayPeeking(vPt))
			{
				pBox = (CColBox*)pBox;
				return true;
			}
			++iBoxIdx;
		}
		return false;
	};

	//초기화 
	_int iPeekingIdx = NOT_FOUND;
	m_pBox = nullptr; 
	m_sTriBoxNavID = L"";
	//피킹 옵션에 따라 피킹리스트 분기
	if (m_rbPeekBoxType[eBoxType::Collision].GetCheck())
	{
		NULL_CHECK(m_pColBoxList);
		if (SearchPeekingBox(m_pColBoxList, iPeekingIdx,m_pBox))
		{
			m_lbCollsionList.SetCurSel(iPeekingIdx);
		}
	}
	else if(m_rbPeekBoxType[eBoxType::Trigger].GetCheck())
	{
		NULL_CHECK(m_pTriBoxList);
		if (SearchPeekingBox(m_pTriBoxList, iPeekingIdx,m_pBox))
		{
			m_lbTriggerList.SetCurSel(iPeekingIdx);
			m_sTriBoxNavID.Format(L"%d", static_cast<CColBox*>(m_pBox)->m_iNavID);
		}
	}

	UpdateData(FALSE);
}

void CBoxDeployTab::Update_TransInfo()
{
	if (m_pBox->m_eType)
	{
		m_sTriBoxNavID.Format(L"%d", m_pBox->m_eType);
	}

	m_sPos[eFloat3::X].Format(L"%d", m_pBox->m_pTrans->Get_Position().x);
	m_sPos[eFloat3::Y].Format(L"%d", m_pBox->m_pTrans->Get_Position().y);
	m_sPos[eFloat3::Z].Format(L"%d", m_pBox->m_pTrans->Get_Position().z);

	m_sSacle[eFloat3::X].Format(L"%d", m_pBox->m_pTrans->Get_Sacle().x);
	m_sSacle[eFloat3::Y].Format(L"%d", m_pBox->m_pTrans->Get_Sacle().y);
	m_sSacle[eFloat3::Z].Format(L"%d", m_pBox->m_pTrans->Get_Sacle().z);

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

		CNaviObj* pMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device());
		CNaviMesh* pNaviMeshCom = CNaviMesh::Load(CManagement::Get_Instance()->Get_Device(), Dlg.GetPathName(),true);
		pMesh->Set_Navi(pNaviMeshCom);

		CManagement::Get_Instance()->Add_InstantGameObject(pMesh, L"Layer_NaviMesh");
		m_pNavMeshList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");

		SetUp_Tree(Dlg.GetFileTitle());
	}
}


void CBoxDeployTab::OnBnClickedButtonNaviDelete()
{
	if (m_pNavMeshList == nullptr || m_iNavMeshIdx == NOT_FOUND)
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

void CBoxDeployTab::OnBnClicked_EnableCreateBox()
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


void CBoxDeployTab::OnBnClicked_EnablePeekingBox()
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


//콜리전 리스트 클리어 
void CBoxDeployTab::OnBnClickedClearColBox()
{
	m_lbCollsionList.ResetContent();
	for (auto& pBox : *m_pColBoxList)
	{
		pBox->Set_Delete();
	}
}

// 콜리전 박스 세이브
void CBoxDeployTab::OnBnClickedSaveColBox()
{
	NULL_CHECK(m_pColBoxList);

	//  [2/19/2021 Administrator]
	/************************************************************************/
	/*콜박스의 트렌스 폼만 저장 스케일 위치 
	1.scals 2. position
	트리거 박스랑 따로 저장하는 하는 이유는 세이브 파일 수정작업 시 분할 저장으로 수정규모 최소화 */
	/************************************************************************/
	
	CFileDialog Dlg(FALSE,
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

		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
			return;
		
		DWORD dwByte;
		for (auto& pBox : *m_pColBoxList)
		{
			CTransform* pTrans =  (CTransform*)pBox->Get_Component(eComponentID::Transform);
			WriteFile(hFile, &pTrans->Get_Sacle(), sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &pTrans->Get_Position(), sizeof(_vec3), &dwByte, nullptr);
		}
		CloseHandle(hFile);
	}
}


void CBoxDeployTab::OnBnClickedLoadColBox()
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

		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
			return;


		DWORD dwbyte;
		_vec3 vScale ,vPos;
		while(true)
		{
			ReadFile(hFile, &vScale, sizeof(_vec3), &dwbyte, nullptr); // Read Scals
			if(dwbyte == 0 )
				break;
			ReadFile(hFile, &vPos, sizeof(_vec3), &dwbyte, nullptr); // Read Position

			CColBox* pBox = (CColBox*)CManagement::Get_Instance()->Add_InstantGameObject(L"Col_Box", L"Layer_ColBox");
			pBox->Set_Scale(vScale);
			pBox->Set_Pos(vPos);
		}
		CloseHandle(hFile);

	
		m_pColBoxList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_ColBox");

		//Load 후 리스트 박스 초기화 
		m_lbCollsionList.ResetContent();
		_tchar szBuffer[32] = L"";
		for (size_t i = 0; i < m_pColBoxList->size(); ++i)
		{
			wsprintf(szBuffer, L"ColBox[%d]", i);
			m_lbCollsionList.AddString(szBuffer);
		}
	}
}


void CBoxDeployTab::OnBnClickedClearTri()
{
	NULL_CHECK(m_pTriBoxList);

	m_lbTriggerList.ResetContent();
	for (auto& pBox : *m_pTriBoxList)
	{
		pBox->Set_Delete();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBoxDeployTab::OnBnClickedSaveTriBox()
{
	NULL_CHECK(m_pTriBoxList);

	// NavID 체크 
	_uint iBoxIdx = 0;
	for (auto& pBox : *m_pColBoxList)
	{
		if (((CColBox*)pBox)->m_iNavID == NOT_FOUND)
		{
			_tchar szBuffer[64] = L"";
			wsprintf(szBuffer, L"TriBox[%d] of m_iNavID Null", iBoxIdx);
			MSG_BOX(szBuffer);
			return;
		}
	}
	//  [2/19/2021 Administrator]
	/************************************************************************/
	/* 트리박스 저장 
	1.scals 2. position 3.NavID
	데이터  수정작업 시 분할 저장으로 수정규모 최소화 */
	/************************************************************************/

	CFileDialog Dlg(FALSE,
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

		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
			return;

		DWORD dwByte;
		for (auto& pBox : *m_pColBoxList)
		{
			CTransform* pTrans = (CTransform*)pBox->Get_Component(eComponentID::Transform);
			WriteFile(hFile, &pTrans->Get_Sacle(), sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &pTrans->Get_Position(), sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &((CColBox*)pBox)->m_iNavID, sizeof(_int), &dwByte, nullptr);

		}
		CloseHandle(hFile);



	}
}


void CBoxDeployTab::OnBnClickedLoadTriBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		DWORD dwbyte;
		//load로 obj 만든건 load 값 검사해서 다른 로직으로 
		_vec3 vScale, vPos;
		_int  iNavId = NOT_FOUND;
		while (true)
		{
			ReadFile(hFile, &vScale, sizeof(_vec3), &dwbyte, nullptr); // Read Scals
			if (dwbyte == 0)
				break;
			ReadFile(hFile, &vPos, sizeof(_vec3), &dwbyte, nullptr); // Read Position
			ReadFile(hFile, &iNavId, sizeof(_int), &dwbyte, nullptr); // Read NavID

			CColBox* pBox = (CColBox*)CManagement::Get_Instance()->Add_InstantGameObject(L"Tri_Box", L"Layer_TriggerBox");
			pBox->Set_Scale(vScale);
			pBox->Set_Pos(vPos);
			((CColBox*)pBox)->m_iNavID = iNavId;
		}
		CloseHandle(hFile);

		//리스트박스 초기화
		m_lbTriggerList.ResetContent();
		m_pTriBoxList = CManagement::Get_Instance()->Get_GameObjetList(L"Laeyr_TriggerBox");
		_tchar szBuffer[32] = L"";

		for (size_t i = 0; i < m_pTriBoxList->size(); ++i)
		{
			wsprintf(szBuffer, L"TriBox[%d]", i);
			m_lbTriggerList.AddString(szBuffer);
		}
	}

}


void CBoxDeployTab::OnDeltaposSpinSacleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vScale = m_pBox->m_pTrans->Get_Sacle();
	vScale.x += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Scale(vScale);

	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vScale = m_pBox->m_pTrans->Get_Sacle();
	vScale.y += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Scale(vScale);

	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vScale = m_pBox->m_pTrans->Get_Sacle();
	vScale.z += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Scale(vScale);

	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vPos = m_pBox->m_pTrans->Get_Position();
	vPos.x += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Pos(vPos);

	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vPos = m_pBox->m_pTrans->Get_Position();
	vPos.y += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Pos(vPos);

	*pResult = 0;
}


void CBoxDeployTab::OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	NULL_CHECK(m_pBox);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	_vec3 vPos = m_pBox->m_pTrans->Get_Position();
	vPos.z += -(pNMUpDown->iDelta) / 10.f;
	m_pBox->Set_Pos(vPos);

	*pResult = 0;
}

//tri a
void CBoxDeployTab::OnBnClickedPeekTypeCol()
{
	GetDlgItem(IDC_EDIT19)->EnableWindow(FALSE);
	m_sTriBoxNavID = L"";
	UpdateData(FALSE);
}


void CBoxDeployTab::OnBnClickedPeekTypeTri()
{
	GetDlgItem(IDC_EDIT19)->EnableWindow(TRUE);
	m_sTriBoxNavID = L"";
	UpdateData(FALSE);
}


void CBoxDeployTab::OnBnClickedTriBoxIDApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK(m_pBox);
	UpdateData(TRUE);
	static_cast<CColBox*>(m_pBox)->m_iNavID = _ttoi(m_sTriBoxNavID);
}


void CBoxDeployTab::OnTvnSelchangedNavTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK(m_pNavMeshList);

	int iIndex = 0;
	HTREEITEM hItem = m_NavTreeCtrl.GetSelectedItem();
	HTREEITEM hLoop;
	//root 클릭 예외처리


	m_iNavMeshIdx = 0;
	hLoop = m_NavTreeCtrl.GetRootItem();

	while (hLoop != nullptr)
	{
		if (hLoop == hItem)
		{
			m_pNavMesh = Find_NavMeshFromLayer();
			//m_sSelectNavID m_sTriBoxNavID 아이디 추가해야함 
			m_sSelectNaviName = m_NavTreeCtrl.GetItemText(hItem);
			m_sSelectNavID.Format(L"%d", m_pNavMesh->m_pNaviCom->Get_NaviID());
			UpdateData(FALSE);
			return;
		}
		hLoop = m_NavTreeCtrl.GetNextItem(hLoop, TVGN_NEXT);
		++m_iNavMeshIdx;
	}
	m_iNavMeshIdx = NOT_FOUND;
	*pResult = 0;
}


void CBoxDeployTab::Add_TriBox()
{
	_int iIdx = m_lbTriggerList.GetCount();
	if (iIdx == LB_ERR)
		return;

	CString str;

	str.Format(L"TriBox[%d]", iIdx);
	m_lbTriggerList.AddString(str);
}

void CBoxDeployTab::Add_ColBox()
{
	_int iIdx = m_lbCollsionList.GetCount();
	if (iIdx == LB_ERR)
		return;

	CString str;
	str.Format(L"ColBox[%d]", iIdx);
	m_lbCollsionList.AddString(str);
}

CNaviObj * CBoxDeployTab::Find_NavMeshFromLayer()
{
	NULL_CHECK_RETURN(m_pNavMeshList, nullptr);

	auto& iter = m_pNavMeshList->begin();
	for (int i = 0; iter != m_pNavMeshList->end(); ++i, ++iter)
	{
		if (i == m_iNavMeshIdx)
			return (CNaviObj*)(*iter);
	}

	return nullptr;
}



void CBoxDeployTab::OnBnClicked_DeleteTriBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




BOOL CBoxDeployTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
