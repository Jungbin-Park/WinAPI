#include "pch.h"
#include "CBoss.h"

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
#include "BIdleState.h"
#include "BJumpState.h"
#include "BDownState.h"
#include "BDeadState.h"



CBoss::CBoss()
	: m_Dead(false)
	, m_Down(false)
	, m_Ground(false)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetActive(true);
	m_Collider->SetOffsetPos(Vec2(0.f, 50.f));
	m_Collider->SetScale(Vec2(400.f, 400.f));

	// RigidBody
	m_RigidBody->SetMass(2.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(1500.f);

	// FSM
	m_FSM->AddState(L"Idle", new BIdleState);
	m_FSM->AddState(L"Jump", new BJumpState);
	m_FSM->AddState(L"Down", new BDownState);
	m_FSM->AddState(L"Dead", new BDeadState);
	
	// Animation
	/*
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"BossTex", L"texture\\Monster\\boss\\Boss_1\\boss_1.png");

	m_Animator->CreateAnimation(L"IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(395.f, 560.f), 1, 10);
	m_Animator->CreateAnimation(L"JUMP", pAtlas, Vec2(0.f, 0.f), Vec2(395.f, 560.f), 3, 10);
	m_Animator->CreateAnimation(L"DEAD", pAtlas, Vec2(1185.f, 0.f), Vec2(470.f, 560.f), 2, 1);
	m_Animator->CreateAnimation(L"DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(395.f, 560.f), 3, 10);

	m_Animator->FindAnimation(L"IDLE")->Save(L"animation\\boss\\");
	m_Animator->FindAnimation(L"JUMP")->Save(L"animation\\boss\\");
	m_Animator->FindAnimation(L"DEAD")->Save(L"animation\\boss\\");
	m_Animator->FindAnimation(L"DOWN")->Save(L"animation\\boss\\");

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"BossHitTex", L"texture\\Monster\\boss\\Boss_1\\boss_2.png");
	m_Animator->CreateAnimation(L"HIT", pAtlas, Vec2(0.f, 0.f), Vec2(395.f, 560.f), 1, 10);
	m_Animator->FindAnimation(L"HIT")->Save(L"animation\\boss\\");


	*/
	
	m_Animator->LoadAnimation(L"animation\\boss\\IDLE.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\JUMP.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\DOWN.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\DEAD.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\HIT.anim");
	

}

CBoss::~CBoss()
{
}



void CBoss::begin()
{
	m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	m_FSM->SetBlackboardData(L"Animator", DATA_TYPE::ANIMATOR, &m_Animator);

	m_FSM->ChangeState(L"Idle");

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CBoss::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CBoss::Air);
}

void CBoss::tick()
{
	CObj::tick();
}

void CBoss::Jump()
{
	m_Animator->Play(L"JUMP", false);

	Vec2 vGV = m_RigidBody->GetGravityVelocity();

	if (0.f < vGV.y)
		m_RigidBody->SetGravityVelocity(Vec2(0.f, 0.f));

	m_RigidBody->Jump();
}

void CBoss::Ground()
{
	m_Ground = true;
}

void CBoss::Air()
{
	m_Ground = false;
}

void CBoss::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	// 공격에 맞으면 텍스쳐 변환
	if (_OtherObj->GetName() == L"Snow")
	{
		CSnow* pSnow = dynamic_cast<CSnow*>(_OtherObj);
		m_Animator->Play(L"HIT", false);
	}
}

void CBoss::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CBoss::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}


