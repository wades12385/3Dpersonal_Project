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
	, m_sPeeking_VtxIdx(_T(""))
	, m_sPosX(_T(""))
	, m_sPosY(_T(""))
	, m_sPosZ(_T(""))
	, m_bNowPeeking(false)
	, m_iPeekVtxIdx(NOT_FOUND)
	, m_iPeekCellIdx(NOT_FOUND)
	, m_iNavMeshIdx(NOT_FOUND)
	, m_sPeeking_CellIdx(_T(""))
	, m_sColorR(_T(""))
	, m_sColorG(_T(""))
	, m_sColorB(_T(""))
	, m_sNaviID(_T(""))
	, m_sSelectNavName(_T(""))
	, m_cbHideCell(FALSE)
	, m_cbHideVtx(FALSE)
	, m_sLineOptionID(_T(""))
	, m_sLineOptionIdx(_T(""))
	, m_sCellOptionID(_T(""))
	, m_sCellOptionIdx(_T(""))
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

CNaviModifyTab::~CNaviModifyTab()
{
	//SafeRelease(m_pNavMesh);
}

void CNaviModifyTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, m_bVtxModing);
	DDX_Check(pDX, IDC_CHECK1, m_bHide_ComboBox);
	DDX_Text(pDX, IDC_EDIT10, m_sPeeking_VtxIdx);
	DDX_Text(pDX, IDC_EDIT1, m_sPosX);
	DDX_Text(pDX, IDC_EDIT2, m_sPosY);
	DDX_Text(pDX, IDC_EDIT3, m_sPosZ);
	DDX_Control(pDX, IDC_SPIN1, m_spPosX);
	DDX_Control(pDX, IDC_SPIN2, m_spPosY);
	DDX_Control(pDX, IDC_SPIN3, m_spPosZ);
	DDX_Control(pDX, IDC_TREE1, m_NavTreeCtrl);
	DDX_Control(pDX, IDC_RADIO4, m_PeekingBnt[ePeekingMod::VTX]);
	DDX_Control(pDX, IDC_RADIO5, m_PeekingBnt[ePeekingMod::CELL]);
	DDX_Text(pDX, IDC_EDIT11, m_sPeeking_CellIdx);
	DDX_Text(pDX, IDC_EDIT12, m_sColorR);
	DDX_Text(pDX, IDC_EDIT13, m_sColorG);
	DDX_Text(pDX, IDC_EDIT14, m_sColorB);
	DDX_Text(pDX, IDC_EDIT15, m_sNaviID);
	DDX_Text(pDX, IDC_EDIT17, m_sSelectNavName);
	DDX_Check(pDX, IDC_CHECK4, m_cbHideCell);
	DDX_Check(pDX, IDC_CHECK3, m_cbHideVtx);
	DDX_Control(pDX, IDC_RADIO3, m_rbLineType[0]);
	DDX_Control(pDX, IDC_RADIO13, m_rbLineType[1]);
	DDX_Control(pDX, IDC_RADIO14, m_rbLineType[2]);
	DDX_Text(pDX, IDC_EDIT16, m_sLineOptionID);
	DDX_Text(pDX, IDC_EDIT18, m_sLineOptionIdx);
	DDX_Control(pDX, IDC_RADIO2, m_rbLine[eLineID::AB]);
	DDX_Control(pDX, IDC_RADIO11, m_rbLine[eLineID::BC]);
	DDX_Control(pDX, IDC_RADIO12, m_rbLine[eLineID::CA]);
	DDX_Control(pDX, IDC_LIST2, m_lbLineLink);
	DDX_Control(pDX, IDC_LIST1, m_lbCellLink);
	DDX_Text(pDX, IDC_EDIT4, m_sCellOptionID);
	DDX_Text(pDX, IDC_EDIT21, m_sCellOptionIdx);
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
	ON_BN_CLICKED(IDC_BUTTON4, &CNaviModifyTab::OnBnClickedNaviMeshOption)
	ON_BN_CLICKED(IDC_BUTTON7, &CNaviModifyTab::OnBnClickedDeleteNavMesh)
	ON_BN_CLICKED(IDC_CHECK4, &CNaviModifyTab::OnBnClicked_HideCell)
	ON_BN_CLICKED(IDC_CHECK3, &CNaviModifyTab::OnBnClicked_HideVtx)
	ON_BN_CLICKED(IDC_BUTTON6, &CNaviModifyTab::OnBnClickedLineOption_AddLinkCell)
	ON_BN_CLICKED(IDC_RADIO3, &CNaviModifyTab::OnBnClicked_LineTypeBase)
	ON_BN_CLICKED(IDC_RADIO13, &CNaviModifyTab::OnBnClicked_LineTypeLeave)
	ON_BN_CLICKED(IDC_RADIO14, &CNaviModifyTab::OnBnClicked_LineTypeConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CNaviModifyTab::OnBnClickedNavMeshSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CNaviModifyTab::OnBnClicked_DatLoad)
	ON_BN_CLICKED(IDC_BUTTON17, &CNaviModifyTab::OnBnClicked_LineOptionApply)
	ON_BN_CLICKED(IDC_BUTTON18, &CNaviModifyTab::OnBnClickedCellTypeBase)
	ON_BN_CLICKED(IDC_BUTTON19, &CNaviModifyTab::OnBnClickedCellTypeConnect)
	ON_BN_CLICKED(IDC_BUTTON10, &CNaviModifyTab::OnBnClickedCellOption_AddLinkCell)
	ON_BN_CLICKED(IDC_BUTTON14, &CNaviModifyTab::OnBnClickedCellOption_DeleteLinkCell)
	ON_BN_CLICKED(IDC_BUTTON11, &CNaviModifyTab::OnBnClickedCellOption_Clear)
	ON_BN_CLICKED(IDC_BUTTON16, &CNaviModifyTab::OnBnClickedLineOption_DeleteLinkCell)
	ON_BN_CLICKED(IDC_BUTTON15, &CNaviModifyTab::OnBnClickedLineOption_Clear)
	ON_BN_CLICKED(IDC_RADIO2, &CNaviModifyTab::OnBnClicked_LineAB)
	ON_BN_CLICKED(IDC_RADIO11, &CNaviModifyTab::OnBnClicked_LineBC)
	ON_BN_CLICKED(IDC_RADIO12, &CNaviModifyTab::OnBnClicked_Line_CA)
