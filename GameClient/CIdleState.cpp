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
	// ��ó(Ž�� ����)�� �÷��̾ �ִ��� Ž��
	// float fRange = GetBlackboardData(L"DetectRange");
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj& pSelf = GetBlackboardData<CObj>(L"Self");


	// �÷��̾ Ž���Ǹ� Trace ���·� ����
}

void CIdleState::Exit()
{
}



