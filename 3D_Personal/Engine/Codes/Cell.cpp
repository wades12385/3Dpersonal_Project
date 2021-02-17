#include "Cell.h"

USING(Engine)

Engine::CCell::CCell(LPDIRECT3DDEVICE9 pDevice)
	:CVIBuffer(pDevice)
	, m_pDXLine(nullptr)
	, m_bModified(false)
	, m_pVerTexes(nullptr)
	, m_iCellIdx(0)
	, m_eType(eCellType::Base)
	, m_bSelect(false)
	, m_dwCurColor(COLOR_GRAY)
	, m_dwBaseColor(COLOR_GRAY)
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
	pVtxCol[0].dwColor = m_dwCurColor;

	pVtxCol[1].vPosition = (*m_pVerTexes)[m_tVTXIndex._B];
	pVtxCol[1].dwColor = m_dwCurColor;

	pVtxCol[2].vPosition = (*m_pVerTexes)[m_tVTXIndex._C];
	pVtxCol[2].dwColor = m_dwCurColor;

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();

	return S_OK;
}




HRESULT CCell::Ready_Cell(const _ulong & dwCellIndex, const CELLVTXIDX & Index, vector<_vec3>* pVertexs)
{
	m_pVerTexes = pVertexs;
	m_iCellIdx = dwCellIndex;
	m_tVTXIndex = Index;
	m_tVTXIndex._A -= 1;
	m_tVTXIndex._B -= 1;
	m_tVTXIndex._C -= 1;

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

	if (m_bSelect && m_eType != eCellType::Base)
		m_pDXLine->SetWidth(5.5f);
	else
		m_pDXLine->SetWidth(1.5f);

	m_pDevice->EndScene();
	m_pDevice->BeginScene();

	m_pDXLine->Begin();
	 
	_matrix matTemp;

	if (m_bSelect)
	{
		if (m_eType == eCellType::Base)
		{
			m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), COLOR_RED);
		}
		else
		{
			//컬러값 맴버를 뺄수는 있을거같은데 
			for (int i = 0; i < eLineID::End; ++i)
			{
				if(m_pLine[i]->Get_Type() != eCellType::Base)
					m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), m_pLine[i]->Get_Color());
				else
					m_pDXLine->DrawTransform(vPoint + i, 2, D3DXMatrixIdentity(&matTemp), COLOR_RED);
			}
		}
	}
	else
	{
		m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), COLOR_LIGHTGRAY);
	}

	m_pDXLine->End();
}

Engine::eCompare::eCompare Engine::CCell::Compare(const _vec3* pEndPos, _uint* pCellIndex)
{
	for (_ulong i = 0; i < eLineID::End; ++i)
	{
		if (eRelationLine::OutLine == m_pLine[i]->Compare(&_vec2(pEndPos->x, pEndPos->z)))
		{
			if (nullptr == m_pNeighbor[i])
				return eCompare::Stop;
			else
			{
				*pCellIndex = m_pNeighbor[i]->Get_CellIndex();
				return eCompare::Move;
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
	pVtxCol[0].dwColor = m_dwCurColor;

	pVtxCol[1].vPosition = (*m_pVerTexes)[m_tVTXIndex._B];
	pVtxCol[1].dwColor = m_dwCurColor;

	pVtxCol[2].vPosition = (*m_pVerTexes)[m_tVTXIndex._C];
	pVtxCol[2].dwColor = m_dwCurColor;
	  
	m_pVB->Unlock();
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
	if (m_eType == iType)
		return;

	 m_eType = iType; 

	 switch (m_eType)
	 {
	 case Engine::eCellType::Base:
		 Set_Color(m_dwBaseColor);
		 break;
	 case Engine::eCellType::Leave:
		 Set_Color(COLOR_SKYBLUE);
		 break;
	 case Engine::eCellType::Connect:
		 Set_Color(COLOR_YELLOW);
		 break;
	 }
	 Modifying_Buffer();
}

void CCell::Set_LineOption(const eLineID::eLineID & eID, const eCellType::eCellType & eType)
{
	m_pLine[eID]->Set_Type(eType);
}

CCell * CCell::Create(LPDIRECT3DDEVICE9 pDevice, const _ulong & dwIndex, const CELLVTXIDX & Index , vector<_vec3>* pVerTexs)
{
	CCell*	pIns = new CCell(pDevice);

	if (FAILED(pIns->Ready_Cell(dwIndex, Index, pVerTexs)))
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