END_MESSAGE_MAP()


void CNaviModifyTab::ShowText_Vtx(int idx)
{
	m_iPeekVtxIdx = idx;
	m_sPeeking_VtxIdx.Format(_T("%d"), idx);
	_vec3 vSelectVtx = m_pNavMesh->m_pNaviCom->Get_Vertex()[idx];
	Update_VtxPosEdit(vSelectVtx);
}

void CNaviModifyTab::ShowText_Cell(int idx)
{
	m_iPeekCellIdx = idx;
	m_sPeeking_CellIdx.Format(_T("%d"), m_iPeekCellIdx);
}

void CNaviModifyTab::Update_VtxPosEdit(_vec3 vPos)
{
	m_sPosX.Format(_T("%.2f"), vPos.x);
	m_sPosY.Format(_T("%.2f"), vPos.y);
	m_sPosZ.Format(_T("%.2f"), vPos.z);
}

CNaviObj * CNaviModifyTab::Find_NavMeshFromLayer()
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


void CNaviModifyTab::Peeking(const CPoint & point)
{
	NULL_CHECK(m_pNavMesh);
	_int iIdx;
	//피킹 옵션 체크 
	m_iPeekCellIdx = NOT_FOUND;
	m_iPeekVtxIdx = NOT_FOUND;
	m_lbCellLink.ResetContent();
	m_lbLineLink.ResetContent();
	if (m_PeekingBnt[ePeekingMod::VTX].GetCheck())
	{
		//버텍스 피킹 상태에서  Cell idx 랑 라인옵션 그룹 비활성화 

		Enable_LineOption(false);
		Enable_CellOption(false);
		m_sPeeking_CellIdx = L"NULL";

		if (m_pNavMesh->Vertex_Peeking(_vec2((float)point.x, (float)point.y), iIdx))
		{
			m_pNavMesh->m_bPeekCell = false;
			m_pNavMesh->m_bPeekVTX = true;
			m_pNavMesh->m_ipeekIdx[0] = iIdx;


			ShowText_Vtx(iIdx);
			m_bNowPeeking = true;
		}
		else
		{
			m_pNavMesh->m_bPeekCell = false;
			m_pNavMesh->m_bPeekVTX = false;
			m_sPeeking_VtxIdx = L"NULL";
			m_bNowPeeking = false;
		}
	}
	//Cell Peeking
	else
	{
		m_sPeeking_VtxIdx.Format(_T("NULL"));
		ReSet_LineBtn();
		if (m_pNavMesh->Cell_Peeking(_vec2((float)point.x, (float)point.y), iIdx,_vec3()))
		{
			m_bNowPeeking = true;

			Enable_CellOption(true);

			//NavOjb Peeking update
			m_pNavMesh->m_bPeekCell = true;
			m_pNavMesh->m_bPeekVTX = false;
			m_pNavMesh->m_ipeekIdx[eCellpt::A] = m_pNavMesh->m_pNaviCom->Get_vCell()[iIdx]->Get_CellVtxIdx()._A;
			m_pNavMesh->m_ipeekIdx[eCellpt::B] = m_pNavMesh->m_pNaviCom->Get_vCell()[iIdx]->Get_CellVtxIdx()._B;
			m_pNavMesh->m_ipeekIdx[eCellpt::C] = m_pNavMesh->m_pNaviCom->Get_vCell()[iIdx]->Get_CellVtxIdx()._C;


			eCellType::eCellType Type = m_pNavMesh->m_pNaviCom->Get_vCell()[iIdx]->Get_CellType();
			//linkCells 리스트 갱신
			if (Type == eCellType::Connect)
			{
				Enable_CellOption_Connect(true);
				Update_CellLinkListBox(iIdx);
				Enable_LineOption(false);
			}
			else
			{
				Enable_CellOption_Connect(false);
				Enable_LineOption(true);
			}
			ShowText_Cell(iIdx);
		}
		else
		{
			m_pNavMesh->m_bPeekCell = false;
			m_pNavMesh->m_bPeekVTX = false;
			Enable_CellOption(false);
			Enable_LineOption(false);
			m_sPeeking_CellIdx.Format(L"NULL");
		}
	}

	UpdateData(FALSE);
}

