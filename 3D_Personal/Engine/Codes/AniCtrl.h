#pragma once
#ifndef __ANICTRL_H__
	

#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CAniCtrl : public CBase
{
private:
	explicit CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	explicit CAniCtrl(const CAniCtrl& other);
	virtual ~CAniCtrl() =default;
public:
	HRESULT								Ready_AniCtrl();
	void								Play_Animation(const _float& fTimeDelta);
public:
	void								Set_AnimationIndex(const _uint& iIndex);
	LPD3DXANIMATIONCONTROLLER			Get_AniCtrl() { return m_pAniCtrl; }
	_bool								Is_AnimationSetEnd();
private:
	LPD3DXANIMATIONCONTROLLER			m_pAniCtrl;
	_uint								m_iCurrentTrack;
	_uint								m_iNewTrack;
	_float								m_fAccTime;
	_uint								m_iOriginIdx;

	_double								m_dPeriod;

public:
	static CAniCtrl*					Create(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	static CAniCtrl*					Create(const CAniCtrl& other);
	virtual void						Free()override;

};
END
#define __ANICTRL_H__
#endif // !__ANICTRL_H__
