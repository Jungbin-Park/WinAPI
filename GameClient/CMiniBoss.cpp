#include "pch.h"
#include "CMiniBoss.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

#include "CSnow.h"
#include "CSnowObj.h"

#include "CFSM.h"
#include "MIdleState.h"
#include "MMoveState.h"

CMiniBoss::CMiniBoss()
	: m_Speed(300)
	, m_Dead(false)
	, m_bSnow(false)
	, m_Ground(false)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(95.f, 95.f));


	// FSM
	m_FSM->AddState(L"Idle", new MIdleState);
	m_FSM->AddState(L"Move", new MMoveState);

	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"MiniLeftTex", L"texture\\Monster\\boss\\Boss_1\\miniboss_left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"MiniRightTex", L"texture\\Monster\\boss\\Boss_1\\miniboss_right.png");

	m_Animator->CreateAnimation(L"SHOOT", pAtlasL, Vec2(0.f, 0.f), Vec2(97.f, 97.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE", pAtlasL, Vec2(97.f, 0.f), Vec2(97.f, 97.f), 4, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(485.f, 0.f), Vec2(97.f, 97.f), 2, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(0.f, 0.f), Vec2(97.f, 97.f), 2, 10);

	m_Animator->FindAnimation(L"SHOOT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"IDLE")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\monster\\");

	// Rigidbody 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);
	m_RigidBody->SetMissileSpeed(1000.f);

	m_Animator->Play(L"SHOOT", false);
}

CMiniBoss::CMiniBoss(Vec2(_Pos), Vec2(_Scale))
	: m_Speed(300)
	, m_Dead(false)
	, m_bSnow(false)
	, m_Ground(false)
{

}

CMiniBoss::~CMiniBoss()
{

}

void CMiniBoss::begin()
{
	m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	m_FSM->SetBlackboardData(L"IsSnow", DATA_TYPE::BOOL, &m_bSnow);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CMiniBoss::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CMiniBoss::Air);
}

void CMiniBoss::tick()
{
	CObj::tick();
}


void CMiniBoss::Ground()
{
	m_Ground = true;
}

void CMiniBoss::Air()
{
	m_Ground = false;
}

void CMiniBoss::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	m_FSM->ChangeState(L"Idle");
}

void CMiniBoss::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CMiniBoss::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