void CNaviModifyTab::Enable_LineOption(const _bool & bEnable)
{
	//line check box
	GetDlgItem(IDC_RADIO2)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO11)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO12)->EnableWindow(bEnable);

	//line type 
	GetDlgItem(IDC_RADIO3)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO13)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO14)->EnableWindow(bEnable);

	//apply
	GetDlgItem(IDC_BUTTON17)->EnableWindow(bEnable);

	//list
	GetDlgItem(IDC_BUTTON15)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON16)->EnableWindow(bEnable);
	GetDlgItem(IDC_LIST2)->EnableWindow(bEnable);


	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT18)->EnableWindow(bEnable);

	//add link btn
	GetDlgItem(IDC_BUTTON6)->EnableWindow(bEnable);
}

void CNaviModifyTab::Enable_LineOption_Connect(const _bool & bEnable)
{

	GetDlgItem(IDC_BUTTON15)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON16)->EnableWindow(bEnable);
	GetDlgItem(IDC_LIST2)->EnableWindow(bEnable);

	//edit box
	GetDlgItem(IDC_EDIT16)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT18)->EnableWindow(bEnable);

	//add link btn
	GetDlgItem(IDC_BUTTON6)->EnableWindow(bEnable);
}

void CNaviModifyTab::Enable_CellOption(const _bool & bEnable)
{
	//cell type 
	GetDlgItem(IDC_BUTTON18)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON19)->EnableWindow(bEnable);

	//list
	GetDlgItem(IDC_LIST1)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(bEnable);


	//link
	GetDlgItem(IDC_EDIT4)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT21)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(bEnable);

}

