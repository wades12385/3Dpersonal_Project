#pragma once
#ifndef __CELL_H__
#include "VIBuffer.h"
#include "Line.h"

BEGIN(Engine)
class CNaviMesh;
class ENGINE_DLL CCell : public CVIBuffer
{
private:
	explicit CCell(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCell() = default;
public:
	// CVIBuffer을(를) 통해 상속됨
	virtual HRESULT				Ready_Component() override;
	HRESULT						Ready_Cell(const _ulong& dwCellIndex, const CELLVTXIDX& Index, vector<_vec3>* pVertexs, _vec3 vColor ,vector<CNaviMesh*>* pNaviMeshs ,_bool bToolMod);
	_bool						Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell);
	void						Render_Cell();
	eCompare::eCompare			Compare(const _vec3* pEndPos, _int& iNavID, _int& iCellIndex);
	
	//셀의 버퍼 수정
	void						Modifying_Buffer();
	//셀 충돌 체크 
	_bool						IsInside(const _vec3 vPos);
	//커넥트 트리거 셀 상태일때 라인의 옵션값은 다 베이스인지  
	HRESULT						Check_Data();
	_bool						IsOnLineTrigger() { return m_bOnLineTrigger; }
	void						Add_LinkCell(const LINKCELL& tLinkCell); // Linkcell 
public:
	const _vec3*				Get_Point(const eCellpt::eCellpt& point);
	CLine*						Get_Line(const eLineID::eLineID& eID) { return m_pLine[eID]; };
	const CELLVTXIDX&			Get_CellVtxIdx() { return m_tVTXIndex; }
	CCell*						Get_Neighbor(eNeighbor::eNeighbor eType) const { return m_pNeighbor[eType]; }
	const _uint&				Get_CellIndex() { return m_iCellIdx; }
	const eCellType::eCellType	Get_CellType() { return m_eType; }
	_bool						IsModify() { return m_bModified; }
	vector<LINKCELL>&			Get_LinkCells() { return m_vecLinkCells; }
	
	void						Set_Neighbor(eNeighbor::eNeighbor eType, CCell* pNeighbor) { m_pNeighbor[eType] = pNeighbor; }
	void						Set_CellType(eCellType::eCellType iType);
	void						Set_Color(const _vec3& dwColor) { m_vCurColor = dwColor; }
	void						Set_BaseColor(const _vec3& dwColor) { m_vBaseColor = dwColor; }
	void						Set_Modify(const _bool& bMod) {m_bModified = bMod; }
	void						Set_SelectNav(const _bool& bSelect) { m_bSelect = bSelect; }
	//라인 접근해서 타입 바꾸지 말고 이걸로 (직접 라인 접근하지 말고 셀 통해 접근하는 식으로 짜야겠음 getLine 빼버리고
	void						Set_LineTrigger(const eLineID::eLineID& eID, const eCellType::eCellType& eType);
public:
	static CCell*				Create(LPDIRECT3DDEVICE9 pDevice, const _ulong& dwIndex, const CELLVTXIDX& Index ,vector<_vec3>* pVerTexs , _vec3 vColor = VCOLOR_GRAY ,_bool bToolMod = false , vector<CNaviMesh*>* pNaviMeshs = nullptr);
	virtual CComponent *		Clone() override;
private:
	virtual void				Free() override;
private:
	CCell*						m_pNeighbor[eNeighbor::End];
	CLine*						m_pLine[eLineID::End];
	LPD3DXLINE					m_pDXLine;
	_uint						m_iCellIdx;
	CELLVTXIDX					m_tVTXIndex; //인덱스 
	vector<_vec3>*				m_pVerTexes; //네비매쉬의 정점집합 주소 
	
	//////////////////////////////////////////////////////////////////////////
	eCellType::eCellType		m_eType; // 쉘 속성
	vector<CNaviMesh*>*		    m_pNavMeshs = nullptr;	//네비매쉬 배열의 주소 
	vector<LINKCELL>			m_vecLinkCells; 	// 커넥트 셀 벡터
	_bool						m_bOnLineTrigger;//셀의 라인들이 트리거 옵션이 있는가

	//////////////////////////////////////////////////////////////////////////

	_bool						m_bToolMode;
	_bool						m_bModified; //수정이 됐는지 확인 이거 필요한지 나중에 검토
	_bool						m_bCellRender;
	_vec3						m_vCurColor; // type에 따라 바뀌고 난 뒤 색
	_vec3						m_vBaseColor;// 기본색 층수에 따라 다른 색 부여 
	_bool						m_bSelect; // Select 상태인지 확인용 베이스 타입의 라인컬러를 바꿈 

};
END

#define __CELL_H__ 
#endif
