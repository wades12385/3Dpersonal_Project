// NaviModifyTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NaviModifyTab.h"
#include "afxdialogex.h"
#include "StaticMesh.h"
#include "Resource.h"

// CNaviModifyTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNaviModifyTab, CDialog)
USING(Engine)
CNaviModifyTab::CNaviModifyTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NAVIMODIFYTAB, pParent)
	, m_bVtxModing(FALSE)
	, m_pNavMesh(nullptr)
	, m_pListNavMeshObj(nullptr)
	, m_bHideSwitch(false)
	, m_bHide_ComboBox(FALSE)
	, m_cPeekingVtxIdx(_T(""))
	, m_sPosX(_T(""))
	, m_sPosY(_T(""))
	, m_sPosZ(_T(""))
	, m_bNowPeeking(false)
	, m_iPeekVtxIdx(NOT_FOUND)
	, m_iPeekCellIdx(NOT_FOUND)
	, m_iNavMeshIdx(NOT_FOUND)
	, m_cPeekingCellIdx(_T(""))
	, m_sColorR(_T(""))
	, m_sColorG(_T(""))
	, m_sColorB(_T(""))
	, m_sNaviID(_T(""))
	, m_sSelectNavName(_T(""))
	, m_cbHideCell(FALSE)
	, m_cbHideVtx(FALSE)
	, m_cbModifyOption(FALSE)
	
{

}

CNaviModifyTab::~CNaviModifyTab()
{
}

void CNaviModifyTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, m_bVtxModing);
	DDX_Check(pDX, IDC_CHECK1, m_bHide_ComboBox);
	DDX_Text(pDX, IDC_EDIT10, m_cPeekingVtxIdx);
	DDX_Text(pDX, IDC_EDIT1, m_sPosX);
	DDX_Text(pDX, IDC_EDIT2, m_sPosY);
	DDX_Text(pDX, IDC_EDIT3, m_sPosZ);
	DDX_Control(pDX, IDC_SPIN1, m_spPosX);
	DDX_Control(pDX, IDC_SPIN2, m_spPosY);
	DDX_Control(pDX, IDC_SPIN3, m_spPosZ);
	DDX_Control(pDX, IDC_TREE1, m_tcTreeCtrl);
	DDX_Control(pDX, IDC_RADIO1, m_CellTypeBnt[0]);
	DDX_Control(pDX, IDC_RADIO2, m_CellTypeBnt[1]);
	DDX_Control(pDX, IDC_RADIO3, m_CellTypeBnt[2]);
	DDX_Control(pDX, IDC_RADIO4, m_PeekingBnt[0]);
	DDX_Control(pDX, IDC_RADIO5, m_PeekingBnt[1]);
	DDX_Text(pDX, IDC_EDIT11, m_cPeekingCellIdx);
	DDX_Text(pDX, IDC_EDIT12, m_sColorR);
	DDX_Text(pDX, IDC_EDIT13, m_sColorG);
	DDX_Text(pDX, IDC_EDIT14, m_sColorB);
	DDX_Text(pDX, IDC_EDIT15, m_sNaviID);
	DDX_Text(pDX, IDC_EDIT17, m_sSelectNavName);
	DDX_Check(pDX, IDC_CHECK4, m_cbHideCell);
	DDX_Check(pDX, IDC_CHECK3, m_cbHideVtx);
	DDX_Control(pDX, IDC_EDIT16, m_edNextNavID);
	DDX_Control(pDX, IDC_EDIT18, m_edConnectIdx);
	DDX_Check(pDX, IDC_CHECK5, m_cbLineID[eLineID::AB]);
	DDX_Check(pDX, IDC_CHECK6, m_cbLineID[eLineID::BC]);
	DDX_Check(pDX, IDC_CHECK7, m_cbLineID[eLineID::CA]);
	DDX_Check(pDX, IDC_CHECK8, m_cbModifyOption);
	DDX_Control(pDX, IDC_RADIO6, m_LineTypeBnt[0]);
	DDX_Control(pDX, IDC_RADIO7, m_LineTypeBnt[1]);
	DDX_Control(pDX, IDC_RADIO8, m_LineTypeBnt[2]);
}

void CNaviModifyTab::Update_NaviModityTab()
{
	UpdateData(FALSE);
}