void CNaviModifyTab::Enable_CellOption_Connect(const _bool & bEnable)
{
	//list
	GetDlgItem(IDC_LIST1)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(bEnable);

	//link
	GetDlgItem(IDC_EDIT4)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT21)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(bEnable);
}

void CNaviModifyTab::Update_CellLinkListBox(const _int & iCellIdx)
{
	m_lbCellLink.ResetContent();
	CString str;
	for (auto& tLinkCell : m_pNavMesh->m_pNaviCom->Get_vCell()[iCellIdx]->Get_LinkCells())
	{
		str.Format(L"ID: %d / IDX: %d", tLinkCell.iNaviID, tLinkCell.iCellIdx);
		m_lbCellLink.AddString(str);
	}
}

void CNaviModifyTab::Update_LineLinkListBox(const _int & iCellIdx, const eLineID::eLineID & eLineID)
{
	m_lbLineLink.ResetContent();
	CString str;
	for (auto& tLinkCell : m_pNavMesh->m_pNaviCom->Get_vCell()[iCellIdx]->Get_Line(eLineID)->Get_LinkCells())
	{
		str.Format(L"ID: %d / IDX: %d", tLinkCell.iNaviID, tLinkCell.iCellIdx);
		m_lbLineLink.AddString(str);
	}
}

void CNaviModifyTab::ReSet_LineBtn()
{
	for (int i = 0; i < eLineID::End; ++i)
		m_rbLine[i].SetCheck(false);

	ReSet_LineTypeBtn();
}

void CNaviModifyTab::ReSet_LineTypeBtn()
{
	for (int i = 0; i < eLineID::End; ++i)
		m_rbLineType[i].SetCheck(false);
}

