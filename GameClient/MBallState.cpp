#include "pch.h"
#include "MBallState.h"

#include "CFSM.h"
#include "CMiniBoss.h"
#include "CAnimator.h"

static float Time = 0.f;

MBallState::MBallState()
{
}

MBallState::~MBallState()
{
}

void MBallState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();
	eDirection pDir = pMBoss->GetDirection();

	if (pMBoss->IsMonDead() != true)
	{
		if (pDir == eDirection::Left)
		{
			pDir = eDirection::Right;
			pMBoss->SetDirection(pDir);
			pAnimator->Play(L"BALL_LEFT", false);
		}
		else if (pDir == eDirection::Right)
		{
			pDir = eDirection::Left;
			pMBoss->SetDirection(pDir);
			pAnimator->Play(L"BALL_RIGHT", false);
		}
	}
}

void MBallState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();

	Time += DT;

	if (Time >= 1.f)
	{
		GetFSM()->ChangeState(L"Wake");
	}
}

void MBallState::Exit()
{
	Time = 0.f;
}



