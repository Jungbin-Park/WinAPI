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
#include "MBallState.h"
#include "MMoveState.h"
#include "MWakeState.h"
#include "MSnowState.h"

CMiniBoss::CMiniBoss()
	: m_Speed(300)
	, m_Dead(false)
	, m_bSnow(false)
	, m_Ground(false)
	, m_Direction(eDirection::Left)
	, m_StopLeft(false)
	, m_StopRight(false)
	, m_Wall(false)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(95.f, 95.f));

	// FSM
	m_FSM->AddState(L"Wake", new MWakeState);
	m_FSM->AddState(L"Ball", new MBallState);
	m_FSM->AddState(L"Move", new MMoveState);
	m_FSM->AddState(L"Snow", new MSnowState);

	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"MiniLeftTex", L"texture\\Monster\\boss\\Boss_1\\miniboss_left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"MiniRightTex", L"texture\\Monster\\boss\\Boss_1\\miniboss_right.png");

	/*m_Animator->CreateAnimation(L"SHOOT", pAtlasL, Vec2(0.f, 0.f), Vec2(97.f, 97.f), 1, 10);
	m_Animator->CreateAnimation(L"BALL_LEFT", pAtlasL, Vec2(97.f, 0.f), Vec2(97.f, 97.f), 4, 10);
	m_Animator->CreateAnimation(L"BALL_RIGHT", pAtlasR, Vec2(194.f, 0.f), Vec2(97.f, 97.f), 4, 10);
	m_Animator->CreateAnimation(L"WAKE_LEFT", pAtlasL, Vec2(97.f, 0.f), Vec2(97.f, 97.f), 4, 10);
	m_Animator->CreateAnimation(L"WAKE_RIGHT", pAtlasR, Vec2(194.f, 0.f), Vec2(97.f, 97.f), 4, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(485.f, 0.f), Vec2(97.f, 97.f), 2, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(0.f, 0.f), Vec2(97.f, 97.f), 2, 10);

	m_Animator->FindAnimation(L"SHOOT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"BALL_LEFT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"BALL_RIGHT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"WAKE_LEFT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"WAKE_RIGHT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\miniboss\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\miniboss\\");*/

	m_Animator->LoadAnimation(L"animation\\miniboss\\SHOOT.anim");

	m_Animator->LoadAnimation(L"animation\\miniboss\\BALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\miniboss\\BALL_RIGHT.anim");

	m_Animator->LoadAnimation(L"animation\\miniboss\\WAKE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\miniboss\\WAKE_RIGHT.anim");

	m_Animator->LoadAnimation(L"animation\\miniboss\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\miniboss\\WALK_RIGHT.anim");

	// Rigidbody 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(700.f);
	m_RigidBody->SetMaxWalkSpeed(1500.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
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
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_Speed);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CMiniBoss::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CMiniBoss::Air);
	m_RigidBody->SetWallDelegate(this, (DELEGATE)&CMiniBoss::SetWall);
	m_RigidBody->SetWallOffDelegate(this, (DELEGATE)&CMiniBoss::SetWallOff);
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

void CMiniBoss::SetWall()
{
	if (m_Direction == eDirection::Left)
	{
		m_StopLeft = true;
	}
	else if (m_Direction == eDirection::Right)
	{
		m_StopRight = true;
	}
}

void CMiniBoss::SetWallOff()
{
	m_StopLeft = false;
	m_StopRight = false;
}

void CMiniBoss::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{

	if (_OtherObj->GetName() == L"Wall")
	{
		m_Wall = true;
		m_FSM->ChangeState(L"Ball");
	}

	if (_OtherObj->GetName() == L"Snow")
	{
		CSnow* pSnow = dynamic_cast<CSnow*>(_OtherObj);
		if (!m_bSnow)
		{
			CSnowObj* pObject = new CSnowObj;
			pObject->SetName(L"SnowObj");
			pObject->SetPos(GetPos() + Vec2(0.f, -30.f));
			pObject->SetScale(120.f, 120.f);
			pObject->SetOwner(this);
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(LAYER_TYPE::SNOW, pObject);
		}
		m_bSnow = true;
		m_FSM->ChangeState(L"Snow");
	}

	if (_OtherObj->GetName() == L"SnowObj")
	{
		CSnowObj* pSnowObj = dynamic_cast<CSnowObj*>(_OtherObj);

		if (pSnowObj->GetOwner() != this && pSnowObj->IsRoll() && !m_bSnow)
		{
			Destroy();
		}
	}
}

void CMiniBoss::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CMiniBoss::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Wall")
	{
		m_Wall = false;
	}
}

