#include "pch.h"
#include "BJumpState.h"

#include "CLevelMgr.h"

#include "CBoss.h"
#include "CMiniBoss.h"

#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

static float Time = 0.f;

BJumpState::BJumpState()
	: m_bShoot1(true)
	, m_bShoot2(true)
	, m_bShoot3(true)
{
}

BJumpState::~BJumpState()
{
}

void BJumpState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();
	CRigidBody* pRigidbody = pBoss->GetRigidBody();

	pBoss->SetDown(false);

	pAnimator->Play(L"JUMP", false);
	pRigidbody->Jump();

	m_bShoot1 = true;
	m_bShoot2 = true;
	m_bShoot3 = true;
}

void BJumpState::FinalTick()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();

	Time += DT;

	if (pAnimator->GetCurAnim()->GetCurFrame() == 0)
	{
		if (m_bShoot1)
		{
			Shoot();
			m_bShoot1 = false;
		}
	}
	else if (pAnimator->GetCurAnim()->GetCurFrame() == 1)
	{
		if (m_bShoot2)
		{
			Shoot();
			m_bShoot2 = false;
		}

	}
	else if (pAnimator->GetCurAnim()->GetCurFrame() == 2)
	{
		if (m_bShoot3)
		{
			Shoot();
			m_bShoot3 = false;
		}
	}

	if (Time >= 3.f)
	{
		GetFSM()->ChangeState(L"Idle");
	}
}

void BJumpState::Exit()
{
	Time = 0.f;
}

void BJumpState::Shoot()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");

	// 미니 보스 소환
	CMiniBoss* pMBoss = new CMiniBoss;
	pMBoss->SetName(L"MiniBoss");

	Vec2 vMBossPos = pSelf->GetPos();
	vMBossPos.x -= pSelf->GetScale().x / 2.f;

	pMBoss->SetPos(vMBossPos);
	pMBoss->SetScale(Vec2(30.f, 40.f));

	pMBoss->GetRigidBody()->SetMissileSpeed(1500.f);
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER, pMBoss);
	pMBoss->GetRigidBody()->Shoot(Vec2(-1.f, 0.0f));
}



