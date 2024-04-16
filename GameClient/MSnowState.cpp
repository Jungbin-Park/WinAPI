#include "pch.h"
#include "MSnowState.h"

#include "CFSM.h"
#include "CMiniBoss.h"
#include "CAnimator.h"

MSnowState::MSnowState()
{
}

MSnowState::~MSnowState()
{
}

void MSnowState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();

	pAnimator->Play(L"SHOOT", true);
}

void MSnowState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMiniBoss* pMBoss = dynamic_cast<CMiniBoss*>(pSelf);
	CAnimator* pAnimator = pMBoss->GetAnimator();

	bool IsSnow = GetBlackboardData<bool>(L"IsSnow");

	if (!IsSnow)
	{
		GetFSM()->ChangeState(L"Wake");
	}
}

void MSnowState::Exit()
{
}



