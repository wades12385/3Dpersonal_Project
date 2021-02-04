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
	// �ִϸ��̼��� ������ �Ǿ �ȵǱ� ������ ���ʿ� �����ϴ� �Լ��� ����
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(),
		rhs.m_pAniCtrl->GetMaxNumAnimationSets(),
		rhs.m_pAniCtrl->GetMaxNumTracks(),
		rhs.m_pAniCtrl->GetMaxNumEvents(),
		&m_pAniCtrl);
	// 1���� : ���� �� ������ �����ϴ� �ִϸ��̼��� �ִ� ����
	// 2���� : ���� ������ �ִϸ��̼��� �ִ� ����(�밳 ù ��° ���ڰ��� ���� ��ġ��)
	// 3���� : ���� ������ �ִ� Ʈ���� ����(�밳�� �� ���� ���, ��¥ ���� ����� �� �� ��) 
	// 4���� : �ִϸ��̼ǿ��� �����ϴ� Ư���� �̺�Ʈ�� �ִ� ����(������ �츮�� ������� ����)
	// 5���� : �ִϸ��̼� ������ ������ �İ�ü
}


void Engine::CAniCtrl::Play_Animation(const _float& fTimeDelta)
{
	// �ִϸ��̼��� ����ϴ� �Լ�, 2���� : Ư�� �̺�Ʈ �Ǵ� ����Ʈ�� ���� ó���� ��� ���� �����ϴ� ��ü�� �ּ�(������  ���� ������)
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

	// �ִϸ��̼� ���� ����Ǵ� ������ �ð� ���� ��ȯ
	m_dPeriod = pAS->GetPeriod();

	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAS);

	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	// ���� �����ϴ� Ʈ���� ����ġ�� �����ϴ� �Լ�
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	// Ʈ���� Ȱ��ȭ���� �����ϴ� �Լ�
	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();	// �ִϸ��̼��� ����� �� ������ �ð����� �ʱ�ȭ�ϴ� �Լ�
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
