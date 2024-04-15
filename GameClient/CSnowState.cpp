#include "pch.h"
#include "CSnowState.h"

#include "CMonster.h"
#include "CAnimator.h"

CSnowState::CSnowState()
{
}

CSnowState::~CSnowState()
{
}

void CSnowState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();

	pAnimator->Play(L"STRUGGLE", true);
}

void CSnowState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();

	bool IsSnow = GetBlackboardData<bool>(L"IsSnow");

	if (!IsSnow)
	{
		GetFSM()->ChangeState(L"Idle");
	}
		

}

void CSnowState::Exit()
{
}



