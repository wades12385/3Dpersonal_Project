// ObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "StaticDeploymentTab.h"
#include "afxdialogex.h"
#include "Management.h"
#include <string>
USING(Engine)

// CObjectTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStaticDeploymentTab, CDialog)

void CStaticDeploymentTab::SetUp_DataTable()
{
	CString str; 

	auto bToW = [&](_bool bValue) {
		if (bValue)
			return L"TRUE";
		return L"FALSE";
	};

	for (_uint i = 0; i < m_pDataTable->size(); ++i)
	{
		str.Format(L"%d", (*m_pDataTable)[i].iItemID);
		m_lcStaticTable.InsertItem(i,str);
		m_lcStaticTable.SetItemText(i, eObjDataID::Tag,(*m_pDataTable)[i].wstrTag.c_str());
		
		str.Format(L"%.2f", (*m_pDataTable)[i].fSacle);
		m_lcStaticTable.SetItemText(i, eObjDataID::Scale, str);

		str.Format(L"%.2f", (*m_pDataTable)[i].fSize);
		m_lcStaticTable.SetItemText(i, eObjDataID::Size, str);
		
		str.Format(L"%.2f", (*m_pDataTable)[i].fWeight);
		m_lcStaticTable.SetItemText(i, eObjDataID::Weight,str);
		

		m_lcStaticTable.SetItemText(i, eObjDataID::Decoration, bToW((*m_pDataTable)[i].bDecoration));
		m_lcStaticTable.SetItemText(i, eObjDataID::Floating, bToW((*m_pDataTable)[i].bFloating));
		m_lcStaticTable.SetItemText(i, eObjDataID::Stationary, bToW((*m_pDataTable)[i].bStationary));
	}
}

void CStaticDeploymentTab::Update_ObjInfo(_int & iIdx)
{
	m_sObjTag.Format(L"%s", (*m_pDataTable)[iIdx].wstrTag.c_str());
	m_sScale.Format(L"%.2f", (*m_pDataTable)[iIdx].fSacle);
	m_sSize.Format(L"%.2f", (*m_pDataTable)[iIdx].fSize);
	m_sWeight.Format(L"%.2f", (*m_pDataTable)[iIdx].fWeight);

	m_cbDecoration.SetCheck((*m_pDataTable)[iIdx].bDecoration);
	m_cbFloating.SetCheck((*m_pDataTable)[iIdx].bFloating);
	m_cbStationary.SetCheck((*m_pDataTable)[iIdx].bStationary);
	UpdateData(FALSE);

}

void CStaticDeploymentTab::SetUp_Tool()
{
	m_pAxis = (CAxis*)CManagement::Get_Instance()->Get_GameObjet(L"Layer_Tool1");
	m_pSize = (CSizeCheck*)CManagement::Get_Instance()->Get_GameObjet(L"Layer_Tool2");


	m_sSizeCheck.Format(L"%f", m_pSize->m_fSize);
	UpdateData(FALSE);
}

void CStaticDeploymentTab::Peeking(const CPoint & vPos)
{
	_int type = NOT_FOUND;
	for (_int i = 0; i < eStaticItemPeek::End; ++i)
	{
		if (m_rbPeektype[i].GetCheck())
		{
			type = i;
			break;
		}
	}
	if (type == NOT_FOUND)
		return;


	switch (type)
	{
	case eStaticItemPeek::Create:
		Create_Obj(vPos);
		break;
	case eStaticItemPeek::Delete:
		break;
	case eStaticItemPeek::Modify:
		break;
	}


}