void CNaviModifyTab::Setup_LineOfLink(CCell * pCell, const _int& iLineID)
{
	auto& LinkCells = pCell->Get_Line((eLineID::eLineID)iLineID)->Get_LinkCells();
	LinkCells.clear();
	LinkCells.shrink_to_fit();

	_int iBoxCnt = m_lbLineLink.GetCount();
	LinkCells.reserve(iBoxCnt);

	CString str;
	LINKCELL tLink;
	for (int i = 0; i < iBoxCnt; ++i)
	{
		m_lbLineLink.GetText(i, str);
		swscanf_s(str, L"ID: %d / Idx: %d", &tLink.iNaviID, &tLink.iCellIdx);
		LinkCells.emplace_back(tLink);
	}
}


 
// CNaviModifyTab 메시지 처리기입니다.


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
	NULL_CHECK_RETURN(m_pNavMesh, );
	
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
	
	//처음 초기화 과정에서  호출되는거 떄문에 매크로로 안썼음 
	if (m_pListNavMeshObj == nullptr) 
		return;
	//  정리 
	//1. 피킹셀 인덱스 초기화
	//2. 셀 리스트 순회 검사 
	//3. pos ShowText_Cell 콜 
	//4. 못찾으면 셀 인덱스 에러값으로 

	int iIndex = 0;
	HTREEITEM hItem = m_NavTreeCtrl.GetSelectedItem();
	HTREEITEM hLoop;
	m_bNowPeeking = false;
	Enable_LineOption(false);
	//root 클릭 예외처리
	if (hItem == m_NavTreeCtrl.GetRootItem())
		return;
	//매쉬 셀렉트 
	if (m_NavTreeCtrl.ItemHasChildren(hItem))
	{
		m_iNavMeshIdx = 0;
		hLoop = m_NavTreeCtrl.GetParentItem(hItem);
		hLoop = m_NavTreeCtrl.GetChildItem(hLoop);

		while (hLoop != nullptr)
		{
			if (hLoop == hItem)
			{
				//select Nav name 설정 
				m_sSelectNavName = m_NavTreeCtrl.GetItemText(hItem);
				m_bNowPeeking = true;
				//m_pNavMesh 변경

				//변경전 이전값에서 정리할거 (select, 또 있나)
				if (m_pNavMesh != nullptr)
				{
					m_pNavMesh->m_bPeekCell = false;
					m_pNavMesh->m_bPeekVTX = false;
					m_pNavMesh->m_pNaviCom->Set_Select(false);
				}
				m_pNavMesh = Find_NavMeshFromLayer();
				m_pNavMesh->m_pNaviCom->Set_Select(true);
				m_sNaviID.Format(L"%d", m_pNavMesh->m_pNaviCom->Get_NaviID());
				SetUp_HideOption();
				UpdateData(FALSE);
				return;
			}

			hLoop = m_NavTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
			++m_iNavMeshIdx;
		}
		m_iNavMeshIdx = NOT_FOUND;
	}
	//Cell Select
	else
	{

		m_iPeekCellIdx = 0;
		hLoop = m_NavTreeCtrl.GetParentItem(hItem);
		m_sSelectNavName = m_NavTreeCtrl.GetItemText(hLoop);
		UpdateData(FALSE);
		hLoop = m_NavTreeCtrl.GetChildItem(hLoop);
		while (hLoop != nullptr)
		{
			if (hLoop == hItem)
			{
				ShowText_Cell(m_iPeekCellIdx);
				m_bNowPeeking = true;
				return;
			}

			hLoop = m_NavTreeCtrl.GetNextItem(hLoop, TVGN_NEXT);
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

	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_Vertex()[m_iPeekVtxIdx];
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

	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_Vertex()[m_iPeekVtxIdx];
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
	_vec3& SelectVtx = m_pNavMesh->m_pNaviCom->Get_Vertex()[m_iPeekVtxIdx];
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

	HTREEITEM hLoop = m_NavTreeCtrl.GetRootItem(); // loot
	hLoop = m_NavTreeCtrl.GetChildItem(hLoop);
	// Tree Clear
	while (hLoop != nullptr)
	{
		HTREEITEM hTemp  = m_NavTreeCtrl.GetNextItem(hLoop, TVGN_NEXTVISIBLE);
		m_NavTreeCtrl.DeleteItem(hLoop);
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
	m_pNavMesh = nullptr;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}





BOOL CNaviModifyTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_spPosX.SetRange(-500, 500);
	m_spPosY.SetRange(-500, 500);
	m_spPosZ.SetRange(-500, 500);


	HTREEITEM root;
	root = m_NavTreeCtrl.InsertItem(L"Root", 0, 0, TVI_ROOT, TVI_LAST);

	Enable_CellOption(false);
	Enable_LineOption(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CNaviModifyTab::SetUp_Tree(const CString& strName, const CNaviObj* pMesh)
{
	if (pMesh == nullptr)
		return;
	CString  ObjEntry;


	HTREEITEM root, NaviMesh;
	root = m_NavTreeCtrl.GetRootItem();
	NaviMesh = m_NavTreeCtrl.InsertItem(strName, 0, 0, root, TVI_LAST);

	_uint idx = 0;
	for (auto& pCell : pMesh->m_pNaviCom->Get_vCell())
	{
		ObjEntry.Format(L"Cell [%d]", idx);
		m_NavTreeCtrl.InsertItem(ObjEntry, 0, 0, NaviMesh, TVI_LAST);
		++idx;
	}
	UpdateData(FALSE);
}

/*네비매쉬 베이스 색이랑 id 세팅*/
void CNaviModifyTab::OnBnClickedNaviMeshOption()
{
	NULL_CHECK_RETURN_MSG(m_pNavMesh, ,L"m_pNavMesh is nullptr");
	UpdateData(TRUE);

	_float fR = (_float)_ttof(m_sColorR.GetString());
	_float fG = (_float)_ttof(m_sColorG.GetString());
	_float fB = (_float)_ttof(m_sColorB.GetString());
	m_pNavMesh->m_pNaviCom->Set_BaseColor(_vec3(fR,fG,fB));
	m_pNavMesh->m_pNaviCom->Set_NaviID(_ttoi(m_sNaviID));
}


void CNaviModifyTab::OnBnClickedDeleteNavMesh()
{
	if (m_pListNavMeshObj == nullptr || m_iNavMeshIdx == NOT_FOUND)
		return;

	// changed Tree에서 셋업한 pNavMesh 
	m_pNavMesh->Set_Delete();
	m_pNavMesh = nullptr;
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
	Enable_LineOption_Connect(false);
}


void CNaviModifyTab::OnBnClicked_LineTypeLeave()
{
	//edit box
	Enable_LineOption_Connect(false);
}


void CNaviModifyTab::OnBnClicked_LineTypeConnect()
{
	//edit box
	Enable_LineOption_Connect(true);
}


void CNaviModifyTab::OnBnClickedNavMeshSave()
{

	NULL_CHECK(m_pNavMesh);

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
		CNaviObj* pMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device());
		CNaviMesh* pNaviMeshCom = CNaviMesh::Create(CManagement::Get_Instance()->Get_Device(), Dlg.GetPathName(),true);
		pMesh->Set_Navi(pNaviMeshCom);

		CManagement::Get_Instance()->Add_InstantGameObject(pMesh, L"Layer_NaviMesh");
		m_pListNavMeshObj = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");
		SetUp_Tree(Dlg.GetFileTitle(), pMesh);
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
		CNaviObj* pMesh = CNaviObj::Create(CManagement::Get_Instance()->Get_Device());
		CNaviMesh* pNaviMeshCom = CNaviMesh::Load(CManagement::Get_Instance()->Get_Device(),Dlg.GetPathName(), true);
		pMesh->Set_Navi(pNaviMeshCom);

		CManagement::Get_Instance()->Add_InstantGameObject(pMesh, L"Layer_NaviMesh");
		m_pListNavMeshObj = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");
		SetUp_Tree(Dlg.GetFileTitle(), pMesh);
	}
}


void CNaviModifyTab::OnBnClicked_LineOptionApply()
{

	if (m_pNavMesh == nullptr)
		return;

	UpdateData(TRUE);
	//커넥트 셀 단독 옵션 적용 판별용
	CCell* pSelectCell = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx];

	for (int i = eLineID::AB; i < eLineID::End; ++i) // line ID
	{
		if (m_rbLine[i].GetCheck())
		{
			// 라인 타입
			if (m_rbLineType[eCellType::Connect].GetCheck())
			{
				UpdateData(TRUE);
				//Type setter, 네비의 아디  ,셀인덱스
				pSelectCell->Set_LineTrigger((eLineID::eLineID)i, eCellType::Connect);
				Setup_LineOfLink(pSelectCell, i);
			}
			else if ( m_rbLineType[eCellType::Leave].GetCheck())
				pSelectCell->Set_LineTrigger((eLineID::eLineID)i, eCellType::Leave);
			else
				pSelectCell->Set_LineTrigger((eLineID::eLineID)i, eCellType::Base);
		}

	}
}