void CNaviModifyTab::ShowText_Vtx(int idx)
{
	m_iPeekVtxIdx = idx;
	m_cPeekingVtxIdx.Format(_T("%d"), idx);
	_vec3 vSelectVtx = m_pNavMesh->m_pNaviCom->Get_vCellVtx()[idx];
	Update_VtxPosEdit(vSelectVtx);
	UpdateData(FALSE);
}

void CNaviModifyTab::ShowText_Cell(int idx)
{
	m_iPeekCellIdx = idx;
	m_cPeekingCellIdx.Format(_T("%d"), idx);

	//Line Option enable
	if (m_pNavMesh != nullptr &&
		m_pNavMesh->m_pNaviCom->Get_vCell()[idx]->Get_CellType() != eCellType::Base)
			Enable_LineOption(true);
	else
		Enable_LineOption(false);

	UpdateData(FALSE);
}

void CNaviModifyTab::Update_VtxPosEdit(_vec3 vPos)
{
	m_sPosX.Format(_T("%.2f"), vPos.x);
	m_sPosY.Format(_T("%.2f"), vPos.y);
	m_sPosZ.Format(_T("%.2f"), vPos.z);
	UpdateData(FALSE);
}

_uint CNaviModifyTab::Get_CellType()
{
	UpdateData(TRUE);
	
	for (int i = 0; i < eCellType::End; ++i)
	{
		if (m_CellTypeBnt[i].GetCheck())
			return i;
	}
	return 0;
}

CNaviObj * CNaviModifyTab::Get_ObjFromNavLayer(const _uint & iIdx)
{
	NULL_CHECK_RETURN(m_pListNavMeshObj, nullptr);

	auto& iter = m_pListNavMeshObj->begin();
	for (int i = 0; iter != m_pListNavMeshObj->end(); ++i, ++iter)
	{
		if (i == m_iNavMeshIdx)
			return (CNaviObj*)(*iter);
	}

	return nullptr;
}

void CNaviModifyTab::SetUp_HideOption()
{
	NULL_CHECK_RETURN_MSG(m_pNavMesh, , L"Nullptr Error From SetUp_RenderOption()");

	m_cbHideVtx = m_pNavMesh->m_bHideVtx;
	m_cbHideCell = m_pNavMesh->m_bHideCell;

	UpdateData(FALSE);
}

void CNaviModifyTab::LineID_CheckBoxClear()
{
	for (auto& CheckBox : m_cbLineID)
		CheckBox = FALSE;

	UpdateData(FALSE);
}

void CNaviModifyTab::Enable_LineOption(const _bool & bEnable)
{
	//line check box
	GetDlgItem(IDC_CHECK5)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK6)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK7)->EnableWindow(bEnable);

	//line type radio btn
	GetDlgItem(IDC_RADIO6)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO7)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO8)->EnableWindow(bEnable);

	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT18)->EnableWindow(bEnable);

	//apply btn
	GetDlgItem(IDC_BUTTON6)->EnableWindow(bEnable);
}


BEGIN_MESSAGE_MAP(CNaviModifyTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNaviModifyTab::OnBnClicked_ObjLoad)
	ON_BN_CLICKED(IDC_CHECK2, &CNaviModifyTab::OnBnClickedNavMeshModing)
	ON_BN_CLICKED(IDC_CHECK1, &CNaviModifyTab::OnBnClickedHideBtn)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CNaviModifyTab::OnDeltaposSpinPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CNaviModifyTab::OnDeltaposSpinPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CNaviModifyTab::OnDeltaposSpinPosZ)
	ON_BN_CLICKED(IDC_BUTTON5, &CNaviModifyTab::OnBnClickedClearTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CNaviModifyTab::OnTvnSelchangedTree)
	ON_BN_CLICKED(IDC_BUTTON4, &CNaviModifyTab::OnBnClickedButtonColorSetUp)
	ON_BN_CLICKED(IDC_BUTTON7, &CNaviModifyTab::OnBnClickedDeleteNavMesh)
	ON_BN_CLICKED(IDC_CHECK4, &CNaviModifyTab::OnBnClicked_HideCell)
	ON_BN_CLICKED(IDC_CHECK3, &CNaviModifyTab::OnBnClicked_HideVtx)
	ON_BN_CLICKED(IDC_BUTTON6, &CNaviModifyTab::OnBnClicked_LineOptionApply)
	ON_BN_CLICKED(IDC_RADIO6, &CNaviModifyTab::OnBnClicked_LineTypeBase)
	ON_BN_CLICKED(IDC_RADIO7, &CNaviModifyTab::OnBnClicked_LineTypeLeave)
	ON_BN_CLICKED(IDC_RADIO8, &CNaviModifyTab::OnBnClicked_LineTypeConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CNaviModifyTab::OnBnClickedNavMeshSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CNaviModifyTab::OnBnClicked_DatLoad)
