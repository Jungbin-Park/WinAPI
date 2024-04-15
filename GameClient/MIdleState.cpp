#include "pch.h"
#include "MIdleState.h"

#include "CFSM.h"
#include "CMiniBoss.h"
#include "CAnimator.h"

static float Time = 0.f;

MIdleState::MIdleState()
{
}

MIdleState::~MIdleState()
{
}

void MIdleState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();

	pAnimator->Play(L"IDLE", true);
}

void MIdleState::FinalTick()
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

void MIdleState::Exit()
{
	Time = 0.f;
}