void CNaviModifyTab::OnBnClickedCellTypeBase()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]->Set_CellType(eCellType::Base);
	Enable_CellOption_Connect(false);
	Enable_LineOption(true);
}


void CNaviModifyTab::OnBnClickedCellTypeConnect()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;
	m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]->Set_CellType(eCellType::Connect);
	Enable_CellOption_Connect(true);
	Enable_LineOption(false);
}


void CNaviModifyTab::OnBnClickedCellOption_AddLinkCell()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;
	UpdateData(TRUE);
	
	CString str;

	str.Format(L"ID: %s / Idx: %s", m_sCellOptionID, m_sCellOptionIdx);
	m_lbCellLink.AddString(str);

	LINKCELL tLink(_ttoi(m_sCellOptionID), _ttoi(m_sCellOptionIdx));

	m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]->Get_LinkCells().emplace_back(tLink);

}


void CNaviModifyTab::OnBnClickedCellOption_DeleteLinkCell()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	_int iDeleteSel = m_lbCellLink.GetCurSel();
	m_lbCellLink.DeleteString(iDeleteSel);
	if (iDeleteSel == NOT_FOUND)
		return;
	vector<LINKCELL>& LinkCells = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]->Get_LinkCells();
	auto iter = LinkCells.begin();

	for (int i = 0; iter != LinkCells.end(); ++i, ++iter)
	{
		if (i == iDeleteSel)
		{
			LinkCells.erase(iter);
			return;
		}
	}
}


