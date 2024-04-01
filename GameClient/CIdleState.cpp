#include "pch.h"
#include "CIdleState.h"

#include "CFSM.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::FinalTick()
{
	// 근처(탐지 범위)에 플레이어가 있는지 탐색
	// float fRange = GetBlackboardData(L"DetectRange");
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	// 몬스터의 탐지 범위를 시각화
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetPos(), Vec2(Range * 2.f, Range * 2.f), 0);
	

	// 플레이어가 탐지되면 Trace 상태로 변경
	if (pPlayer->GetPos().GetDistance(pSelf->GetPos()) < Range)
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void CIdleState::Exit()
{
}



