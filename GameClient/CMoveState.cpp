#include "pch.h"
#include "CMoveState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "MRana.h"
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
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");
	eDirection pDir = pSelf->GetDirection();
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	MRana* Rana = dynamic_cast<MRana*>(pSelf);
	CAnimator* pAnimator;

	if (pMon != nullptr)
	{
		pAnimator = pMon->GetAnimator();
	}
	else
	{
		pAnimator = Rana->GetAnimator();
	}

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
	float Speed = GetBlackboardData<float>(L"Speed");

	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	MRana* Rana = dynamic_cast<MRana*>(pSelf);
	eDirection pDir = pSelf->GetDirection();
	Vec2 vPos = pSelf->GetPos();

	if (pMon != nullptr)
	{
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
	else
	{
		if (Rana->IsMonDead() != true)
		{
			Time += DT;

			// 몬스터의 탐지 범위를 시각화
			DrawDebugCircle(PEN_TYPE::PEN_GREEN, vPos, Vec2(Range * 2.f, Range * 2.f), 0);

			if (pDir == eDirection::Right)
			{
				if (Rana->IsGround() && !Rana->IsStopRight())
					vPos.x += Speed * DT;

				pSelf->SetPos(vPos);
			}
			else if (pDir == eDirection::Left)
			{
				if (Rana->IsGround() && !Rana->IsStopLeft())
					vPos.x -= Speed * DT;

				pSelf->SetPos(vPos);
			}


			if (Time >= 2.f)
			{
				GetFSM()->ChangeState(L"Attack");
				Time = 0.f;
			}
		}
	}

	
}

void CMoveState::Exit()
{
}



