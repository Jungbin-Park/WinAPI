#include "pch.h"
#include "CSnowState.h"

#include "CMonster.h"
#include "MRana.h"
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

	pAnimator->Play(L"STRUGGLE", true);
}

void CSnowState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
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

	bool IsSnow = GetBlackboardData<bool>(L"IsSnow");

	if (!IsSnow)
	{
		GetFSM()->ChangeState(L"Idle");
	}
		

}

void CSnowState::Exit()
{
}



