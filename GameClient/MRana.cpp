#include "pch.h"
#include "MRana.h"

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
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CMoveState.h"
#include "CSnowState.h"
#include "CJumpState.h"

MRana::MRana()
	: m_DetectRange(300)
	, m_Speed(300)
	, m_Dead(false)
	, m_bSnow(false)
	, m_Ground(false)
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
	m_Collider->SetScale(Vec2(100.f, 120.f));

	// FSM
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
	m_FSM->AddState(L"Attack", new CAttackState);
	m_FSM->AddState(L"Dead", new CDeadState);
	m_FSM->AddState(L"Move", new CMoveState);
	m_FSM->AddState(L"Snow", new CSnowState);
	m_FSM->AddState(L"Jump", new CJumpState);


	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"RanaLeftTex", L"texture\\Monster\\Enemy\\Rana_Left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"RanaRightTex", L"texture\\Monster\\Enemy\\Rana_Right.png");

	/*m_Animator->CreateAnimation(L"IDLE", pAtlasL, Vec2(0.f, 800.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 800.f), Vec2(160.f, 160.f), 2, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(320.f, 800.f), Vec2(160.f, 160.f), 2, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"FIRE_LEFT", pAtlasL, Vec2(0.f, 160.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"FIRE_RIGHT", pAtlasR, Vec2(480.f, 160.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_LEFT", pAtlasL, Vec2(0.f, 1180.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_RIGHT", pAtlasR, Vec2(480.f, 1180.f), Vec2(160.f, 160.f), 1, 10);

	m_Animator->CreateAnimation(L"STRUGGLE", pAtlasL, Vec2(0.f, 320.f), Vec2(160.f, 160.f), 2, 10);
	m_Animator->CreateAnimation(L"SHAKE", pAtlasL, Vec2(0.f, 960.f), Vec2(160.f, 160.f), 2, 10);
	m_Animator->CreateAnimation(L"DEAD", pAtlasL, Vec2(0.f, 1280.f), Vec2(160.f, 160.f), 7, 10);

	m_Animator->FindAnimation(L"IDLE")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"FIRE_LEFT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"FIRE_RIGHT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"AIR_LEFT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"AIR_RIGHT")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"STRUGGLE")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"SHAKE")->Save(L"animation\\monster2\\");
	m_Animator->FindAnimation(L"DEAD")->Save(L"animation\\monster2\\");*/

	m_Animator->LoadAnimation(L"animation\\monster2\\IDLE.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\FIRE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\FIRE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\AIR_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\AIR_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\STRUGGLE.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\SHAKE.anim");
	m_Animator->LoadAnimation(L"animation\\monster2\\DEAD.anim");

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
}

MRana::MRana(Vec2(_Pos), Vec2(_Scale))
{
}

MRana::~MRana()
{
}

void MRana::begin()
{
	// 블랙보드 추가는 프레임마다 호출하는 대신 begin() 쪽에다가
	m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &m_DetectRange);
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_Speed);
	m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	m_FSM->SetBlackboardData(L"IsSnow", DATA_TYPE::BOOL, &m_bSnow);


	// 플레이어를 타겟으로 설정해서 블랙보드에 추가
	CObj* pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pPlayer);

	m_FSM->ChangeState(L"Idle");

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&MRana::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&MRana::Air);
	m_RigidBody->SetWallDelegate(this, (DELEGATE)&MRana::SetWall);
	m_RigidBody->SetWallOffDelegate(this, (DELEGATE)&MRana::SetWallOff);
}

void MRana::tick()
{
	CObj::tick();

	// 애니메이션 끝났을 때
	if (m_Animator->GetCurAnim()->IsFinish())
	{
		if (m_Animator->GetCurAnim()->GetName() == L"DEAD")
		{
			CLevel_Stage01* curLevel = dynamic_cast<CLevel_Stage01*>(CLevelMgr::GetInst()->GetCurrentLevel());
			curLevel->AddScore(1);
			GetFSM()->GetOwner()->Dead(true);
		}
	}
}

void MRana::Jump()
{
}

void MRana::Ground()
{
	m_Ground = true;
}

void MRana::Air()
{
	m_Ground = false;
}

void MRana::SetWall()
{
	if (GetDirection() == eDirection::Left)
	{
		m_StopLeft = true;
	}
	else if (GetDirection() == eDirection::Right)
	{
		m_StopRight = true;
	}
}

void MRana::SetWallOff()
{
	m_StopLeft = false;
	m_StopRight = false;
}

void MRana::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	if (_OtherObj->GetName() == L"Snow")
	{
		CSnow* pSnow = dynamic_cast<CSnow*>(_OtherObj);
		if (!m_bSnow)
		{
			CSnowObj* pObject = new CSnowObj;
			pObject->SetName(L"SnowObj");
			pObject->SetPos(GetPos() + Vec2(0.f, -20.f));
			pObject->SetScale(120.f, 120.f);
			pObject->SetOwner(this);
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(LAYER_TYPE::SNOW, pObject);
		}
		m_bSnow = true;
		m_FSM->ChangeState(L"Snow");
	}

	if (_OtherObj->GetName() == L"Wall")
	{
		m_Wall = true;
		m_FSM->ChangeState(L"Idle");
	}

	if (_OtherObj->GetName() == L"SnowObj")
	{
		CSnowObj* pSnowObj = dynamic_cast<CSnowObj*>(_OtherObj);

		if (pSnowObj->GetOwner() != this && pSnowObj->IsRoll() && !m_bSnow)
		{
			// 날아감
			m_Dead = true;
			if (GetPos().x < pSnowObj->GetPos().x)
			{
				m_RigidBody->Jump(Vec2(-0.5f, -1.f));
			}
			else
			{
				m_RigidBody->Jump(Vec2(0.5f, -1.f));
			}

			m_FSM->ChangeState(L"Dead");
		}
	}
}

void MRana::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void MRana::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Wall")
	{
		m_Wall = false;
	}
}


