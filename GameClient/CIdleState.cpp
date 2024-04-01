#include "pch.h"
#include "CIdleState.h"

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


	// 플레이어가 탐지되면 Trace 상태로 변경
}

void CIdleState::Exit()
{
}