void CStaticDeploymentTab::Create_Obj(const CPoint & vPos)
{
	NULL_CHECK(m_pNavObj);
	if (m_iTableIdx == NOT_FOUND)
	{
		MSG_BOX(L"Not Select Table");
		return;
	}
	_int iCellIdx = NOT_FOUND;
	_vec3 vPeekPos = vZero;
	//if (m_rbCreateOption[eBoxType::Collision].GetCheck())
	//{
	//	pBox->Set_Type(eBoxType::Collision);
	//	CManagement::Get_Instance()->Add_InstantGameObject(pBox, L"Layer_ColBox");
	//	m_pColBoxList = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_ColBox");
	//}
	if (m_pNavObj->Cell_Peeking(_vec2((_float)vPos.x, (_float)vPos.y), iCellIdx, vPeekPos))
	{
		m_pObjItem = CMfcStaticItem::Create(CManagement::Get_Instance()->Get_Device(),m_iTableIdx);
		CManagement::Get_Instance()->Add_InstantGameObject(m_pObjItem, L"Layer_StaticItem");
		m_pObjItem->Set_Position(vPeekPos);
	}
}

void CStaticDeploymentTab::Delete_Obj(const CPoint & vPos)
{
}

void CStaticDeploymentTab::Modify_Obj(const CPoint & vPos)
{
}

void CStaticDeploymentTab::SetUp_Tranform()
{
	NULL_CHECK(m_pObjItem);

	m_sPos[eFloat3::X].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Position().x);
	m_sPos[eFloat3::Y].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Position().y);
	m_sPos[eFloat3::Z].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Position().z);

	m_sRot[eFloat3::X].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Rotate().x);
	m_sRot[eFloat3::Y].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Rotate().y);
	m_sRot[eFloat3::Z].Format(L"%.2f", m_pObjItem->Get_Transform()->Get_Rotate().z);


	UpdateData(FALSE);
}

CStaticDeploymentTab::CStaticDeploymentTab(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTAB, pParent)
	, m_sScale(_T(""))
	, m_sSize(_T(""))
	, m_sObjTag(_T(""))
	, m_sWeight(_T(""))
	, m_sSelectNaviID(_T(""))
	, m_sSelectNaviName(_T(""))
	, m_sPeekingItem(_T(""))
	, m_sSizeCheck(_T(""))

{
}

CStaticDeploymentTab::~CStaticDeploymentTab()
{
}

void CStaticDeploymentTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, m_lcStaticTable);
	DDX_Text(pDX, IDC_EDIT1, m_sScale);
	DDX_Text(pDX, IDC_EDIT12, m_sSize);
	DDX_Text(pDX, IDC_EDIT14, m_sObjTag);
	DDX_Text(pDX, IDC_EDIT32, m_sWeight);
	DDX_Control(pDX, IDC_CHECK9, m_cbFloating);
	DDX_Control(pDX, IDC_CHECK1, m_cbDecoration);
	DDX_Control(pDX, IDC_CHECK10, m_cbStationary);
	DDX_Control(pDX, IDC_LIST2, m_lbNaviMeshs);
	DDX_Text(pDX, IDC_EDIT11, m_sSelectNaviID);
	DDX_Text(pDX, IDC_EDIT31, m_sSelectNaviName);
	DDX_Control(pDX, IDC_RADIO1, m_rbPeektype[eStaticItemPeek::Create]);
	DDX_Control(pDX, IDC_RADIO2, m_rbPeektype[eStaticItemPeek::Delete]);
	DDX_Control(pDX, IDC_RADIO3, m_rbPeektype[eStaticItemPeek::Modify]);
	DDX_Control(pDX, IDC_RADIO4, m_rbPeektype[eStaticItemPeek::None]);

	DDX_Text(pDX, IDC_EDIT15, m_sPeekingItem);
	DDX_Text(pDX, IDC_EDIT13, m_sSizeCheck);
	DDX_Text(pDX, IDC_EDIT28, m_sPos[eFloat3::X]);
	DDX_Text(pDX, IDC_EDIT29, m_sPos[eFloat3::Y]);
	DDX_Text(pDX, IDC_EDIT30, m_sPos[eFloat3::Z]);
	DDX_Control(pDX, IDC_EDIT1, m_edScale);
	DDX_Control(pDX, IDC_EDIT13, m_edSizeCheck);
	DDX_Control(pDX, IDC_EDIT28, m_edPos[eFloat3::X]);
	DDX_Control(pDX, IDC_EDIT29, m_edPos[eFloat3::Y]);
	DDX_Control(pDX, IDC_EDIT30, m_edPos[eFloat3::Z]);

	DDX_Control(pDX, IDC_EDIT25, m_edRot[eFloat3::X]);
	DDX_Control(pDX, IDC_EDIT26, m_edRot[eFloat3::Y]);
	DDX_Control(pDX, IDC_EDIT27, m_edRot[eFloat3::Z]);

	DDX_Text(pDX, IDC_EDIT28, m_sRot[eFloat3::X]);
	DDX_Text(pDX, IDC_EDIT29, m_sRot[eFloat3::Y]);
	DDX_Text(pDX, IDC_EDIT30, m_sRot[eFloat3::Z]);

}


