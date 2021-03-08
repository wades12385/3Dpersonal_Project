#include "Line.h"

USING(Engine)
CLine::CLine()
	:m_vColor(VCOLOR_LIGHTGRAY)
	,m_eType(eCellType::Base)
{
}

HRESULT CLine::Ready_Line(const _vec2 * pPointA, const _vec2 * pPointB)
{
	m_vPoint[eLinePt::Start] = *pPointA;
	m_vPoint[eLinePt::Last] = *pPointB;

	m_vDirection = m_vPoint[eLinePt::Last] - m_vPoint[eLinePt::Start];
	m_vNormal = _vec2(m_vDirection.y * -1.f, m_vDirection.x);
	D3DXVec2Normalize(&m_vNormal, &m_vNormal);

	return S_OK;
}

eRelationLine::eRelationLine CLine::Compare(const _vec2 * pEndPos)
{
	_vec2 vDest = *pEndPos - m_vPoint[eLinePt::Start];
	_float fResult = D3DXVec2Dot(D3DXVec2Normalize(&vDest, &vDest), &m_vNormal);

	if (0.f <= fResult)
		return eRelationLine::OutLine;
	else
		return eRelationLine::InLine;
}

void CLine::Set_Type(eCellType::eCellType eType)
{
	switch (eType)
	{
	case Engine::eCellType::Base:
		Set_Color(VCOLOR_LIGHTGRAY);
		m_vecLinkCells.clear();
		m_vecLinkCells.shrink_to_fit();
		break;
	case Engine::eCellType::Leave:
		Set_Color(VCOLOR_BLUE);
		m_vecLinkCells.clear();
		m_vecLinkCells.shrink_to_fit();
		break;
	case Engine::eCellType::Connect:
		Set_Color(VCOLOR_ORANGE);
		break;
	}
	m_eType = eType;
}

CLine * CLine::Create(const _vec2 * pPointA, const _vec2 * pPointB)
{
	CLine*	pIns = new CLine();

	if (FAILED(pIns->Ready_Line(pPointA, pPointB)))
		SafeRelease(pIns);

	return pIns;
}

void CLine::Free()
{
	m_vecLinkCells.clear();
	m_vecLinkCells.shrink_to_fit();
}
