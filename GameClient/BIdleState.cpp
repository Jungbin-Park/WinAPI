#include "pch.h"
#include "BIdleState.h"

#include "CFSM.h"
#include "CBoss.h"
#include "CAnimator.h"

static float Time = 0.f;

BIdleState::BIdleState()
{
	
}

BIdleState::~BIdleState()
{
}

void BIdleState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	pAnimator->Play(L"IDLE", true);
}

void BIdleState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	Time += DT;

	if (Time >= 3.f)
	{
		if (pBoss->IsDown())
		{
			// 위로 점프
			GetFSM()->ChangeState(L"Jump");
		}
		else
		{
			// 아래로 점프
			GetFSM()->ChangeState(L"Down");
		}

	}
}

void BIdleState::Exit()
{
	Time = 0.f;
}


