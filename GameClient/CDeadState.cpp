#include "pch.h"
#include "CDeadState.h"

#include "CLevel_Stage01.h"
#include "CLevelMgr.h"

#include "CFSM.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

CDeadState::CDeadState()
{
}

CDeadState::~CDeadState()
{
}


void CDeadState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();

	pAnimator->Play(L"DEAD", false);
}

void CDeadState::FinalTick()
{

}

void CDeadState::Exit()
{
}