void CNaviModifyTab::OnBnClickedCellOption_Clear()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	m_lbCellLink.ResetContent();
	auto& LinkCells = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]->Get_LinkCells();
	LinkCells.clear();
	LinkCells.shrink_to_fit();
}


void CNaviModifyTab::OnBnClickedLineOption_AddLinkCell()
{

	UpdateData(TRUE);

	CString str;

	str.Format(L"ID: %s / Idx: %s", m_sLineOptionID, m_sLineOptionIdx);
	m_lbLineLink.AddString(str);
}


void CNaviModifyTab::OnBnClickedLineOption_DeleteLinkCell()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	_int iDeleteSel = m_lbLineLink.GetCurSel();
	m_lbLineLink.DeleteString(iDeleteSel);
	if (iDeleteSel == NOT_FOUND)
		return;
	for (int LineID = 0; LineID < eLineID::End; ++LineID)
	{
		if (m_rbLine[LineID].GetCheck())
		{
			vector<LINKCELL>& LinkCells = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
				->Get_Line((eLineID::eLineID)LineID)->Get_LinkCells();
			auto iter = LinkCells.begin();

			for (int i = 0; iter != LinkCells.end(); ++i, ++iter)
			{
				if (i == iDeleteSel)
				{
					LinkCells.erase(iter);
					return;
				}
			}
			return;
		}
	}
}


void CNaviModifyTab::OnBnClickedLineOption_Clear()
{
	for (int LineID = 0; LineID < eLineID::End; ++LineID)
	{
		if (m_rbLine[LineID].GetCheck())
		{
			vector<LINKCELL>& LinkCells = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
				->Get_Line((eLineID::eLineID)LineID)->Get_LinkCells();

			LinkCells.clear();
			LinkCells.shrink_to_fit();

			m_lbLineLink.ResetContent();
			return;
		}
	}
}


void CNaviModifyTab::OnBnClicked_LineAB()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	ReSet_LineTypeBtn();
	eCellType::eCellType eType = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
										->Get_Line(eLineID::AB)->Get_Type();
	m_rbLineType[eType].SetCheck(true);

	if (eType == eCellType::Connect)
	{
		Enable_LineOption_Connect(true);
		Update_LineLinkListBox(m_iPeekCellIdx, eLineID::AB);
	}
	else
	{
		m_lbLineLink.ResetContent();
		Enable_LineOption_Connect(false);
	}
}


void CNaviModifyTab::OnBnClicked_LineBC()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	ReSet_LineTypeBtn();
	eCellType::eCellType eType = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
												->Get_Line(eLineID::BC)->Get_Type();
	m_rbLineType[eType].SetCheck(true);

	if (eType == eCellType::Connect)
	{
		Enable_LineOption_Connect(true);
		Update_LineLinkListBox(m_iPeekCellIdx, eLineID::BC);
	}
	else
	{
		m_lbLineLink.ResetContent();
		Enable_LineOption_Connect(false);
	}
}


void CNaviModifyTab::OnBnClicked_Line_CA()
{
	if (m_iPeekCellIdx == NOT_FOUND)
		return;

	ReSet_LineTypeBtn();
	eCellType::eCellType eType = m_pNavMesh->m_pNaviCom->Get_vCell()[m_iPeekCellIdx]
											->Get_Line(eLineID::CA)->Get_Type();
	m_rbLineType[eType].SetCheck(true);

	if (eType == eCellType::Connect)
	{
		Enable_LineOption_Connect(true);
		Update_LineLinkListBox(m_iPeekCellIdx, eLineID::CA);
	}
	else
	{
		m_lbLineLink.ResetContent();
		Enable_LineOption_Connect(false);
	}
}
