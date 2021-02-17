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
	// CVIBuffer��(��) ���� ��ӵ�
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
	CELLVTXIDX					m_tVTXIndex; //�ε��� 
	vector<_vec3>*				m_pVerTexes; //�׺�Ž��� �������� �ּ� 
	
	
	eCellType::eCellType		m_eType; // �� �Ӽ�



	_bool						m_bModified; //������ �ƴ��� Ȯ�� �̰� �ʿ����� ���߿� ����
	_bool						m_bCellRender;
	D3DXCOLOR					m_dwCurColor; // type�� ���� �ٲ�� �� �� ��
	D3DXCOLOR					m_dwBaseColor;// �⺻�� ������ ���� �ٸ� �� �ο� 

	_bool						m_bSelect; // Select �������� Ȯ�ο� ���̽� Ÿ���� �����÷��� �ٲ� 
};
END

#define __CELL_H__

#endif
