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
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	// ������ Ž�� ������ �ð�ȭ
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetPos(), Vec2(Range * 2.f, Range * 2.f), 0);
	

	// �÷��̾ Ž���Ǹ� Trace ���·� ����
	if (pPlayer->GetPos().GetDistance(pSelf->GetPos()) < Range)
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void CIdleState::Exit()
{
}



