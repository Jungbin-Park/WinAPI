#include "pch.h"
#include "BDownState.h"

#include "CLevelMgr.h"

#include "CBoss.h"
#include "CMiniBoss.h"

#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

static float Time = 0.f;



BDownState::BDownState()
	: m_bShoot1(true)
	, m_bShoot2(true)
	, m_bShoot3(true)
{
}

BDownState::~BDownState()
{
}

void BDownState::Enter()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CBoss* pBoss = dynamic_cast<CBoss*>(pSelf);
	CAnimator* pAnimator = pBoss->GetAnimator();
	CRigidBody* pRigidbody = pBoss->GetRigidBody();

	pBoss->SetDown(true);

	pAnimator->Play(L"DOWN", false);
	pRigidbody->SetGround(false);

	m_bShoot1 = true;
	m_bShoot2 = true;
	m_bShoot3 = true;
}

void BDownState::FinalTick()
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

	if (Time >= 1.f)
	{
		GetFSM()->ChangeState(L"Idle");
	}
}

void BDownState::Exit()
{
	Time = 0.f;
}

void BDownState::Shoot()
{
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");

	// 미니 보스 소환
	CMiniBoss* pMBoss = new CMiniBoss;
	pMBoss->SetName(L"MiniBoss");

	Vec2 vMBossPos = pSelf->GetPos();
	vMBossPos.x -= pSelf->GetScale().x / 2.f;

	pMBoss->SetPos(vMBossPos);
	pMBoss->SetScale(Vec2(95.f, 95.f));

	pMBoss->GetRigidBody()->SetMissileSpeed(1500.f);
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER, pMBoss);
	pMBoss->GetRigidBody()->Shoot(Vec2(-10.f, 0.0f));
}
