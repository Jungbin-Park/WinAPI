#include "pch.h"
#include "CTraceState.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::FinalTick()
{
	float Range = GetBlackboardData<float>(L"DetectRange");
	float Speed = GetBlackboardData<float>(L"Speed");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	// 플레이어를 추적
	Vec2 vDir = pPlayer->GetPos() - pSelf->GetPos();
	if (!vDir.IsZero())
	{
		vDir.Normalize();
		Vec2 vPos = pSelf->GetPos() + (vDir * Speed * DT);
		pSelf->SetPos(vPos);
	}
	
}

void CTraceState::Exit()
{
}



