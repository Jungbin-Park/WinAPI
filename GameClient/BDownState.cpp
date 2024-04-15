#include "pch.h"
#include "BDownState.h"

#include "CFSM.h"
#include "CBoss.h"
#include "CMiniBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

static float Time = 0.f;

BDownState::BDownState()
{
}

BDownState::~BDownState()
{
}

void BDownState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();
	CRigidBody* pRigidbody = pBoss->GetRigidBody();

	pBoss->SetDown(true);

	pAnimator->Play(L"DOWN", false);
	pRigidbody->SetGround(false);
}

void BDownState::FinalTick()
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

	if (Time >= 1.f)
	{
		GetFSM()->ChangeState(L"Idle");
	}
}

void BDownState::Exit()
{
	Time = 0.f;
}


