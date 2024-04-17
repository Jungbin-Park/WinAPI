#include "pch.h"
#include "CIdleState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "MRana.h"
#include "CAnimator.h"

static float Time = 0.f;

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	// ���� �Ĵٺ��� ���� ���� ���ϱ�
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");
	eDirection pDir = pSelf->GetDirection();
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	MRana* Rana = dynamic_cast<MRana*>(pSelf);
	CAnimator* pAnimator;

	Vec2 pPos = pPlayer->GetPos();
	Vec2 sPos = pSelf->GetPos();
	Vec2 vDir = pPos - sPos;

	if (pMon != nullptr)
	{
		pAnimator = pMon->GetAnimator();

		if (pMon->IsMonDead() != true)
		{
			// ���� �ȿ� ������ �÷��̾� �������� ���� ����
			if (pPlayer->GetPos().GetDistance(sPos) < Range)
			{
				if (vDir.x > 0.f)
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_RIGHT", false);
				}
				else if (vDir.x < 0.f)
				{
					pDir = eDirection::Left;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_LEFT", false);
				}
			}
			else
			{
				if (pDir == eDirection::Left)
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_LEFT", false);
				}
				else if (pDir == eDirection::Right)
				{
					pDir = eDirection::Left;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_RIGHT", false);
				}
				else
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE", false);
				}
			}
		}
	}
	else
	{
		pAnimator = Rana->GetAnimator();

		if (Rana->IsMonDead() != true)
		{
			// ���� �ȿ� ������ �÷��̾� �������� ���� ����
			if (pPlayer->GetPos().GetDistance(sPos) < Range)
			{
				if (vDir.x > 0.f)
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_RIGHT", false);
				}
				else if (vDir.x < 0.f)
				{
					pDir = eDirection::Left;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_LEFT", false);
				}
			}
			else
			{
				if (pDir == eDirection::Left)
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_LEFT", false);
				}
				else if (pDir == eDirection::Right)
				{
					pDir = eDirection::Left;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE_RIGHT", false);
				}
				else
				{
					pDir = eDirection::Right;
					pSelf->SetDirection(pDir);
					pAnimator->Play(L"IDLE", false);
				}
			}
		}
	}
	
	
	
	
}

void CIdleState::FinalTick()
{
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CMonster* pMon = dynamic_cast<CMonster*>(pSelf);
	MRana* Rana = dynamic_cast<MRana*>(pSelf);

	// ������ Ž�� ������ �ð�ȭ
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetPos(), Vec2(Range * 2.f, Range * 2.f), 0);

	if (pMon != nullptr)
	{
		// 2�ʰ� ���� �� Move ���·� ��ȯ
		if (pMon->IsMonDead() != true)
		{
			Time += DT;
			if (Time >= 2.f)
			{
				GetFSM()->ChangeState(L"Move");
			}
		}
	}
	else
	{
		if (Rana->IsMonDead() != true)
		{
			Time += DT;
			if (Time >= 2.f)
			{
				GetFSM()->ChangeState(L"Move");
			}
		}
	}
	
	
}

void CIdleState::Exit()
{
	Time = 0.f;
}



