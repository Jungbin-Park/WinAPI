#include "pch.h"
#include "CTraceState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "CAnimator.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	CAnimator* pAnimator = pMon->GetAnimator();
	eDirection pDir = pMon->GetDirection();

	Vec2 pPos = pPlayer->GetPos();
	Vec2 sPos = pSelf->GetPos();

	Vec2 vDir = pPos - sPos;

	// 플레이어를 향해 방향만 설정

	if (vDir.x > 0.f)
	{
		pDir = eDirection::Right;
		pMon->SetDirection(pDir);
	}
	else if (vDir.x < 0.f)
	{
		pDir = eDirection::Left;
		pMon->SetDirection(pDir);
	}
	
}

void CTraceState::FinalTick()
{
	//float Time = 0.f;
	//Time += DT;

	//float Range = GetBlackboardData<float>(L"DetectRange");
	//float Speed = GetBlackboardData<float>(L"Speed");
	//CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	//CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");
	//CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	//CAnimator* pAnimator = pMon->GetAnimator();

	//Vec2 pPos = pPlayer->GetPos();
	//Vec2 sPos = pSelf->GetPos();

	//// 플레이어를 추적
	//Vec2 vDir = pPos - sPos;

	//if (!vDir.IsZero())
	//{
	//	vDir.Normalize();

	//	if(pMon->IsGround())
	//		sPos.x += (vDir.x * Speed * DT);
	//	
	//	pSelf->SetPos(sPos);

	//	if (sPos.y - pPos.y > 150.f)
	//	{
	//		if (pMon->IsGround())
	//			GetFSM()->ChangeState(L"Jump");
	//	}
	//}

	//// Range 벗어나면 Idle
	//if (pPlayer->GetPos().GetDistance(sPos) > Range)
	//{
	//	GetFSM()->ChangeState(L"Idle");
	//}
	///*if (Time >= 2.f)
	//{
	//	GetFSM()->ChangeState(L"Idle");
	//}*/
	
}

void CTraceState::Exit()
{
}



