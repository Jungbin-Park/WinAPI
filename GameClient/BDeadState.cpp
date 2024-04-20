#include "pch.h"
#include "BDeadState.h"

#include "CFSM.h"
#include "CBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSound.h"

BDeadState::BDeadState()
{

}

BDeadState::~BDeadState()
{

}

void BDeadState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Boss", L"sound\\Music\\Boss.wav");
	pSound->SetVolume(0.f);
	pSound->PlayToBGM();

	pAnimator->Play(L"DEAD", false);
}

void BDeadState::FinalTick()
{

}

void BDeadState::Exit()
{

}



