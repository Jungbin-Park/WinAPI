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
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();
	eDirection pDir = pMBoss->GetDirection();

	if (pDir == eDirection::Left)
		pAnimator->Play(L"WALK_LEFT", true);
	else if (pDir == eDirection::Right)
		pAnimator->Play(L"WALK_RIGHT", true);
}

void MMoveState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	float Speed = GetBlackboardData<float>(L"Speed");

	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();
	eDirection pDir = pMBoss->GetDirection();
	
	Vec2 vPos = pSelf->GetPos();

	if (pMBoss->IsMonDead() != true)
	{
		Time += DT;

		if (pDir == eDirection::Left)
		{
			if (pMBoss->IsGround() && !pMBoss->IsStopLeft())
				vPos.x -= Speed * DT;

			pSelf->SetPos(vPos);
		}
		else if (pDir == eDirection::Right)
		{
			if (pMBoss->IsGround() && !pMBoss->IsStopRight())
				vPos.x += Speed * DT;

			pSelf->SetPos(vPos);
		}

		if (Time >= 2.f)
		{
			GetFSM()->ChangeState(L"Ball");
		}
	}

	

}

void MMoveState::Exit()
{
	Time = 0.f;
}



