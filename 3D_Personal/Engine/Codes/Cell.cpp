#include "Cell.h"
#include "NaviMesh.h"
USING(Engine)

Engine::CCell::CCell(LPDIRECT3DDEVICE9 pDevice)
	:CVIBuffer(pDevice)
	, m_pDXLine(nullptr)
	, m_bModified(false)
	, m_pVerTexes(nullptr)
	, m_iCellIdx(0)
	, m_eType(eCellType::Base)
	, m_bSelect(false)
	, m_vCurColor(VCOLOR_GRAY)
	, m_vBaseColor(VCOLOR_GRAY)
	, m_bOnLineTrigger(false)
	, m_bToolMode(false)
{
	m_pDevice->AddRef();
	ZeroMemory(&m_tVTXIndex, sizeof(CELLVTXIDX));
	ZeroMemory(m_pNeighbor, sizeof(CCell*) * eNeighbor::End);
	ZeroMemory(m_pLine, sizeof(CLine*) * eLineID::End);
}



HRESULT CCell::Ready_Component()
{
	m_iVertexCount = 3;
	m_iTriCount = 1;
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iIdxSize = sizeof(INDEX16);
	m_dwFVF = FVF_VTX_COLOR;
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::Ready_Component());

	VTX_COLOR*		pVtxCol = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPosition = (*m_pVerTexes)[m_tVTXIndex._A];
	pVtxCol[0].dwColor = VecToColor_XRGB(m_vCurColor);

	pVtxCol[1].vPosition = (*m_pVerTexes)[m_tVTXIndex._B];
	pVtxCol[1].dwColor = VecToColor_XRGB(m_vCurColor);

	pVtxCol[2].vPosition = (*m_pVerTexes)[m_tVTXIndex._C];
	pVtxCol[2].dwColor = VecToColor_XRGB(m_vCurColor);

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();

	return S_OK;
}




HRESULT CCell::Ready_Cell(const _ulong & dwCellIndex, const CELLVTXIDX & Index, 
	vector<_vec3>* pVertexs, _vec3 vColor , vector<CNaviMesh*>* pNaviMeshs , _bool bToolMod)
{
	m_pVerTexes = pVertexs;
	m_iCellIdx = dwCellIndex;
	m_vBaseColor = vColor;
	m_vCurColor = vColor;
	m_tVTXIndex = Index;
	m_tVTXIndex._A -= 1;
	m_tVTXIndex._B -= 1;
	m_tVTXIndex._C -= 1;
	m_pNavMeshs = pNaviMeshs;
	m_bToolMode = bToolMod;
	//Buffer
	FAILED_CHECK(Ready_Component());

	m_pLine[eLineID::AB] = CLine::Create(&_vec2((*m_pVerTexes)[m_tVTXIndex._A].x , (*m_pVerTexes)[m_tVTXIndex._A].z) 
										, &_vec2((*m_pVerTexes)[m_tVTXIndex._B].x , (*m_pVerTexes)[m_tVTXIndex._B].z) ) ;

	m_pLine[eLineID::BC] = CLine::Create(&_vec2((*m_pVerTexes)[m_tVTXIndex._B].x, (*m_pVerTexes)[m_tVTXIndex._B].z)
		, &_vec2((*m_pVerTexes)[m_tVTXIndex._C].x, (*m_pVerTexes)[m_tVTXIndex._C].z));

	m_pLine[eLineID::CA] = CLine::Create(&_vec2((*m_pVerTexes)[m_tVTXIndex._C].x, (*m_pVerTexes)[m_tVTXIndex._C].z)
		, &_vec2((*m_pVerTexes)[m_tVTXIndex._A].x, (*m_pVerTexes)[m_tVTXIndex._A].z));

#ifdef _DEBUG
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pDXLine)))
		return E_FAIL;
#endif
	return S_OK;
}

