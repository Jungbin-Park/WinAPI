#include "pch.h"
#include "CAttackState.h"

#include "CFSM.h"
#include "CMonster.h"
#include "MRana.h"
#include "CMonsterMissile.h"

#include "CAnimator.h"
#include "CLevelMgr.h"

static float Time = 0.f;

CAttackState::CAttackState()
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	MRana* Rana = dynamic_cast<MRana*>(pSelf);
	CAnimator* pAnimator = Rana->GetAnimator();
	eDirection pDir = pSelf->GetDirection();
	Vec2 vPos = pSelf->GetPos();

	CMonsterMissile* pMissile = new CMonsterMissile;
	pMissile->SetName(L"MonsterMissile");

	Vec2 mPos = vPos;

	if (pDir == eDirection::Left)
	{
		pAnimator->Play(L"FIRE_LEFT", false);
		mPos.x -= pSelf->GetScale().x * 0.5f;
		pMissile->SetPos(mPos);
		pMissile->SetDirection(eDirection::Left);
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pMissile);
	}
	else
	{
		pAnimator->Play(L"FIRE_RIGHT", false);
		mPos.x += pSelf->GetScale().x * 0.5f;
		pMissile->SetPos(mPos);
		pMissile->SetDirection(eDirection::Right);
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pMissile);
	}
	
}

void CAttackState::FinalTick()
{
	Time += DT;

	if (Time >= 2.f)
		GetFSM()->ChangeState(L"Idle");
}

void CAttackState::Exit()
{
	Time = 0.f;
}



