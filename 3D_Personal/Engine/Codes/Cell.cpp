#include "Cell.h"

USING(Engine)

Engine::CCell::CCell(LPDIRECT3DDEVICE9 pDevice)
	:m_pDevice(pDevice)
	,m_pDXLine(nullptr)
{
	m_pDevice->AddRef();
	ZeroMemory(m_vPoint, sizeof(_vec3*) * eCellpt::End);
	ZeroMemory(m_pNeighbor, sizeof(CCell*) * eNeighbor::End);
	ZeroMemory(m_pLine, sizeof(CLine*) * eLineID::End);
}

HRESULT Engine::CCell::Ready_Cell(const _ulong& dwIndex, const _vec3* pPointA, const _vec3* pPointB, const _vec3* pPointC)
{
	m_dwIndex = dwIndex;

	m_vPoint[eCellpt::A] = *pPointA;
	m_vPoint[eCellpt::B] = *pPointB;
	m_vPoint[eCellpt::C] = *pPointC;

	m_pLine[eLineID::AB] = CLine::Create(&_vec2(m_vPoint[eCellpt::A].x, m_vPoint[eCellpt::A].z),
										&_vec2(m_vPoint[eCellpt::B].x, m_vPoint[eCellpt::B].z));

	m_pLine[eLineID::BC] = CLine::Create(&_vec2(m_vPoint[eCellpt::B].x, m_vPoint[eCellpt::B].z),
								  		 &_vec2(m_vPoint[eCellpt::C].x, m_vPoint[eCellpt::C].z));	

	m_pLine[eLineID::CA] = CLine::Create(&_vec2(m_vPoint[eCellpt::C].x, m_vPoint[eCellpt::C].z),
										 &_vec2(m_vPoint[eCellpt::A].x, m_vPoint[eCellpt::A].z));

#ifdef _DEBUG
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pDXLine)))
		return E_FAIL;
#endif
	return S_OK;
}


_bool Engine::CCell::Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell)
{
	if (*pPointFirst == m_vPoint[eCellpt::A])
	{
		if (*pPointSecond == m_vPoint[eCellpt::B])
		{
			m_pNeighbor[eNeighbor::AB] = pCell;
			return true;
		}

		if (*pPointSecond == m_vPoint[eCellpt::C])
		{
			m_pNeighbor[eNeighbor::CA] = pCell;
			return true;
		}
	}

	if (*pPointFirst == m_vPoint[eCellpt::B])
	{
		if (*pPointSecond == m_vPoint[eCellpt::A])
		{
			m_pNeighbor[eNeighbor::AB] = pCell;
			return true;
		}

		if (*pPointSecond == m_vPoint[eCellpt::C])
		{
			m_pNeighbor[eNeighbor::BC] = pCell;
			return true;
		}
	}

	if (*pPointFirst == m_vPoint[eCellpt::C])
	{
		if (*pPointSecond == m_vPoint[eCellpt::B])
		{
			m_pNeighbor[eNeighbor::BC] = pCell;
			return true;
		}

		if (*pPointSecond == m_vPoint[eCellpt::A])
		{
			m_pNeighbor[eNeighbor::CA] = pCell;
			return true;
		}
	}

	return false;
}
void Engine::CCell::Render_Cell(void)
{
	_vec3		vPoint[4];

	vPoint[0] = m_vPoint[eCellpt::A];
	vPoint[1] = m_vPoint[eCellpt::B];
	vPoint[2] = m_vPoint[eCellpt::C];
	vPoint[3] = m_vPoint[eCellpt::A];

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

	m_pDXLine->SetWidth(3.f);	//라인 굵기를 결정
	m_pDevice->EndScene();
	m_pDevice->BeginScene();

	m_pDXLine->Begin();

	_matrix matTemp;

	m_pDXLine->DrawTransform(vPoint, 4, D3DXMatrixIdentity(&matTemp), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));

	m_pDXLine->End();
}

Engine::eCompare::eCompare Engine::CCell::Compare(const _vec3* pEndPos, _ulong* pCellIndex)
{
	for (_ulong i = 0; i < eLineID::End; ++i)
	{
		if (eRelationLine::OutLine == m_pLine[i]->Compare(&_vec2(pEndPos->x, pEndPos->z)))
		{
			if (nullptr == m_pNeighbor[i])
				return eCompare::Stop;
			else
			{
				*pCellIndex = *m_pNeighbor[i]->Get_CellIndex();
				return eCompare::Move;
			}
		}
	}

	return eCompare::Move;
}

CCell* Engine::CCell::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwIndex, const _vec3* pPointA, const _vec3* pPointB, const _vec3* pPointC)
{
	CCell*	pIns = new CCell(pGraphicDev);

	if (FAILED(pIns->Ready_Cell(dwIndex, pPointA, pPointB, pPointC)))
		SafeRelease(pIns);

	return pIns;
}

void CCell::Free()
{
	for (_ulong i = 0; i < eLineID::End; ++i)
		SafeRelease(m_pLine[i]);

	SafeRelease(m_pDXLine);
	SafeRelease(m_pDevice);
}
