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
	// CVIBuffer��(��) ���� ��ӵ�
	virtual HRESULT				Ready_Component() override;
	HRESULT						Ready_Cell(const _ulong& dwCellIndex, const CELLVTXIDX& Index, vector<_vec3>* pVertexs, _vec3 vColor ,vector<CNaviMesh*>* pNaviMeshs ,_bool bToolMod);
	_bool						Compare_Point(const _vec3* pPointFirst, const _vec3* pPointSecond, CCell* pCell);
	void						Render_Cell();
	eCompare::eCompare			Compare(const _vec3* pEndPos, _int& iNavID, _int& iCellIndex);
	
	//���� ���� ����
	void						Modifying_Buffer();
	//�� �浹 üũ 
	_bool						IsInside(const _vec3 vPos);
	//Ŀ��Ʈ Ʈ���� �� �����϶� ������ �ɼǰ��� �� ���̽�����  
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
	//���� �����ؼ� Ÿ�� �ٲ��� ���� �̰ɷ� (���� ���� �������� ���� �� ���� �����ϴ� ������ ¥�߰��� getLine ��������
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
	CELLVTXIDX					m_tVTXIndex; //�ε��� 
	vector<_vec3>*				m_pVerTexes; //�׺�Ž��� �������� �ּ� 
	
	//////////////////////////////////////////////////////////////////////////
	eCellType::eCellType		m_eType; // �� �Ӽ�
	vector<CNaviMesh*>*		    m_pNavMeshs = nullptr;	//�׺�Ž� �迭�� �ּ� 
	vector<LINKCELL>			m_vecLinkCells; 	// Ŀ��Ʈ �� ����
	_bool						m_bOnLineTrigger;//���� ���ε��� Ʈ���� �ɼ��� �ִ°�

	//////////////////////////////////////////////////////////////////////////

	_bool						m_bToolMode;
	_bool						m_bModified; //������ �ƴ��� Ȯ�� �̰� �ʿ����� ���߿� ����
	_bool						m_bCellRender;
	_vec3						m_vCurColor; // type�� ���� �ٲ�� �� �� ��
	_vec3						m_vBaseColor;// �⺻�� ������ ���� �ٸ� �� �ο� 
	_bool						m_bSelect; // Select �������� Ȯ�ο� ���̽� Ÿ���� �����÷��� �ٲ� 

};
END

#define __CELL_H__ 
#endif
