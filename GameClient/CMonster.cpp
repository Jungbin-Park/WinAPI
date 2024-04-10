#include "pch.h"
#include "CMonster.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

#include "CSnow.h"

#include "CFSM.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CMoveState.h"
#include "CSnowState.h"
#include "CJumpState.h"



CMonster::CMonster()
	: m_HP(5)
	, m_DetectRange(300)
	, m_Speed(300)
	, m_bDead(false)
	, m_Ground(false)
	, m_Direction(eDirection::None)
	, m_StopLeft(false)
	, m_StopRight(false)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(100.f, 120.f));
	

	// RigidBody
	m_RigidBody->SetMass(2.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);


	// FSM
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
	m_FSM->AddState(L"Attack", new CAttackState);
	m_FSM->AddState(L"Dead", new CDeadState);
	m_FSM->AddState(L"Move", new CMoveState);
	m_FSM->AddState(L"Snow", new CSnowState);
	m_FSM->AddState(L"Jump", new CJumpState);


	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"MonsterLeftTex", L"texture\\Monster\\Enemy\\Demonio_Left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"MonsterRightTex", L"texture\\Monster\\Enemy\\Demonio_Right.png");

	/*m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"JUMP_LEFT", pAtlasL, Vec2(160.f, 320.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"JUMP_RIGHT", pAtlasR, Vec2(480.f, 320.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_LEFT", pAtlasL, Vec2(320.f, 320.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_RIGHT", pAtlasR, Vec2(320.f, 320.f), Vec2(160.f, 160.f), 1, 10);

	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"AIR_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"AIR_RIGHT")->Save(L"animation\\monster\\");
	*/
	
	m_Animator->CreateAnimation(L"JUMPREADY_LEFT", pAtlasL, Vec2(480.f, 320.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"JUMPREADY_RIGHT", pAtlasR, Vec2(160.f, 320.f), Vec2(160.f, 160.f), 1, 10);

	m_Animator->FindAnimation(L"JUMPREADY_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"JUMPREADY_RIGHT")->Save(L"animation\\monster\\");

	m_Animator->LoadAnimation(L"animation\\monster\\IDLE.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\AIR_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\AIR_RIGHT.anim");

	//m_Animator->Play(L"IDLE_RIGHT", true);

	// Rigidbody 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);

}

CMonster::CMonster(Vec2(_Pos), Vec2(_Scale))
	: m_HP(5)
	, m_DetectRange(200)
	, m_Speed(100)
{
	SetPos(_Pos);
	SetScale(_Scale);

	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(GetScale());

	// RigidBody
	m_RigidBody->SetMass(2.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);


	// FSM
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
	m_FSM->AddState(L"Attack", new CAttackState);
	m_FSM->AddState(L"Dead", new CDeadState);
	


	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"MonsterLeftTex", L"texture\\Monster\\Enemy\\Demonio_Left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"MonsterRightTex", L"texture\\Monster\\Enemy\\Demonio_Right.png");

	/*m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);

	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\monster\\");*/

	// Load
	/*m_Animator->LoadAnimation(L"IDLE_LEFT");
	m_Animator->LoadAnimation(L"IDLE_RIGHT");
	m_Animator->LoadAnimation(L"WALK_LEFT");
	m_Animator->LoadAnimation(L"WALK_RIGHT");*/

	//m_Animator->Play(L"IDLE_RIGHT", true);

	// Rigidbody 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);
}

CMonster::~CMonster()
{

}



void CMonster::begin()
{
	// 블랙보드 추가는 프레임마다 호출하는 대신 begin() 쪽에다가
	m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &m_DetectRange);
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_Speed);
	m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	m_FSM->SetBlackboardData(L"Animator", DATA_TYPE::ANIMATOR, &m_Animator);


	// 플레이어를 타겟으로 설정해서 블랙보드에 추가
	CObj* pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pPlayer);

	m_FSM->ChangeState(L"Idle");

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CMonster::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CMonster::Air);
	m_RigidBody->SetWallDelegate(this, (DELEGATE)&CMonster::SetWall);
	m_RigidBody->SetWallOffDelegate(this, (DELEGATE)&CMonster::SetWallOff);
}

void CMonster::tick()
{
	CObj::tick();
}

//void CMonster::render()
//{
//	Vec2 vPos = GetRenderPos();
//	Vec2 vScale = GetScale();
//
//	/*TransparentBlt(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
//					   , (int)(vPos.y - m_Img->GetHeight() / 2.f)
//					   , m_Img->GetWidth(), m_Img->GetHeight()
//					   , m_Img->GetDC(), 0, 0
//					   , m_Img->GetWidth(), m_Img->GetHeight(), RGB(255, 0, 255));*/
//
//
//	static float alpha = 0;
//	static float dir = 1;
//
//	alpha += DT * 400.f * dir;
//
//	if (255.f <= alpha)
//	{
//		dir *= -1.f;
//	}
//	else if (alpha <= 0.f)
//	{
//		dir *= -1.f;
//	}
//
//	// AlphaBlending  
//	// 지정한 색을 출력을 아예 안하는 Transparent와는 다르게 
//	// AlphaBlend는 (본인의 RGB x Alpha) + (목적지 색상 x (1-Alpha)) 값을 출력해준다.
//	BLENDFUNCTION bf = {};
//
//	bf.BlendOp = AC_SRC_OVER;
//	bf.BlendFlags = 0;
//	bf.SourceConstantAlpha = 255;	// 투명도(0~255)
//	bf.AlphaFormat = AC_SRC_ALPHA;	// 소스의 알팍값을 이용하겠다.
//	
//
//	AlphaBlend(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
//				 , (int)(vPos.y - m_Img->GetHeight() / 2.f)
//				 , m_Img->GetWidth(), m_Img->GetHeight()
//				 , m_Img->GetDC(), 0, 0, m_Img->GetWidth(), m_Img->GetHeight(), bf);
//}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	CSnow* pSnow = dynamic_cast<CSnow*>(_OtherObj);

	if (_OtherObj->GetName() == L"Snow")
	{
		--m_HP;

		if (0 >= m_HP)
		{
			Destroy();
		}
	}
}

void CMonster::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CMonster::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CMonster::Jump()
{
	if (m_Direction == eDirection::Left)
		m_Animator->Play(L"JUMP_LEFT", false);
	else if (m_Direction == eDirection::Right)
		m_Animator->Play(L"JUMP_RIGHT", false);

	Vec2 vGV = m_RigidBody->GetGravityVelocity();

	if (0.f < vGV.y)
		m_RigidBody->SetGravityVelocity(Vec2(0.f, 0.f));

	m_RigidBody->Jump();
}

void CMonster::Ground()
{
	m_Ground = true;
}

void CMonster::Air()
{
	m_Ground = false;
}

void CMonster::SetWall()
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

void CMonster::SetWallOff()
{
	m_StopLeft = false;
	m_StopRight = false;
}