_bool Engine::CCell::Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell)
{

	if (*pPointFirst == (*m_pVerTexes)[m_tVTXIndex._A])
	{
		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._B])
		{
			m_pNeighbor[eNeighbor::AB] = pCell;
			return true;
		}

		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._C])
		{
			m_pNeighbor[eNeighbor::CA] = pCell;
			return true;
		}
	}

	if (*pPointFirst == (*m_pVerTexes)[m_tVTXIndex._B])
	{
		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._A])
		{
			m_pNeighbor[eNeighbor::AB] = pCell;
			return true;
		}

		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._C])
		{
			m_pNeighbor[eNeighbor::BC] = pCell;
			return true;
		}
	}

	if (*pPointFirst == (*m_pVerTexes)[m_tVTXIndex._C])
	{
		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._B])
		{
			m_pNeighbor[eNeighbor::BC] = pCell;
			return true;
		}

		if (*pPointSecond == (*m_pVerTexes)[m_tVTXIndex._A])
		{
			m_pNeighbor[eNeighbor::CA] = pCell;
			return true;
		}
	}

	return false;
}
void Engine::CCell::Render_Cell(void)
{
	//Buffer 먼저 그리고 
	CVIBuffer::Render_VIBuffer();

	//Line Render
	_vec3		vPoint[4];
	vPoint[0] = (*m_pVerTexes)[m_tVTXIndex._A];
	vPoint[1] =(*m_pVerTexes)[m_tVTXIndex._B];
	vPoint[2] =(*m_pVerTexes)[m_tVTXIndex._C];
	vPoint[3] = (*m_pVerTexes)[m_tVTXIndex._A];

	_matrix		matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	for (_ulong i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matView);
		if (vPoint[i].z <= 0.1f)
			vPoint[i].z = 0.1f;

		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matProj);
	}

	if (m_bOnLineTrigger)
		m_pDXLine->SetWidth(5.5f);
	else
		m_pDXLine->SetWidth(1.5f);

	m_pDevice->EndScene();
	m_pDevice->BeginScene();

	m_pDXLine->Begin();

	_matrix matTemp;
	if (m_bToolMode)
	{

		if (m_bSelect)
		{
			if (m_bOnLineTrigger == false)
			{
				m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), COLOR_RED);
			}
			else
			{
				for (int i = 0; i < eLineID::End; ++i)
				{
					if (m_pLine[i]->Get_Type() != eCellType::Base)
						m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), VecToColor_XRGB(m_pLine[i]->Get_Color()));
					else
						m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), COLOR_RED);
				}
			}
		}
		else
		{
			m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), COLOR_LIGHTGRAY);
		}
	}
	else
	{
		if (m_bOnLineTrigger == false)
		{
			m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), COLOR_RED);
		}
		else
		{
			for (int i = 0; i < eLineID::End; ++i)
			{
				if (m_pLine[i]->Get_Type() != eCellType::Base)
					m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), VecToColor_XRGB(m_pLine[i]->Get_Color()));
				else
					m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), COLOR_RED);
			}
		}
	}

	
	m_pDXLine->End();
}

eCompare::eCompare CCell::Compare(const _vec3* pEndPos, _int& iNavID, _int& iCellIndex)
{
	/*
	해당 라인 속성 체크 후 
	리브면 플레이어 리브상태로 변경 
	커넥트면 내비 메쉬 아이디 변경 셀인덱스 변경 out인자로 오브젝트 네비매쉬 끌고와서 변경 해주면 될듯 

	만약 
	라인이 기본타입이고 셀이 커넥트일경우 
	기본적으로 스탑무브 처리는 해주고 추가적으로 연결된 다른 네비의 셀인 아웃 처리 해야함 

	inside 일경우 id변경 

	*/
	//커넥트 셀일경우 연결된 셀 충돌 검사
	if (m_eType == eCellType::Connect)
	{
		if (m_pNavMeshs == nullptr)
		{
			MSG_BOX(L"m_pNavMeshs is Null");
			return eCompare::Stop;
		}
		for (auto& Link : m_vecLinkCells)
		{
			if ((*m_pNavMeshs)[Link.iNaviID]->Get_vCell()[Link.iCellIdx]->IsInside(*pEndPos))
			{
				iNavID = Link.iNaviID;
				iCellIndex = Link.iCellIdx;
				return eCompare::Move;
			}
		}
	}
	// type base and line is connect 
	for (_ulong i = 0; i < eLineID::End; ++i)
	{
		if (eRelationLine::OutLine == m_pLine[i]->Compare(&_vec2(pEndPos->x, pEndPos->z)))
		{
			//라인 타입에 따라 분기 
			switch (m_pLine[i]->Get_Type())
			{
			case Engine::eCellType::Base:
				if (nullptr == m_pNeighbor[i])
					return eCompare::Stop;
				else
				{
					iCellIndex = m_pNeighbor[i]->Get_CellIndex();
					return eCompare::Move;
				}
				break;
			case Engine::eCellType::Leave:
				return eCompare::Leave;
			case Engine::eCellType::Connect:
				for (auto& Link : m_pLine[i]->Get_LinkCells())
				{
					if ((*m_pNavMeshs)[Link.iNaviID]->Get_vCell()[Link.iCellIdx]->IsInside(*pEndPos))
					{
						iNavID = Link.iNaviID;
						iCellIndex = Link.iCellIdx;
						return eCompare::Move;
					}
				}
				return eCompare::Stop;
				break;
			}
		}
	}

	return eCompare::Move;
}