BEGIN_MESSAGE_MAP(CStaticDeploymentTab, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST2, &CStaticDeploymentTab::OnLbnSelchange_NaviMesh)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, &CStaticDeploymentTab::OnNMClickList_Table)
	ON_BN_CLICKED(IDC_BUTTON1, &CStaticDeploymentTab::OnBnClicked_TableApply)
	ON_BN_CLICKED(IDC_BUTTON2, &CStaticDeploymentTab::OnBnClicked_NaviLoad)
	ON_EN_CHANGE(IDC_EDIT1, &CStaticDeploymentTab::OnEnChange_Sacle)
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CStaticDeploymentTab::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON6, &CStaticDeploymentTab::OnBnClicked_SizeCheck)
	ON_EN_CHANGE(IDC_EDIT13, &CStaticDeploymentTab::OnEnChange_SizeText)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN17, &CStaticDeploymentTab::OnDeltaposSpin_SizeCheck)
END_MESSAGE_MAP()


// CObjectTab 메시지 처리기입니다.


BOOL CStaticDeploymentTab::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_lcStaticTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lcStaticTable.InsertColumn(0, L"ID", LVCFMT_CENTER, 30);
	m_lcStaticTable.InsertColumn(1, L"Tag", LVCFMT_CENTER, 60);
	m_lcStaticTable.InsertColumn(2, L"Scale", LVCFMT_CENTER, 55);
	m_lcStaticTable.InsertColumn(3, L"Size", LVCFMT_CENTER, 50);
	m_lcStaticTable.InsertColumn(4, L"Weght", LVCFMT_CENTER, 50);
	m_lcStaticTable.InsertColumn(5, L"Deco", LVCFMT_CENTER, 50);
	m_lcStaticTable.InsertColumn(6, L"Floating", LVCFMT_CENTER, 60);
	m_lcStaticTable.InsertColumn(7, L"Stationary", LVCFMT_CENTER, 80);

	m_iTableIdx = NOT_FOUND;
	m_iSelectNaviIdx = NOT_FOUND;
	m_rbPeektype[eStaticItemPeek::None].SetCheck(TRUE);

	CManagement::Get_Instance()->Load_DataTable(L"../Data/DataTable.tsv");
	m_pDataTable = CManagement::Get_Instance()->Get_DataTableVector();
	SetUp_DataTable();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void CStaticDeploymentTab::OnLbnSelchange_NaviMesh()
{
	NULL_CHECK(m_pListNavMeshObj);

	_int SelectIdx = m_lbNaviMeshs.GetCurSel();
	_int iIdx = 0;
	CString str;
	for (auto& pNavi : *m_pListNavMeshObj)
	{
		if (SelectIdx == iIdx)
		{
			m_pNavObj = (CNaviObj*)pNavi;
			m_sSelectNaviID.Format(L"%d", m_pNavObj->m_pNaviCom->Get_NaviID());
			m_lbNaviMeshs.GetText(SelectIdx, m_sSelectNaviName);
			UpdateData(FALSE);
			break;
		}
	}

}

void CStaticDeploymentTab::OnNMClickList_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_iTableIdx = pNMItemActivate->iItem;
	Update_ObjInfo(m_iTableIdx);
	*pResult = 0;
}