END_MESSAGE_MAP()

 
// CNaviModifyTab 메시지 처리기입니다.

void CNaviModifyTab::OnBnClicked_ObjLoad()
{
	CFileDialog Dlg(TRUE,
		L"Obj",
		L"*.Obj",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.Obj) |*.Obj||", this);
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
		CManagement::Get_Instance()->Ready_Mesh(strFileName, eResourcesID::NaviMesh,
			strFilePath, strFileName);

		m_pNavMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device(), strFileName);
		CManagement::Get_Instance()->Add_InstantGameObject(m_pNavMesh, L"Layer_NaviMesh");
		m_pListNavMeshObj = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");
		CManagement::Get_Instance()->Get_GameObjet(L"Layer_NaviMesh");

		SetUp_Tree(Dlg.GetFileTitle());
	}


}


void CNaviModifyTab::OnBnClickedStaticLoad()
{
	CFileDialog Dlg(TRUE,
		L"x",
		L"*.x",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.x) |*.x||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		CString strFileName = Dlg.GetFileName();

		////추가하고 
		//CManagement::Get_Instance()->Ready_Mesh(strFileName, eResourcesID::StaticMesh,
		//	strFilePath, strFileName);

		//m_pStaticMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device(),
		//	strFileName);
		//CManagement::Get_Instance()->Add_InstantGameObject(m_pStaticMesh, L"NaviMesh_Layer");
	}
}


void CNaviModifyTab::OnBnClickedNavMeshModing()
{
	UpdateData(TRUE);
	NULL_CHECK_RETURN_MSG(m_pNavMesh, ,L"pNasMesh is Nullptr");
	
	m_pNavMesh->m_bModding = m_bVtxModing == 1 ? true : false;

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNaviModifyTab::OnBnClickedHideBtn()
{
	UpdateData(TRUE);
	m_bHide_ComboBox;
	CGameObject* pObj = CManagement::Get_Instance()->Get_GameObjet(L"Layer_Terrain");
	if(m_bHide_ComboBox)
		pObj->Set_Enalbe(false);
	else
		pObj->Set_Enalbe(true);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
}

// 트리컨트롤로 Cell  , NavMesh 탐색
void CNaviModifyTab::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	if (m_pListNavMeshObj == nullptr)
		return;


	//  정리 
	//1. 피킹셀 인덱스 초기화
	//2. 셀 리스트 순회 검사 
	//3. pos ShowText_Cell 콜 
	//4. 못찾으면 셀 인덱스 에러값으로 

	int iIndex = 0;
	HTREEITEM hItem = m_tcTreeCtrl.GetSelectedItem();
	HTREEITEM hLoop;
	m_bNowPeeking = false;
	Enable_LineOption(false);
	//root 클릭 예외처리
	if (hItem == m_tcTreeCtrl.GetRootItem())
		return;
	//매쉬 셀렉트 
	if (m_tcTreeCtrl.ItemHasChildren(hItem))
	{
		m_iNavMeshIdx = 0;
		hLoop = m_tcTreeCtrl.GetParentItem(hItem);
		hLoop = m_tcTreeCtrl.GetChildItem(hLoop);

		while (hLoop != nullptr)
		{
			if (hLoop == hItem)
			{
				//select Nav name 설정 
				m_sSelectNavName = m_tcTreeCtrl.GetItemText(hItem);
				UpdateData(FALSE);
				m_bNowPeeking = true;
				//m_pNavMesh 변경

				//변경전 이전값에서 정리할거 (select, 또 있나)
				if (m_pNavMesh != nullptr)
				{
					m_pNavMesh->m_pNaviCom->Set_Select(false);
				}
				m_pNavMesh = Get_ObjFromNavLayer(m_iNavMeshIdx);
				m_pNavMesh->m_pNaviCom->Set_Select(true);
				SetUp_HideOption();
				return;
			}

			hLoop = m_tcTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
			++m_iNavMeshIdx;
		}
		m_iNavMeshIdx = NOT_FOUND;
	}
	//Cell Select
	else
	{

		m_iPeekCellIdx = 0;
		hLoop = m_tcTreeCtrl.GetParentItem(hItem);
		m_sSelectNavName = m_tcTreeCtrl.GetItemText(hLoop);
		UpdateData(FALSE);
		hLoop = m_tcTreeCtrl.GetChildItem(hLoop);
		while (hLoop != nullptr)
		{
			if (hLoop == hItem)
			{
				ShowText_Cell(iIndex);
				m_bNowPeeking = true;
				return;
			}

			hLoop = m_tcTreeCtrl.GetNextItem(hLoop, TVGN_NEXT);
			++m_iPeekCellIdx;
		}
		m_iPeekCellIdx = NOT_FOUND;

	}
	m_sSelectNavName = L"";

	UpdateData(FALSE);
	*pResult = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region SpinCtrl


void CNaviModifyTab::OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bNowPeeking == false)
		return;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_vCellVtx()[m_iPeekVtxIdx];
	SelectVtx.x += (pNMUpDown->iDelta) / 10.f;;

	Update_VtxPosEdit(SelectVtx);
	m_pNavMesh->m_pNaviCom->Modifying_Vertex(m_iPeekVtxIdx);

	*pResult = 0;
}