void CCell::Modifying_Buffer()
{

	VTX_COLOR*		pVtxCol = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);
	pVtxCol[0].vPosition = (*m_pVerTexes)[m_tVTXIndex._A];
	pVtxCol[0].dwColor = VecToColor_XRGB(m_vCurColor);

	pVtxCol[1].vPosition = (*m_pVerTexes)[m_tVTXIndex._B];
	pVtxCol[1].dwColor = VecToColor_XRGB(m_vCurColor);

	pVtxCol[2].vPosition = (*m_pVerTexes)[m_tVTXIndex._C];
	pVtxCol[2].dwColor = VecToColor_XRGB(m_vCurColor);
	  
	m_pVB->Unlock();
}

_bool CCell::IsInside(const _vec3 vPos)
{
	for (int i = 0; i < eLineID::End; ++i)
	{
		if (eRelationLine::OutLine == m_pLine[i]->Compare(&_vec2(vPos.x, vPos.z)))
			return false;
	}

	return true;
}

const _vec3 * CCell::Get_Point(const eCellpt::eCellpt& point)
{
	switch (point)
	{
	case eCellpt::A:
		return &(*m_pVerTexes)[m_tVTXIndex._A];
	case eCellpt::B:
		return &(*m_pVerTexes)[m_tVTXIndex._B];
	case eCellpt::C:
		return &(*m_pVerTexes)[m_tVTXIndex._C];
	}
	return nullptr;
}



//셀의 타입이랑 해당 색깔도 같이 적용 그리고 버퍼 업데이트 콜
void CCell::Set_CellType(eCellType::eCellType iType)
{
	//if (m_eType == iType) 컬러바꿀때 걸림 
	//	return;
	 m_eType = iType; 

	 switch (m_eType)
	 {
	 case Engine::eCellType::Base:
		 m_vCurColor = m_vBaseColor;
		 m_vecLinkCells.clear();
		 m_vecLinkCells.shrink_to_fit();
		 break;
	 case Engine::eCellType::Connect:
		 m_vCurColor = VCOLOR_YELLOW;
		 // 라인 트리거 다 초기화 
		 m_bOnLineTrigger = false;
		 for (int i = 0; i < eLineID::End; ++i)
			 m_pLine[i]->Set_Type(eCellType::Base);
		 break;
	 }
	 Modifying_Buffer();
}

void CCell::Set_LineTrigger(const eLineID::eLineID & eID, const eCellType::eCellType & eType)
{
	//베이스가 아닌 옵션이 적용할 겅우에만 onlineOption 트루로 
	if (eType == eCellType::Base)
	{
		m_pLine[eID]->Set_Type(eType);
		m_bOnLineTrigger = false;
		for (int i = 0; i < eLineID::End; ++i)
		{
			if (m_pLine[i]->Get_Type() != eCellType::Base)
				m_bOnLineTrigger = true;
		}
	}
	else
	{
		m_bOnLineTrigger = true;
		m_pLine[eID]->Set_Type(eType);
	}
}

void CCell::Add_LinkCell(const LINKCELL& tLinkCell)
{
	if (m_eType == eCellType::Base)
	{
		MSG_BOX(L"Is't Connect type");
		return;
	}

	m_vecLinkCells.emplace_back(tLinkCell);

	if (m_bOnLineTrigger)
	{
		m_bOnLineTrigger = false;
		for (int i = 0; i < eLineID::End; ++i)
			m_pLine[i]->Set_Type(eCellType::Base);
	}
}

HRESULT CCell::Check_Data()
{
	if (m_eType == eCellType::Connect && m_bOnLineTrigger)
		return E_FAIL;

	return S_OK;
}

CCell * CCell::Create(LPDIRECT3DDEVICE9 pDevice, const _ulong & dwIndex,
	const CELLVTXIDX & Index , vector<_vec3>* pVerTexs,
	_vec3 vColor /*= COLOR_GRAY*/, _bool bToolMod /*= false */,vector<CNaviMesh*>* pNaviMeshs)
{
	CCell*	pIns = new CCell(pDevice);

	if (FAILED(pIns->Ready_Cell(dwIndex, Index, pVerTexs, vColor, pNaviMeshs, bToolMod)))
		SafeRelease(pIns);
	return pIns;
}


CComponent * CCell::Clone()
{
	return nullptr;
}

void CCell::Free()
{
	for (_ulong i = 0; i < eLineID::End; ++i)
		SafeRelease(m_pLine[i]);

	SafeRelease(m_pDXLine);
	SafeRelease(m_pDevice);
	CVIBuffer::Free();
}
