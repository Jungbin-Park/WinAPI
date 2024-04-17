#include "pch.h"
#include "BDeadState.h"

#include "CFSM.h"
#include "CBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"

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

	pAnimator->Play(L"DEAD", false);
}

void BDeadState::FinalTick()
{

}

void BDeadState::Exit()
{

}