void CNaviModifyTab::OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bNowPeeking == false)
		return;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_vCellVtx()[m_iPeekVtxIdx];
	SelectVtx.y += (pNMUpDown->iDelta) / 10.f;;
	Update_VtxPosEdit(SelectVtx);

	m_pNavMesh->m_pNaviCom->Modifying_Vertex(m_iPeekVtxIdx);

	*pResult = 0;
}


void CNaviModifyTab::OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bNowPeeking == false)
		return;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_vCellVtx()[m_iPeekVtxIdx];
	SelectVtx.z += (pNMUpDown->iDelta) / 10.f;;
	Update_VtxPosEdit(SelectVtx);

	m_pNavMesh->m_pNaviCom->Modifying_Vertex(m_iPeekVtxIdx);

	*pResult = 0;
}
#pragma endregion



void CNaviModifyTab::OnBnClickedClearTree()
{
	if (m_pNavMesh == nullptr)
		return;

	HTREEITEM hLoop = m_tcTreeCtrl.GetRootItem(); // loot
	hLoop = m_tcTreeCtrl.GetChildItem(hLoop);
	// Tree Clear
	while (hLoop != nullptr)
	{
		HTREEITEM hTemp  = m_tcTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
		m_tcTreeCtrl.DeleteItem(hLoop);
		hLoop = hTemp;
	}
	//obj layer Clear 
	if (m_pListNavMeshObj != nullptr)
	{
		for (auto& pObj : *m_pListNavMeshObj)
		{
			pObj->Set_Delete();
		}
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}





BOOL CNaviModifyTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_spPosX.SetRange(-500, 500);
	m_spPosY.SetRange(-500, 500);
	m_spPosZ.SetRange(-500, 500);

	m_PeekingBnt[0].SetCheck(TRUE);
	m_CellTypeBnt[0].SetCheck(TRUE);

	HTREEITEM root;
	root = m_tcTreeCtrl.InsertItem(L"Root", 0, 0, TVI_ROOT, TVI_LAST);

	Enable_LineOption(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CNaviModifyTab::SetUp_Tree(const CString& strName)
{
	if (m_pNavMesh == nullptr)
		return;
	CString NaviMeshRoot, ObjEntry;


	HTREEITEM root, NaviMesh, Vtx;
	root = m_tcTreeCtrl.GetRootItem();
	NaviMesh = m_tcTreeCtrl.InsertItem(strName, 0, 0, root, TVI_LAST);

	_uint idx = 0;
	for (auto& pCell : m_pNavMesh->m_pNaviCom->Get_vCell())
	{
		ObjEntry.Format(L"Cell [%d]", idx);
		m_tcTreeCtrl.InsertItem(ObjEntry, 0, 0, NaviMesh, TVI_LAST);
		++idx;
	}
	UpdateData(FALSE);
}


void CNaviModifyTab::OnBnClickedButtonColorSetUp()
{
	NULL_CHECK_RETURN_MSG(m_pNavMesh, ,L"m_pNavMesh is nullptr");
	UpdateData(TRUE);

	_uint iR =  _ttoi(m_sColorR.GetString());
	_uint iG = _ttoi(m_sColorG.GetString());
	_uint iB = _ttoi(m_sColorB.GetString());

	for (auto& pCell : m_pNavMesh->m_pNaviCom->Get_vCell())
	{
		pCell->Set_BaseColor(D3DCOLOR_XRGB(iR, iG, iB));
		//CellType 속성 부여한거 까지 싹다 색깔 초기화 하면 곤란하니 base 값만 
		if (pCell->Get_CellType() == eCellType::Base)
		{
			pCell->Set_Color(D3DCOLOR_XRGB(iR, iG, iB));
			pCell->Modifying_Buffer();
		}
	}

}


void CNaviModifyTab::OnBnClickedDeleteNavMesh()
{
	if (m_pListNavMeshObj == nullptr || m_iNavMeshIdx == NOT_FOUND)
		return;

	// changed Tree에서 셋업한 pNavMesh 
	m_pNavMesh->Set_Delete();

	// Tree Delete
	HTREEITEM hLoop = m_tcTreeCtrl.GetRootItem(); // loot
	hLoop = m_tcTreeCtrl.GetChildItem(hLoop);
	_uint iIdx = 0;
	// Tree Clear
	while (hLoop != nullptr)
	{
		if (iIdx == m_iNavMeshIdx)
		{
			m_tcTreeCtrl.DeleteItem(hLoop);
			m_iNavMeshIdx = NOT_FOUND;
			break;
		}
		hLoop = m_tcTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
		++iIdx;
	}

}


void CNaviModifyTab::OnBnClicked_HideCell()
{
	UpdateData(TRUE);
	m_pNavMesh->m_bHideCell = BOOLTobool( m_cbHideCell);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNaviModifyTab::OnBnClicked_HideVtx()
{
	UpdateData(TRUE);
	m_pNavMesh->m_bHideVtx = BOOLTobool(m_cbHideVtx);
	
}


void CNaviModifyTab::OnBnClicked_LineTypeBase()
{
	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(false);
	GetDlgItem(IDC_EDIT18)->EnableWindow(false);
}


void CNaviModifyTab::OnBnClicked_LineTypeLeave()
{
	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(false);
	GetDlgItem(IDC_EDIT18)->EnableWindow(false);
}


void CNaviModifyTab::OnBnClicked_LineTypeConnect()
{
	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(true);
	GetDlgItem(IDC_EDIT18)->EnableWindow(true);
}


void CNaviModifyTab::OnBnClicked_LineOptionApply()
{
	if (m_pNavMesh == nullptr)
		return;
	UpdateData(TRUE);
	for (int i = eLineID::AB; i < eLineID::End; ++i)
	{
		if (m_cbLineID[i])
		{
			for (int j = 0; j < eCellType::End; ++j)
			{
				if (m_LineTypeBnt[j].GetCheck())
				{
					/*				m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
									->Set_LineOption((eLineID::eLineID)i, (eCellType::eCellType)j);
				*/
					m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
					->Get_Line((eLineID::eLineID)i)->Set_Type((eCellType::eCellType)j);
				}
			}
		}
		else
		{
			//m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
			//	->Set_LineOption((eLineID::eLineID)i, eCellType::Base);

			m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
				->Get_Line((eLineID::eLineID)i)->Set_Type(eCellType::Base);
		}
	}
}


void CNaviModifyTab::OnBnClickedNavMeshSave()
{
	if (m_pNavMesh == nullptr)
		return;
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
		if (FAILED(m_pNavMesh->SaveFile(strFilePath.GetString())))
		{
			MSG_BOX(L"Failed Save");
		}
	}
}


void CNaviModifyTab::OnBnClicked_DatLoad()
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
		m_pListNavMeshObj = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");
		CManagement::Get_Instance()->Get_GameObjet(L"Layer_NaviMesh");

		SetUp_Tree(Dlg.GetFileTitle());
	}
}
