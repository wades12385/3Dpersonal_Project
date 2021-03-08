#pragma once
#ifndef __NAVIMESH_H__
#include "Component.h"
#include "Cell.h"
BEGIN(Engine)
class ENGINE_DLL CNaviMesh : public CComponent
{
	typedef struct LineData
	{
		eCellType::eCellType iLineType;
		vector<LINKCELL> vecLinkCells;

	}LINEDATA;
	typedef struct LoadData
	{
		_int iCellIdx;
		vector<LINKCELL> vecLinkCells;
		_bool bOnLineTrigger;
		LINEDATA vLine[eLineID::End];
	}LOADDATA;
private:
	explicit CNaviMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CNaviMesh(const CNaviMesh& rhs);
	virtual ~CNaviMesh() = default;

public:
	HRESULT						Ready_Meshes(const _tchar * pFilePath, const _bool& bToolMod); // .obj data Loading 
	HRESULT						Load_Mesh(const _tchar * pFilePath, const _bool& bToolMod);
	HRESULT						Ready_NavigationMesh(vector<CNaviMesh*>* pNaviMeshs = nullptr);  //  Cell instancing
	void						Render_Meshes() ;

public:
	HRESULT						Link_Cell();
	//���� ��ġ�� �ش��ϴ� �� ��ȣ ã��
	HRESULT						Find_CurCellIdx(const _vec3& vPos, _int& iCellIdx);
	//Navi �¿�� 
	void						OnNaviMesh(_vec3& vPos , const _int& iCellidx);
	// 1�� range ������ ����� �������� 
	eCompare::eCompare			CompareCell(_int& iNavID, _int& iCellIdx,const  _vec3&	vEndPos,const _float& fRange);
	_vec3						MoveNaviMesh(_int& iNavID, _int& CellIdx, const _vec3& vTargetPos, const _vec3& vTargetDir, const _float& fRange);
	
	//////////////////////////////////////////////////////////////////////////
public:
	void						Set_HideCell(const _bool& bHide) { m_bHideCell = bHide; }
	void						Set_Select(const _bool& bSelect) { m_bSelect = bSelect; }
	void						Set_BaseColor(const _vec3& dwColor);
	void						Set_NaviID(const _int& iID) { m_iNaviID = iID; }

	vector<_vec3>&				Get_Vertex() { return m_vecVTX; }
	vector<CELLVTXIDX>&			Get_vIndex() { return m_vecIndex; }
	const _int&					Get_NaviID(){ return m_iNaviID; }
	_vec3&						Get_Color() { return m_vBaseColor; }

	vector<CCell*>&				Get_vCell() { return m_vecCell; }
	_bool						IsHideCell() { return m_bHideCell; };

	void						Modifying_Vertex(const _uint& iVtxIdx);
	void						Modifying_CellIdx(const _uint& iCellIdx);
public:
	static CNaviMesh*			Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath, const _bool& bToolMode = false);
	static CNaviMesh*			Load(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath,const _bool& bToolMode = false, vector<CNaviMesh*>* pNaviMeshs = nullptr);
private:
	virtual void				Free();
private:
	vector<CELLVTXIDX>			m_vecIndex;
	vector<CCell*>				m_vecCell;
	vector<_vec3>				m_vecVTX;
	vector<list<CCell*>>		m_listRelation; // �����ϳ��� ���谡 �ִ� ���� ����Ʈ 

	vector<LOADDATA>			m_vecLoadData;//�ε� �� ���� ���� ������
	_bool						m_bLoad; //�ε� Ȯ��

	_bool						m_bHideCell;
	_bool						m_bSelect; //�������� ������ �׺�Ž� ���� ǥ�ÿ�

	_vec3						m_vBaseColor;
	_int						m_iNaviID;

	_bool						m_bToolMode;

	// CComponent��(��) ���� ��ӵ�
	virtual HRESULT Ready_Component() override;
	virtual HRESULT Update_Component(const _float & fTimeDelta = 0.f) override;
	//////////////////////////////////////////////////////////////////////////
};
END
#define __NAVIMESH_H__
#endif

/*
Cell Ŭ������ ���Ͱ��� �ƴ϶� 

���� ����Ʈ�� �ε������� ���� �ְ� 
�׺�Ž��� ��� ������ ���ͷ� ����ְ� 

cellŬ������ ���� �ּҶ� �ڱ��� �ε�����ȣ 3���� �����ؼ� 

�ٷ� �����ؼ� �ϴ°ɷ� 


�׺� �Ž��� ���������� �ε��� ������ ����ְ� ���� 

 
����Ʈ�����÷� �������� 

�� �ǵ� ������ ������ ���� ������ ���Դٴ� ��ȣ�� �ְ� �ڴ��� ��������� ���� �����ϰ� 
�������� �������� false ���״� �״�� �׸� 


��ü ���� ��ȸ �ϸ鼭 ������ ������ �����̴��� �� �˻縦 �ؾ��ϳ�?? �˻��ϴ°� �������

�Ź� �� ����� ������� 

���� 

�������� ������ ��� 3������ �ϳ���� ������ �ɶ��� �� �ɼ� ���� 


�� ��ŷ�� �׳� �� ��ȸ �ϸ鼭 ���ͷ�ƮƮ���� ��ȸ�ؾ߰ڳ� 

�������� �Ⱥκ��� �����ִ����¸𸣰ڰ� 

����������� �ε����� ��Ʈ����ؾ��ϰ� 

Ʈ����Ʈ�� ���� �ϼ��ؾ߰ڰ� 

�����̵��� 6��ü��  ����� ������ �浹�ߴ����� ���� ����Ʈ ��ǥ�� ����� �Ҽ� �����Ű��� 

���� �ĸ� �浹�� x y �� 

�¿� y z 

���ϴ� z x �� �̰ڳ� 

*/

/*



�������� ��� �������� �׺񿡼� ��Ż�ϴ� ����Ӽ� 

�� ��ü�� �ϴ°ͺ��� ������ �ѹ� �׸��� ������ ��� ���ο��� ��Ż������ �׋� ���� �����ϰ� 

�÷��̾ ��������϶� 

section ������ �ڽ� �� �ڽ��� �浹�ϸ� �浹�� �ڽ����� ����Ż �׺� �޽� ���̵� �� �׺�Ž� �����ְ� 

�� �ε����� ..��ȸ �ؾ��ϳ� 

x z�θ� ��


����� ���� ����������� ������ -> ����� ���� 

�׳� ���� ��ġ�� ��������� ������ ������ ��������� ��︦ ���ϴ°ɷ� -> 



*/


/*
//  [2/15/2021 Administrator]
1. ���� Ŀ��Ʈ Ÿ���̰� �ű⼭ move ó�� �ҋ��� ����� �׺� �Ž��� ���� �߰��ż� �˻� ���� 

����� ���̶� �˻� �ؼ� ���ϰ�� �״�� ���� �Ž��� ������ �̵�ó�� 

�˻� �� ���� ���  �׺� �Ž� ��ü �� �� �̵� 

2. ���� Ŀ��Ʈ Ÿ�� -> ���ӵ� ���ο� Ŀ��Ʈ �Ӽ��� ���� ��� 
�� ���ο��� �ƿ� ó���� �Ǹ� ���ο� ����� ����� �׺�Ž��� �̵� ���� �̵� 

*/


