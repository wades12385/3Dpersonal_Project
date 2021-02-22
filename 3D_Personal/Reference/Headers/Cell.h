#pragma once
#ifndef __CELL_H__
#include "VIBuffer.h"
#include "Line.h"

BEGIN(Engine)
class ENGINE_DLL CCell : public CVIBuffer
{
private:
	explicit CCell(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCell() = default;
public:
	// CVIBuffer을(를) 통해 상속됨
	virtual HRESULT				Ready_Component() override;
	HRESULT						Ready_Cell(const _ulong& dwCellIndex, const CELLVTXIDX& Index, vector<_vec3>* pVertexs);
	_bool						Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell);
	void						Render_Cell();
	eCompare::eCompare			Compare(const _vec3* pEndPos, _uint* pCellIndex);
	void						Modifying_Buffer();
public:
	const _vec3*				Get_Point(const eCellpt::eCellpt& point);
	CLine*						Get_Line(const eLineID::eLineID& eID) { return m_pLine[eID]; };
	CCell*						Get_Neighbor(eNeighbor::eNeighbor eType) const { return m_pNeighbor[eType]; }
	const _uint&				Get_CellIndex() { return m_iCellIdx; }
	const eCellType::eCellType	Get_CellType() { return m_eType; }
	_bool						IsModify() { return m_bModified; }
	
//////////////////////////////////////////////////////////////////////////
	void						Set_Neighbor(eNeighbor::eNeighbor eType, CCell* pNeighbor) { m_pNeighbor[eType] = pNeighbor; }
	void						Set_CellType(eCellType::eCellType iType);
	void						Set_Color(const D3DXCOLOR& dwColor) { m_dwCurColor = dwColor; }
	void						Set_BaseColor(const D3DXCOLOR& dwColor) { m_dwBaseColor = dwColor; }
	void						Set_Modify(const _bool& bMod) {m_bModified = bMod; }
	void						Set_SelectNav(const _bool& bSelect) { m_bSelect = bSelect; }

	void						Set_LineOption(const eLineID::eLineID& eID, const eCellType::eCellType& eType);
	  
public:
	static CCell*				Create(LPDIRECT3DDEVICE9 pDevice, const _ulong& dwIndex, const CELLVTXIDX& Index ,vector<_vec3>* pVerTexs);
	virtual CComponent *		Clone() override;
private:
	virtual void				Free() override;
private:
	CCell*						m_pNeighbor[eNeighbor::End];
	CLine*						m_pLine[eLineID::End];
	LPD3DXLINE					m_pDXLine;
	_uint						m_iCellIdx;
	//- 2021 02 08 Modify
	CELLVTXIDX					m_tVTXIndex; //인덱스 
	vector<_vec3>*				m_pVerTexes; //네비매쉬의 정점집합 주소 
	
	
	eCellType::eCellType		m_eType; // 쉘 속성



	_bool						m_bModified; //수정이 됐는지 확인 이거 필요한지 나중에 검토
	_bool						m_bCellRender;
	D3DXCOLOR					m_dwCurColor; // type에 따라 바뀌고 난 뒤 색
	D3DXCOLOR					m_dwBaseColor;// 기본색 층수에 따라 다른 색 부여 

	_bool						m_bSelect; // Select 상태인지 확인용 베이스 타입의 라인컬러를 바꿈 
};
END

#define __CELL_H__

#endif
