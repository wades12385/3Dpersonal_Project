#pragma once
#ifndef __LINE_H__
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CLine : public CBase
{
private:
	explicit CLine();
	virtual ~CLine()= default;

public:
	HRESULT	Ready_Line(const _vec2* pPointA, const _vec2* pPointB);
	eRelationLine::eRelationLine Compare(const _vec2* pEndPos);

public:
	void						Set_Color(const _vec3& dwColor) { m_vColor = dwColor; }
	const _vec3&				Get_Color(){ return m_vColor; }
	void						Set_Type(eCellType::eCellType eType);

	const eCellType::eCellType  Get_Type() { return m_eType; }
	vector<LINKCELL>&			Get_LinkCells() { return m_vecLinkCells; }

public:
	static CLine*		Create(const _vec2* pPointA, const _vec2* pPointB);
	virtual void Free() override;
private:
	_vec2						m_vPoint[eLinePt::End];
	_vec2						m_vDirection;
	_vec2						m_vNormal;
	_vec3						m_vColor;
	eCellType::eCellType		m_eType;
	vector<LINKCELL>			m_vecLinkCells;
	//네비매쉬 주소도 보관해야하나 차피 아이디로 찾는거나 뭐나 지랄같음
};
END
#define __LINE_H__
#endif
