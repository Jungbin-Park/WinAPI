#include "pch.h"
#include "CMoveState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "CAnimator.h"

CMoveState::CMoveState()
{
}

CMoveState::~CMoveState()
{
}

void CMoveState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();
	eDirection pDir = pMon->GetDirection();

	if (pDir == eDirection::Right)
		pAnimator->Play(L"WALK_RIGHT", true);
	else if (pDir == eDirection::Left)
		pAnimator->Play(L"WALK_LEFT", true);
	
}

void CMoveState::FinalTick()
{
	static float Time = 0.f;

	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");
	float Speed = GetBlackboardData<float>(L"Speed");

	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	eDirection pDir = pMon->GetDirection();
	Vec2 vPos = pSelf->GetPos();

	if (pMon->IsMonDead() != true)
	{
		Time += DT;

		// 몬스터의 탐지 범위를 시각화
		DrawDebugCircle(PEN_TYPE::PEN_GREEN, vPos, Vec2(Range * 2.f, Range * 2.f), 0);

		if (pDir == eDirection::Right)
		{
			if (pMon->IsGround() && !pMon->IsStopRight())
				vPos.x += Speed * DT;

			pSelf->SetPos(vPos);
		}
		else if (pDir == eDirection::Left)
		{
			if (pMon->IsGround() && !pMon->IsStopLeft())
				vPos.x -= Speed * DT;

			pSelf->SetPos(vPos);
		}


		if (Time >= 2.f)
		{
			GetFSM()->ChangeState(L"Idle");
			Time = 0.f;
		}
	}
}

void CMoveState::Exit()
{
}



