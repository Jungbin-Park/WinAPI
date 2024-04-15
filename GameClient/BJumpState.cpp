#include "pch.h"
#include "BJumpState.h"

#include "CFSM.h"
#include "CBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

static float Time = 0.f;

BJumpState::BJumpState()
{
}

BJumpState::~BJumpState()
{
}

void BJumpState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();
	CRigidBody* pRigidbody = pBoss->GetRigidBody();

	pBoss->SetDown(false);

	pAnimator->Play(L"JUMP", false);
	pRigidbody->Jump();
}

void BJumpState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	Time += DT;

	if (pAnimator->GetCurAnim()->GetCurFrame() == 0)
	{
		// 미니 보스 소환

	}
	else if (pAnimator->GetCurAnim()->GetCurFrame() == 1)
	{
		// 미니 보스 소환

	}
	else if (pAnimator->GetCurAnim()->GetCurFrame() == 2)
	{
		// 미니 보스 소환

	}

	if (Time >= 3.f)
	{
		GetFSM()->ChangeState(L"Idle");
	}
}

void BJumpState::Exit()
{
	Time = 0.f;
}



