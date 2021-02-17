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

	vector<list<CCell*>>    m_listRelation; // 정점하나와 관계가 있는 셀의 리스트 
	vector<LOADDATA>		m_vecLoadData;
	_bool					m_bHideCell;
	_bool					m_bSelect;
	_bool					m_bLoad; //로드 확인
//////////////////////////////////////////////////////////////////////////
public:

};
END
#define __NAVIMESH_H__
#endif

/*
Cell 클레스가 백터값이 아니라 

백터 리스트의 인덱스값을 갖고 있고 
네비매쉬는 모든 정점을 백터로 들고있고 

cell클레스는 백터 주소랑 자기의 인덱스번호 3개만 저장해서 

바로 접근해서 하는걸로 


네비 매쉬는 정점정보와 인덱스 정보를 들고있게 수정 

 
버퍼트라이컬러 만들어야함 

어 건든 정점을 포함한 쉘만 수정이 들어왔다는 신호를 주고 핸더시 락언락으로 버퍼 수정하고 
나머지는 수정값이 false 일테니 그대로 그림 


전체 쉘을 순회 하면서 수정한 정점을 쓰고이는지 다 검사를 해야하나?? 검사하는게 가벼울까

매번 락 언락이 가벼울까 

들어온 

수정값이 켜지는 경우 3정점중 하나라고 수정이 될때랑 쉘 옵션 변경 


쉘 피킹은 그냥 쉘 순회 하면서 인터렉트트리로 순회해야겠네 

수직으로 된부분이 남아있는지는모르겠고 

정점가운데에쉘 인덱스도 폰트출력해야하고 

트리컨트롤 마져 완성해야겠고 

정점이동은 6면체로  어느쪽 면으로 충돌했는지에 따라 뷰포트 좌표를 월드로 할수 있을거같음 

정면 후면 충돌은 x y 만 

좌우 y z 

상하는 z x 만 이겠네 

*/

/*



떨어지는 기능 구현으로 네비에서 이탈하는 리브속성 

쉘 자체에 하는것보다 쉘에서 한번 그리고 라인중 어느 라인에서 이탈했을지 그떄 리브 적용하고 

플레이어가 리브상태일때 

section 용으로 박스 깔어서 박스와 충돌하면 충돌한 박스에서 갈아탈 네비 메쉬 아이디 얻어서 네비매쉬 정해주고 

쉘 인덱스는 ..순회 해야하나 

x z로만 쉘


평면의 기울기 진행방향으로 평면기울기 -> 어려워 보임 

그냥 현재 위치와 진행방향의 각도를 가지고 진행방향의 기울를 구하는걸로 -> 



*/


/*
//  [2/15/2021 Administrator]
1. 쉘이 커넥트 타입이고 거기서 move 처리 할떄는 연결된 네비 매쉬의 셀이 추가돼서 검사 진행 

연결된 쉘이랑 검사 해서 밖일경우 그대로 현재 매쉬의 셀에서 이동처리 

검사 후 안일 경우  네비 매쉬 교체 및 셀 이동 

2. 쉘이 커넥트 타입 -> 종속된 라인에 커넥트 속성이 있을 경우 
그 라인에서 아웃 처리가 되면 라인에 저장된 연결된 네비매쉬로 이동 셀도 이동 

*/


