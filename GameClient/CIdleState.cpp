#include "pch.h"
#include "CIdleState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "CAnimator.h"

static float Time = 0.f;

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	// 앞을 쳐다보고 다음 방향 정하기
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();
	eDirection pDir = pMon->GetDirection();

	Vec2 pPos = pPlayer->GetPos();
	Vec2 sPos = pSelf->GetPos();

	Vec2 vDir = pPos - sPos;

	if (pMon->IsMonDead() != true)
	{
		// 범위 안에 들어오면 플레이어 방향으로 방향 변경
		if (pPlayer->GetPos().GetDistance(sPos) < Range)
		{
			if (vDir.x > 0.f)
			{
				pDir = eDirection::Right;
				pMon->SetDirection(pDir);
				pAnimator->Play(L"IDLE_RIGHT", false);
			}
			else if (vDir.x < 0.f)
			{
				pDir = eDirection::Left;
				pMon->SetDirection(pDir);
				pAnimator->Play(L"IDLE_LEFT", false);
			}
		}
		else
		{
			if (pDir == eDirection::Left)
			{
				pDir = eDirection::Right;
				pMon->SetDirection(pDir);
				pAnimator->Play(L"IDLE_LEFT", false);
			}
			else if (pDir == eDirection::Right)
			{
				pDir = eDirection::Left;
				pMon->SetDirection(pDir);
				pAnimator->Play(L"IDLE_RIGHT", false);
			}
			else
			{
				pDir = eDirection::Right;
				pMon->SetDirection(pDir);
				pAnimator->Play(L"IDLE", false);
			}
		}
	}
	
}

void CIdleState::FinalTick()
{
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);

	// 몬스터의 탐지 범위를 시각화
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetPos(), Vec2(Range * 2.f, Range * 2.f), 0);

	// 2초가 지난 후 Move 상태로 전환
	if (pMon->IsMonDead() != true)
	{
		Time += DT;
		if (Time >= 2.f)
		{
			GetFSM()->ChangeState(L"Move");
		}
	}
	
}

void CIdleState::Exit()
{
	Time = 0.f;
}



