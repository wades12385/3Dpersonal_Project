#include "stdafx.h"
#include "TileSetCtr.h"
#include "MainFrm.h"
#include "MFCToolView.h"

CTileSetCtr::CTileSetCtr()
	:m_iFirstIdx(0), m_iLastIdx(0), m_bIsDragPeek(FALSE)
	, m_fRatioX(0.f), m_fRatioY(0.f)
	, m_iDragCX(0), m_iDragCY(0)
	, m_byTileSetX(0),m_byTileSetY(0)

{

}

CTileSetCtr::~CTileSetCtr()
{
	Release_TileSetCtr();
}

void CTileSetCtr::PeekingDown(const _vec3 & vMouse)
{
	int idx = Get_TileIndex(vMouse);
	if (idx == -1)
		return;
	m_iFirstIdx = idx;
}

void CTileSetCtr::peekingUp(const _vec3 & vMouse)
{
	int idx = Get_TileIndex(vMouse);
	if (idx == -1)
		return;
	m_iLastIdx = idx;

	// Drag 계산 
	DragPeeking();
}

int CTileSetCtr::Get_TileIndex(const _vec3 & vPos) const
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return -1;
}

bool CTileSetCtr::IsPicking(const _vec3 & vPos, const int & iIndex) const
{
	float fCX =(TILECX*m_fRatioX) * (m_vecTile[iIndex]->vSize.x);
	float fCY =(TILECY*m_fRatioY) * (m_vecTile[iIndex]->vSize.y);
	float fX = m_vecTile[iIndex]->vPos.x * m_fRatioX;
	float fY = m_vecTile[iIndex]->vPos.y * m_fRatioY;

	if ((fX < vPos.x) && (fY < vPos.y)
		&& (fX + fCX) >= vPos.x  && (fY + fCY) >= vPos.y)
		return true;
	return false;
}

void CTileSetCtr::DragPeeking()
{
	ClearDragTile();
	//SingPeeking
	if (m_iFirstIdx == m_iLastIdx)
	{
		m_bIsDragPeek = FALSE;
		CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
		CMFCToolView* pView = (CMFCToolView*)pMain->m_tMainSplitter.GetPane(0, 1);
		//타일셋이미지의 타일 갯수를 
		pView->Set_ChangeSingleInfo(m_wstrTerrainObjKey, m_iFirstIdx, m_byTileSetX, m_byTileSetY);
		return;
	}

	//DragPeeking
	m_bIsDragPeek = TRUE;
	int FirstIdxY = m_iFirstIdx / TILESET_X;
	int LastIdxY = m_iLastIdx / TILESET_X;
	m_iDragCY = LastIdxY - FirstIdxY; 

	if (m_iDragCY < 0)
	{
		ERR_MSG(L"Error size");
		return;
	}
	m_iDragCX = (m_iLastIdx-(m_iDragCY*TILESET_X))-m_iFirstIdx;

	if (m_iDragCX < 0)
	{
		ERR_MSG(L"Error size");
		return;
	}
	InsertDragIdx();
}

HRESULT CTileSetCtr::Ready_TileSetCtr(const wstring& wstrTerrainObjKey,
	const BYTE& byTileSetX, const BYTE& byTileSetY,  const CSize& cSize)
{
	m_wstrTerrainObjKey = wstrTerrainObjKey;

	//백터 생성을 위해 텍스쳐에 들어간 텍스쳐 수가 필요함 

	TILE* pTile = nullptr;
	//타일셋창의 크기를 받아와서 비율 저장 
	m_fRatioX = float(cSize.cx) / WINCX;
	m_fRatioY = float(cSize.cy) / WINCY;
	m_byTileSetX = byTileSetX;
	m_byTileSetY = byTileSetY;
	float fX = 0.f;
	float fY = 0.f;
	
	//타일셋 이미지의 크기가 하나로 통일되니 갯수를 그냥 고정값으로 
	for (int i = 0; i < TILESET_MAXCNT ; ++i)
	{
		pTile = new TILE;
		pTile->bIsEntity = TRUE;
		pTile->byDrawID = i;
		pTile->byType = 0;
		pTile->wstrTileObjKey = wstrTerrainObjKey;
		fX = float(TILECX)	* (i % TILESET_X);
		fY = float(TILECY)	* (i / TILESET_X);
		pTile->vSize = {1.f, 1.f, 0.f };
		pTile->vPos = { fX * pTile->vSize.x, fY * pTile->vSize.y, 0.f };
		m_vecTile.emplace_back(pTile);
	}
	return S_OK;
}