void CStaticDeploymentTab::OnBnClicked_TableApply()
{
	if (m_iTableIdx == NOT_FOUND)
		return;
	CString str;
	auto bToW = [&](_bool bValue) {
		if (bValue)
			return L"TRUE";
		return L"FALSE";
	};
	UpdateData(TRUE);
	(*m_pDataTable)[m_iTableIdx].fSacle = (_float)_ttof(m_sScale);
	(*m_pDataTable)[m_iTableIdx].fSize = (_float)_ttof(m_sSize);
	(*m_pDataTable)[m_iTableIdx].fWeight = (_float)_ttof(m_sWeight);
	(*m_pDataTable)[m_iTableIdx].bDecoration = BOOLTobool(m_cbDecoration.GetCheck());
	(*m_pDataTable)[m_iTableIdx].bFloating = BOOLTobool(m_cbFloating.GetCheck());
	(*m_pDataTable)[m_iTableIdx].bStationary = BOOLTobool(m_cbStationary.GetCheck());

	str.Format(L"%.2f", (*m_pDataTable)[m_iTableIdx].fSacle);
	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Scale, str);
	 
	str.Format(L"%.2f", (*m_pDataTable)[m_iTableIdx].fSize);
	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Size, str);

	str.Format(L"%.2f", (*m_pDataTable)[m_iTableIdx].fWeight);
	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Weight, str);

	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Decoration, bToW((*m_pDataTable)[m_iTableIdx].bDecoration));
	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Floating, bToW((*m_pDataTable)[m_iTableIdx].bFloating));
	m_lcStaticTable.SetItemText(m_iTableIdx, eObjDataID::Stationary, bToW((*m_pDataTable)[m_iTableIdx].bStationary));

	CManagement::Get_Instance()->Save_DataTable(L"../Data/DataTable.tsv");

}


void CStaticDeploymentTab::OnBnClicked_NaviLoad()
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
		CNaviMesh* pNaviMeshCom = CNaviMesh::Load(CManagement::Get_Instance()->Get_Device(), Dlg.GetPathName(), true);
		pMesh->Set_Navi(pNaviMeshCom);

		CManagement::Get_Instance()->Add_InstantGameObject(pMesh, L"Layer_NaviMesh");
		m_pListNavMeshObj = CManagement::Get_Instance()->Get_GameObjetList(L"Layer_NaviMesh");

		m_lbNaviMeshs.AddString(strFileName);
	}

}




void CStaticDeploymentTab::OnEnChange_Sacle()
{
	NULL_CHECK(m_pObjItem);
	UpdateData(TRUE);


	_float fScale = (_float)_ttof(m_sScale);
	m_pObjItem->Set_Sacle(fScale);

}

