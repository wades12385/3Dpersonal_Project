// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
//
#include "MainFrm.h"
#include "MFCToolView.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_iAtkEdit(0)
	, m_iDefEdit(0)
{

}

CUnitTool::~CUnitTool()
{
	for (auto& rPair : m_mapUnitInfo)
		Safe_Delete(rPair.second);
	m_mapUnitInfo.clear(); 

	for (auto& pUnit : m_listUnitPlaced)
		Safe_Delete(pUnit);
	m_listUnitPlaced.clear();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBoxMob);
	DDX_Control(pDX, IDC_LIST1, m_ListBoxAdded);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_PIC_UNIT, m_PicUnit);
	DDX_Text(pDX, IDC_EDIT1, m_iAtkEdit);
	DDX_Text(pDX, IDC_EDIT2, m_iDefEdit);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_RADIO1, &CUnitTool::OnBnClickedRadioNPC)
	ON_BN_CLICKED(IDC_RADIO2, &CUnitTool::OnBnClickedRadioMonster)
	ON_BN_CLICKED(IDC_RADIO3, &CUnitTool::OnBnClickedRadioBoss)
	ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnLbnSelchangeMob)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangePlace)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Radio[0].SetCheck(TRUE);

	InitMapUnit();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUnitTool::OnBnClickedRadioNPC()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_ListBoxMob.ResetContent();

	for (auto& rPair : m_mapUnitInfo)
	{
		if (rPair.second->byJob == 0)
		{
			m_ListBoxMob.AddString(rPair.second->wstrName);
		}
	}

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedRadioMonster()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_ListBoxMob.ResetContent();

	for (auto& rPair : m_mapUnitInfo)
	{
		if (rPair.second->byJob == 1)
		{
			m_ListBoxMob.AddString(rPair.second->wstrName);
		}
	}
}


void CUnitTool::OnBnClickedRadioBoss()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_ListBoxMob.ResetContent();

	for (auto& rPair : m_mapUnitInfo)
	{
		if (rPair.second->byJob == 2)
		{
			m_ListBoxMob.AddString(rPair.second->wstrName);
		}
	}
}


void CUnitTool::OnBnClickedAddButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 

	int iIndex = m_ListBoxMob.GetCurSel();
	if (LB_ERR == iIndex)
		return;
	CString wstrFindName = L"";
	m_ListBoxMob.GetText(iIndex, wstrFindName);

	auto& iter_find = m_mapUnitInfo.find(wstrFindName);
	if (m_mapUnitInfo.end() == iter_find)
		return; 

	m_listUnitPlaced.emplace_back(new UNITINFO(*(*iter_find).second));
	m_ListBoxAdded.AddString(wstrFindName);

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMFCToolView* pView = (CMFCToolView*)pMain->m_tMainSplitter.GetPane(0, 1);
	pView->ReNewScreen();
	
	UpdateData(FALSE); 
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_ListBoxAdded.GetCurSel();
	if (LB_ERR == iIndex)
		return;
	CString wstrFindName = L"";
	m_ListBoxAdded.GetText(iIndex, wstrFindName);

	for (auto& it = m_listUnitPlaced.begin(); it != m_listUnitPlaced.end(); ++it)
	{
		if ((*it)->wstrName == wstrFindName)
		{
			Safe_Delete(*it);
			m_listUnitPlaced.erase(it);
			m_ListBoxAdded.DeleteString(iIndex);
			break;
		}
	}

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMFCToolView* pView = (CMFCToolView*)pMain->m_tMainSplitter.GetPane(0, 1);
	pView->ReNewScreen();

	UpdateData(FALSE);
}

void CUnitTool::OnLbnSelchangeMob()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_ListBoxMob.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	CString strFindName = L"";
	m_ListBoxMob.GetText(iIndex, strFindName);

	auto& iter_find = m_mapUnitInfo.find(strFindName);
	if (m_mapUnitInfo.end() == iter_find)
		return;
	
	m_iAtkEdit = (*iter_find).second->iAtt;
	m_iDefEdit = (*iter_find).second->iDef;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(strFindName.GetString());
	if (nullptr == pTexInfo)
		return;

	CGraphic_Device::Get_Instance()->Render_Begin();

	D3DXMATRIX matSacle, matTrans, matWorld;
	D3DXMatrixTranslation(&matTrans, float(WINCX >> 1), float(WINCY >> 1), 0.f);
	float fSizeX = WINCX / float(pTexInfo->tImageInfo.Width);
	float fSizeY = WINCY / float(pTexInfo->tImageInfo.Height);
	D3DXMatrixScaling(&matSacle, fSizeX, fSizeY, 0.f);
	matWorld = matSacle * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End(m_PicUnit.GetSafeHwnd());

	UpdateData(FALSE);
}


void CUnitTool::OnLbnSelchangePlace()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE);

	//int iIndex = m_ListBoxAdded.GetCurSel();
	//if (LB_ERR == iIndex)
	//	return;

	//UpdateData(FALSE);
}

void CUnitTool::ChangePickedObjPos(const _vec3& _vPos)
{
	UpdateData(TRUE);

	int iIndex = m_ListBoxAdded.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	auto& iter_find = m_listUnitPlaced.begin();
	for (int i = 0; i < iIndex; ++i)
		++iter_find;

	(*iter_find)->vPos = _vPos;

	UpdateData(FALSE);
}

void CUnitTool::InitMapUnit()
{
	UNITINFO* pUnit = new UNITINFO;
	pUnit->wstrName = L"NPC1";
	pUnit->iAtt = 0;
	pUnit->iDef = 0;
	pUnit->byJob = 0;	// NPC
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);
	m_ListBoxMob.AddString(pUnit->wstrName);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"NPC2";
	pUnit->iAtt = 0;
	pUnit->iDef = 0;
	pUnit->byJob = 0;	// NPC
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);
	m_ListBoxMob.AddString(pUnit->wstrName);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"NPC3";
	pUnit->iAtt = 0;
	pUnit->iDef = 0;
	pUnit->byJob = 0;	// NPC
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);
	m_ListBoxMob.AddString(pUnit->wstrName);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"MONSTER1";
	pUnit->iAtt = 1;
	pUnit->iDef = 1;
	pUnit->byJob = 1;	// Monster
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"MONSTER2";
	pUnit->iAtt = 10;
	pUnit->iDef = 10;
	pUnit->byJob = 1;	// Monster
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"MONSTER3";
	pUnit->iAtt = 100;
	pUnit->iDef = 100;
	pUnit->byJob = 1;	// Monster
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"BOSS1";
	pUnit->iAtt = 300;
	pUnit->iDef = 300;
	pUnit->byJob = 2;	// Boss
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"BOSS2";
	pUnit->iAtt = 3000;
	pUnit->iDef = 3000;
	pUnit->byJob = 2;	// Boss
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);

	pUnit = new UNITINFO;
	pUnit->wstrName = L"BOSS3";
	pUnit->iAtt = 9999;
	pUnit->iDef = 9999;
	pUnit->byJob = 2;	// Boss
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit);
}