void CTileSetCtr::ClearDragTile()
{
	m_vecDragIdx.clear();
	m_vecDragIdx.shrink_to_fit();
}

void CTileSetCtr::InsertDragIdx()
{
	int idx = -1;

	for (int j = 0; j < m_iDragCY +1; ++j)
	{
		for (int i = 0; i < m_iDragCX + 1; ++i)
		{
			idx = (m_iFirstIdx +  ( TILESET_X * j ) ) + i;
			m_vecDragIdx.emplace_back(idx);
		}
	}
	//DrageIdx 
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMFCToolView* pView = (CMFCToolView*)pMain->m_tMainSplitter.GetPane(0, 1);
	pView->Set_ChangeDragInfo(m_wstrTerrainObjKey, m_vecDragIdx, m_byTileSetX, m_byTileSetY,m_iDragCX, m_iDragCY);
}

void CTileSetCtr::Render_TileSetCtr()
{

	_matrix matScale, matTrans, matWrold;

	DWORD dwSize = m_vecTile.size();

		for (size_t i = 0; i < dwSize; ++i)
		{
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()-> Get_TexInfo(m_wstrTerrainObjKey);
			assert(!(nullptr == pTexInfo));

			//size :: 1,1,1
			//pos :: ori
			D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[i]->vPos.x,
				m_vecTile[i]->vPos.y, 0.f);
			matWrold = matScale * matTrans;

			RECT rc = {};

			int TileID = m_vecTile[i]->byDrawID;
			rc.left   = (TileID % TILESET_X) * TILECX;
			rc.top    =  (TileID / TILESET_X) * TILECY;
			rc.right  =  rc.left + TILECX;
			rc.bottom =  rc.top + TILECY;


			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc,
				&_vec3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		for (size_t i = 0; i < dwSize; ++i)
			Render_TileLine(i);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	
}

void CTileSetCtr::Render_TileLine(int idx)
{
	_vec2 tileLine[5]=
	{
		{m_vecTile[idx]->vPos.x,m_vecTile[idx]->vPos.y},
		{m_vecTile[idx]->vPos.x + (TILECX * m_vecTile[idx]->vSize.x),m_vecTile[idx]->vPos.y},
		{m_vecTile[idx]->vPos.x + (TILECX * m_vecTile[idx]->vSize.x),m_vecTile[idx]->vPos.y + (TILECY * m_vecTile[idx]->vSize.y)},
		{m_vecTile[idx]->vPos.x,m_vecTile[idx]->vPos.y + (TILECY * m_vecTile[idx]->vSize.y)},
		{m_vecTile[idx]->vPos.x,m_vecTile[idx]->vPos.y}
	};
	CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(3.f);

	if (m_bIsDragPeek)
	{

	auto iter_find = find(m_vecDragIdx.begin(), m_vecDragIdx.end(), idx);
	if (iter_find == m_vecDragIdx.end())
		CGraphic_Device::Get_Instance()->Get_Line()->Draw(tileLine, 5, (D3DCOLOR_ARGB(255, 0, 255, 0)));
	else
		CGraphic_Device::Get_Instance()->Get_Line()->Draw(tileLine, 5, (D3DCOLOR_ARGB(255, 255, 0, 0)));
	}
	else
	{
		if (idx == m_iFirstIdx)
			CGraphic_Device::Get_Instance()->Get_Line()->Draw(tileLine, 5, (D3DCOLOR_ARGB(255, 255, 0, 0)));
		else
			CGraphic_Device::Get_Instance()->Get_Line()->Draw(tileLine, 5, (D3DCOLOR_ARGB(255, 0, 255, 0)));
	}

}

void CTileSetCtr::Release_TileSetCtr()
{

	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile);
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}