BOOL CStaticDeploymentTab::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	NULL_CHECK(m_pObjItem);
	NULL_CHECK(m_pSize);
	UpdateData(TRUE);
	_float fDelta = 0.05f;
	_float fValue;

	RECT tScaleRect , tSizeRect;
	RECT tPosX, tPosY, tPosZ;
	RECT tRotX, tRotY, tRotZ;


	m_edScale.GetWindowRect(&tScaleRect);
	m_edSizeCheck.GetWindowRect(&tSizeRect);
	
	m_edPos[eFloat3::X].GetWindowRect(&tPosX);
	m_edPos[eFloat3::Y].GetWindowRect(&tPosY);
	m_edPos[eFloat3::Z].GetWindowRect(&tPosZ);

	m_edRot[eFloat3::X].GetWindowRect(&tRotX);
	m_edRot[eFloat3::Y].GetWindowRect(&tRotY);
	m_edRot[eFloat3::Z].GetWindowRect(&tRotZ);

	if (PtInRect(&tScaleRect, pt))
	{
		fValue = (_float)_ttof(m_sScale);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		m_sScale.Format(L"%.2f", fValue);
		m_pObjItem->Set_Sacle(fValue);
	}
	else if (PtInRect(&tSizeRect, pt))
	{
		fValue = (_float)_ttof(m_sSizeCheck);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		m_sSizeCheck.Format(L"%.2f", fValue);
		m_pSize->Set_ColliderSize(fValue);
	}
	else if (PtInRect(&tPosX, pt))
	{
		fValue = (_float)_ttof(m_sPos[eFloat3::X]);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vPos = m_pObjItem->Get_Transform()->Get_Position();
		vPos.x = fValue;
		m_pObjItem->Get_Transform()->Set_Position(vPos);
	}
	else if (PtInRect(&tPosY, pt))
	{
		fValue = (_float)_ttof(m_sPos[eFloat3::Y]);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vPos = m_pObjItem->Get_Transform()->Get_Position();
		vPos.y = fValue;
		m_pObjItem->Get_Transform()->Set_Position(vPos);
	}
	else if (PtInRect(&tPosZ, pt))
	{
		fValue = (_float)_ttof(m_sPos[eFloat3::Z]);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vPos = m_pObjItem->Get_Transform()->Get_Position();
		vPos.z = fValue;
		m_pObjItem->Get_Transform()->Set_Position(vPos);
	}
	else if (PtInRect(&tRotX, pt))
	{
		fValue = (_float)_ttof(m_sRot[eFloat3::X]);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vRot = m_pObjItem->Get_Transform()->Get_Rotate();
		vRot.x = fValue;
		m_pObjItem->Get_Transform()->Set_Rotate(vRot);
	}
	else if (PtInRect(&tRotY, pt))
	{
		fValue = (_float)_ttof(m_sRot[eFloat3::Y]);
		fDelta = 1.f;
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vRot = m_pObjItem->Get_Transform()->Get_Rotate();
		vRot.y = fValue;
		m_pObjItem->Get_Transform()->Set_Rotate(vRot);
	}
	else if (PtInRect(&tRotZ, pt))
	{
		fValue = (_float)_ttof(m_sRot[eFloat3::Z]);
		if (zDelta < 0)
			fValue -= fDelta;
		else
			fValue += fDelta;

		_vec3 vRot = m_pObjItem->Get_Transform()->Get_Rotate();
		vRot.z = fValue;
		m_pObjItem->Get_Transform()->Set_Rotate(vRot);
	}

	UpdateData(FALSE);
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void CStaticDeploymentTab::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	NULL_CHECK(m_pObjItem);

	UpdateData(TRUE);
	_float fScale = (_float)_ttof(m_sScale);
	_float fDelta = 0.1f;
	fScale -= pNMUpDown->iDelta * fDelta;
	m_sScale.Format(L"%.2f", fScale);
	m_pObjItem->Set_Sacle(fScale);
	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CStaticDeploymentTab::OnBnClicked_SizeCheck()
{
	NULL_CHECK(m_pObjItem);
	NULL_CHECK(m_pSize);
	NULL_CHECK(m_pAxis);
	m_pSize->m_pTrans->Set_Position(
		static_cast<CTransform*>(m_pObjItem->Get_Component(eComponentID::Transform))->Get_Position());
	m_pSize->m_pTrans->Update_Component();
	m_pAxis->m_vPosition = static_cast<CTransform*>(m_pObjItem->Get_Component(eComponentID::Transform))->Get_Position();
}

void CStaticDeploymentTab::OnEnChange_SizeText()
{
	NULL_CHECK(m_pSize);
	UpdateData(TRUE);

	_float fScale = (_float)_ttof(m_sSizeCheck);
	m_pSize->Set_ColliderSize(fScale);

}


void CStaticDeploymentTab::OnDeltaposSpin_SizeCheck(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	NULL_CHECK(m_pSize);

	UpdateData(TRUE);
	_float fScale = (_float)_ttof(m_sSizeCheck);
	_float fDelta = 0.1f;
	fScale -= pNMUpDown->iDelta * fDelta;
	m_sSizeCheck.Format(L"%.2f", fScale);
	m_pSize->Set_ColliderSize(fScale);
	UpdateData(FALSE);

	*pResult = 0;
}
