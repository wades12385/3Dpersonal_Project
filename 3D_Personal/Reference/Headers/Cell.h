#pragma once
#ifndef __CELL_H__
#include "Base.h"
#include "Line.h"

BEGIN(Engine)
class ENGINE_DLL CCell : public CBase
{
private:
	explicit CCell(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCell() = default;

public:
	HRESULT						Ready_Cell(const _ulong& dwIndex,const _vec3* pPointA,const _vec3* pPointB,const _vec3* pPointC);
	_bool						Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell);
	void						Render_Cell();
	eCompare::eCompare			Compare(const _vec3* pEndPos, _ulong* pCellIndex);
public:
	const _vec3*				Get_Point(eCellpt::eCellpt eType) const { return &m_vPoint[eType]; }
	CCell*						Get_Neighbor(eNeighbor::eNeighbor eType) const { return m_pNeighbor[eType]; }
	const _ulong*				Get_CellIndex() { return &m_dwIndex; }
	void						Set_Neighbor(eNeighbor::eNeighbor eType, CCell* pNeighbor) { m_pNeighbor[eType] = pNeighbor; }
public:
	static CCell*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwIndex, const _vec3* pPointA, const _vec3* pPointB, const _vec3* pPointC);
private:
	virtual void				Free() override;
private:
	_vec3						m_vPoint[eCellpt::End];
	CCell*						m_pNeighbor[eNeighbor::End];
	CLine*						m_pLine[eLineID::End];
	LPD3DXLINE					m_pDXLine;
	_ulong						m_dwIndex;

	LPDIRECT3DDEVICE9			m_pDevice;
};
END

#define __CELL_H__
#endif
