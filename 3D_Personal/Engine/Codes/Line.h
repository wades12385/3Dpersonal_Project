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

	static CLine*		Create(const _vec2* pPointA, const _vec2* pPointB);
	virtual void Free() override;
private:
	_vec2				m_vPoint[eLinePt::End];
	_vec2				m_vDirection;
	_vec2				m_vNormal;
};
END
#define __LINE_H__
#endif
