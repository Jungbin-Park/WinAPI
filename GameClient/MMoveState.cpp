#include "pch.h"
#include "MMoveState.h"

#include "CFSM.h"
#include "CMiniBoss.h"
#include "CAnimator.h"

static float Time = 0.f;

MMoveState::MMoveState()
{
}

MMoveState::~MMoveState()
{
}

void MMoveState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	pAnimator->Play(L"IDLE", true);
}

void MMoveState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();

	Time += DT;

	if (Time >= 2.f)
	{
		GetFSM()->ChangeState(L"Move");
	}
}

void MMoveState::Exit()
{
	Time = 0.f;
}



