#include "pch.h"
#include "MWakeState.h"

#include "CFSM.h"
#include "CMiniBoss.h"
#include "CAnimator.h"

static float Time = 0.f;

MWakeState::MWakeState()
{
}

MWakeState::~MWakeState()
{
}

void MWakeState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();
	eDirection pDir = pMBoss->GetDirection();

	if (pMBoss->IsMonDead() != true)
	{
		if (pDir == eDirection::Left)
		{
			pAnimator->Play(L"WAKE_LEFT", false);
		}
		else if (pDir == eDirection::Right)
		{
			pAnimator->Play(L"WAKE_RIGHT", false);
		}
	}

}

void MWakeState::FinalTick()
{
	Time += DT;

	if (Time >= 1.f)
	{
		GetFSM()->ChangeState(L"Move");
	}
}

void MWakeState::Exit()
{
	Time = 0.f;
}

