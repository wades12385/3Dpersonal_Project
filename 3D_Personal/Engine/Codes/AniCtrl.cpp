#include "AniCtrl.h"


USING(Engine)

Engine::CAniCtrl::CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
	, m_fAccTime(0.f)
	, m_iOriginIdx(999)
	, m_dPeriod(0.0)
{
	m_pAniCtrl->AddRef();
}
Engine::CAniCtrl::CAniCtrl(const CAniCtrl& rhs)
	: m_iCurrentTrack(rhs.m_iCurrentTrack)
	, m_iNewTrack(rhs.m_iNewTrack)
	, m_fAccTime(rhs.m_fAccTime)
	, m_iOriginIdx(rhs.m_iOriginIdx)
	, m_dPeriod(0.0)

{
	// 애니메이션은 공유가 되어선 안되기 때문에 애초에 복제하는 함수가 제공
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(),
		rhs.m_pAniCtrl->GetMaxNumAnimationSets(),
		rhs.m_pAniCtrl->GetMaxNumTracks(),
		rhs.m_pAniCtrl->GetMaxNumEvents(),
		&m_pAniCtrl);
	// 1인자 : 복제 시 원본이 제공하는 애니메이션의 최대 개수
	// 2인자 : 구동 가능한 애니메이션의 최대 개수(대개 첫 번째 인자값이 값이 일치함)
	// 3인자 : 구동 가능한 최대 트랙의 개수(대개는 한 개만 사용, 진짜 많이 써봐야 두 개 씀) 
	// 4인자 : 애니메이션에서 제공하는 특수한 이벤트의 최대 개수(하지만 우리는 사용하지 못함)
	// 5인자 : 애니메이션 정보를 복제할 컴객체
}


void Engine::CAniCtrl::Play_Animation(const _float& fTimeDelta)
{
	// 애니메이션을 재생하는 함수, 2인자 : 특정 이벤트 또는 이펙트에 대한 처리를 어떻게 할지 결정하는 객체의 주소(하지만  직접 제어함)
	m_pAniCtrl->AdvanceTime(fTimeDelta, NULL);	
	m_fAccTime += fTimeDelta;
}

HRESULT Engine::CAniCtrl::Ready_AniCtrl(void)
{
	return S_OK;
}

_bool Engine::CAniCtrl::Is_AnimationSetEnd(void)
{
	D3DXTRACK_DESC				tTrackInfo;
	ZeroMemory(&tTrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrentTrack, &tTrackInfo);

	if (tTrackInfo.Position >= m_dPeriod - 0.1)
		return true;

	return false;
}

void Engine::CAniCtrl::Set_AnimationIndex(const _uint& iIndex)
{
	if (m_iOriginIdx == iIndex)
		return;

	m_iNewTrack = m_iCurrentTrack == 0 ? 1 : 0;

	LPD3DXANIMATIONSET		pAS = NULL;
	m_pAniCtrl->GetAnimationSet(iIndex, &pAS);
	//m_pAniCtrl->GetAnimationSetByName();

	// 애니메이션 셋이 진행되는 최종의 시간 값을 반환
	m_dPeriod = pAS->GetPeriod();

	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAS);

	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	// 현재 구동하는 트랙의 가중치를 결정하는 함수
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	// 트랙을 활성화할지 결정하는 함수
	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();	// 애니메이션이 재생될 때 증가는 시간값을 초기화하는 함수
	m_fAccTime = 0.f;

	m_pAniCtrl->SetTrackPosition(m_iNewTrack, 0.0);
	m_iOriginIdx = iIndex;

	m_iCurrentTrack = m_iNewTrack;

}



Engine::CAniCtrl* Engine::CAniCtrl::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	CAniCtrl*	pIns = new CAniCtrl(pAniCtrl);

	if (FAILED(pIns->Ready_AniCtrl()))
		SafeRelease(pIns);

	return pIns;
}

Engine::CAniCtrl* Engine::CAniCtrl::Create(const CAniCtrl& other)
{
	CAniCtrl*	pIns = new CAniCtrl(other);

	if (FAILED(pIns->Ready_AniCtrl()))
	{
		MSG_BOX(L"Failed Copy AniCtrl");
		SafeRelease(pIns);
	}

	return pIns;
}

void Engine::CAniCtrl::Free()
{
	SafeRelease(m_pAniCtrl);
}
