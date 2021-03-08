#pragma once

class CTileSetCtr
{
public:
	CTileSetCtr();
	~CTileSetCtr();
	//calc
	void PeekingDown(const _vec3& vMouse);
	void peekingUp(const _vec3& vMouse);
	int Get_TileIndex(const _vec3& vPos) const;
	bool IsPicking(const _vec3& vPos, const int& iIndex) const;
	void DragPeeking();
	
	
	HRESULT Ready_TileSetCtr(const wstring& wstrTerrainObjKey ,
		const BYTE& byTileSetX , const BYTE& byTileSetY ,const CSize& cSize);
	void ClearDragTile();
	void InsertDragIdx();

	//reset �� �Լ� 
	void ResetPeeking()
	{
		m_bIsDragPeek = false;
		m_vecDragIdx.clear();
		m_vecDragIdx.shrink_to_fit();
	}
	void Render_TileSetCtr();
	void Render_TileLine(int idx);
	void Release_TileSetCtr();

	//getter

public:
	int m_iFirstIdx;
	int m_iLastIdx;
	int m_iDragCX;
	int m_iDragCY;

	//Ÿ�ϼ� ��������Ʈ Ÿ�� ���� 
	BYTE m_byTileSetX;
	BYTE m_byTileSetY;
	//view ratio 
	float m_fRatioX;
	float m_fRatioY;



	wstring			m_wstrTerrainObjKey;
	vector<TILE*>	m_vecTile; // Ÿ�ϼ� ������ 
	bool			m_bIsDragPeek;
	vector<int>		m_vecDragIdx; //�巡���� Ÿ�� �ε��� 
};

