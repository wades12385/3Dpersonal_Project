#pragma once
#ifndef __NAVIMESH_H__
#include "Mesh.h"
#include "Cell.h"
BEGIN(Engine)
class ENGINE_DLL CNaviMesh : public CMesh
{
	typedef struct LineData
	{
		_uint iLineType;
	}LINEDATA;
	typedef struct LoadData
	{
		_uint iCellIdx;
		_uint iCellType;
		vector<LINEDATA> vLine;
	}LOADDATA;


private:
	explicit CNaviMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CNaviMesh(const CNaviMesh& rhs);
	virtual ~CNaviMesh() = default;

public:
	virtual HRESULT			Ready_Meshes(const _tchar * pFilePath, const _tchar * pFileName) override; // .obj data Loading 
	HRESULT					Load_Mesh(const _tchar * pFilePath);
	HRESULT					Ready_NavigationMesh();  //  Cell instancing
	virtual void			Render_Meshes() override;

public:
	HRESULT					Link_Cell();
	_vec3					Move_OnNaviMesh(const _vec3* pTargetPos, const _vec3* pTargetDir);
public:
	void					Set_CellIndex(const _ulong& iIndex) { m_iCurIndex = iIndex; }
	void					Set_HideCell(const _bool& bHide) { m_bHideCell = bHide; }
	void					Set_Select(const _bool& bSelect) { m_bSelect = bSelect; }

	vector<_vec3>&				Get_vCellVtx() { return m_vecVTX; }
	vector<CELLVTXIDX>&			Get_vIndex() { return m_vecIndex; }

	vector<CCell*>&			Get_vCell() { return m_vecCell; }
	_bool					IsHideCell() { return m_bHideCell; };
	
	void					Modifying_Vertex(const _uint& iVtxIdx);
	void					Modifying_CellIdx(const _uint& iCellIdx);
public:
	static CNaviMesh*		Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFilePath);
	static CNaviMesh*		Load(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath);
	virtual CComponent *	Clone() override;
private:
	virtual void			Free();
private:
	_uint					m_iCurIndex;
	vector<CELLVTXIDX>		m_vecIndex;
	vector<CCell*>			m_vecCell;
	vector<_vec3>			m_vecVTX;

	vector<list<CCell*>>    m_listRelation; // �����ϳ��� ���谡 �ִ� ���� ����Ʈ 
	vector<LOADDATA>		m_vecLoadData;
	_bool					m_bHideCell;
	_bool					m_bSelect;
	_bool					m_bLoad; //�ε� Ȯ��
//////////////////////////////////////////////////////////////////////////
public:

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


