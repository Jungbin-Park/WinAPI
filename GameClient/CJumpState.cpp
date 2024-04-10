#include "pch.h"
#include "CJumpState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "CAnimator.h"

CJumpState::CJumpState()
{
}

CJumpState::~CJumpState()
{
}

void CJumpState::Enter()
{
	// 점프 준비 애니메이션 
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();
	eDirection pDir = pMon->GetDirection();

	if (pDir == eDirection::Left)
	{
		pAnimator->Play(L"JUMPREADY_LEFT", false);
	}
	else if (pDir == eDirection::Right)
	{
		pAnimator->Play(L"JUMPREADY_RIGHT", false);
	}
}

void CJumpState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();

	float Time = 0.f;
	Time += DT;

	if (Time >= 1.f)
	{
		pMon->Jump();
		Time = 0.f;
		GetFSM()->ChangeState(L"Move");
	}
}

void CJumpState::Exit()
{
}


