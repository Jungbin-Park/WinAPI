#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CGuidedMissile.h"
#include "CSnow.h"

#include "CDbgRender.h"

void BeGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded!!");
}

void BeAir()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Aired!!");
}

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
	, m_JumpCount(1)
	, m_CurJumpCount(0)
{
	// Player의 컴포넌트 설정
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(80.f, 128.f));
	m_BodyCol->SetActive(true);


	//// Animation 추가
	/*CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"PlayerLeftTex", L"texture\\Player\\Nick_Left1.bmp");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"PlayerRightTex", L"texture\\Player\\Nick_Right1.bmp");

	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(1120.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"JUMP_LEFT", pAtlasL, Vec2(0.f, 160.f), Vec2(160.f, 160.f), 6, 7);
	m_Animator->CreateAnimation(L"JUMP_RIGHT", pAtlasR, Vec2(320.f, 160.f), Vec2(160.f, 160.f), 6, 7);


	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player\\");*/


	// 오프셋 조정
	//m_Animator->FindAnimation(L"IDLE_RIGHT")->GetFrame(1).Offset = Vec2(1.f, 0.f); 

	// Animation 로드
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_RIGHT.anim");
	
	m_Animator->Play(L"IDLE_RIGHT", true);

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);
		
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)	// 에셋은 공유해서 쓰는 개념이기 때문에 그대로 복사해도 됨. 굳이 같은 이미지를 새로 또 로딩할 필요가 없음
	, m_JumpCount(_Other.m_JumpCount)
	, m_CurJumpCount(_Other.m_CurJumpCount)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	// 부모의 복사생성자를 통해 컴포넌트들의 복사가 이루어졌다면
	// 복사된 컴포넌트들을 찾아서 가리키기만 하면 됨.
	m_BodyCol = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
	// Callback 설정
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::RestoreJumpCount);
}

void CPlayer::tick()
{
	// 이전 좌표 기록을 위해서 CObj의 tick()을 먼저 구현해주어야 함
	CObj::tick();

	switch (m_State)
	{
	case CPlayer::eState::IDLE:
		Idle();
		break;
	case CPlayer::eState::MOVE:
		Move();
		break;
	case CPlayer::eState::ATTACK:
		Attack();
		break;
	case CPlayer::eState::JUMP:
		Jump();
		break;
	default:
		break;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_JumpCount > m_CurJumpCount)
		{
			Jump();
			m_CurJumpCount += 1;
			m_Animator->Play(L"JUMP_LEFT", false);
		}
	}

	

	SetPos(vPos);
}




void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	
}

void CPlayer::Idle()
{
	switch (m_Direction)
	{
	case CPlayer::eDirection::Left:
		m_Animator->Play(L"IDLE_LEFT", true);
		break;
	case CPlayer::eDirection::Right:
		m_Animator->Play(L"IDLE_RIGHT", true);
		break;
	default:
		break;
	}

	if (KEY_PRESSED(KEY::A))
	{
		m_Direction = eDirection::Left;
		m_State = CPlayer::eState::MOVE;
		m_Animator->Play(L"WALK_LEFT", true);
	}
	if (KEY_PRESSED(KEY::D))
	{
		m_Direction = eDirection::Right;
		m_State = CPlayer::eState::MOVE;
		m_Animator->Play(L"WALK_RIGHT", true);
	}
	if (KEY_TAP(KEY::CTRL))
	{
		m_State = CPlayer::eState::ATTACK;
		switch (m_Direction)
		{
		case CPlayer::eDirection::Left:
			m_Animator->Play(L"ATTACK_LEFT", false);
			break;
		case CPlayer::eDirection::Right:
			m_Animator->Play(L"ATTACK_RIGHT", false);
			break;
		default:
			break;
		}
		
	}
}

void CPlayer::Move()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= m_Speed * DT;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_Speed * DT;
	}

	SetPos(vPos);

	if (KEY_RELEASED(KEY::LEFT))
	{
		m_Direction = eDirection::Left;
		m_State = CPlayer::eState::IDLE;
		m_Animator->Play(L"IDLE_LEFT", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		m_Direction = eDirection::Right;
		m_State = CPlayer::eState::IDLE;
		m_Animator->Play(L"IDLE_RIGHT", true);
	}
}

void CPlayer::Attack()
{

}

void CPlayer::Shoot()
{
	CSnow* pSnow = new CSnow;
	pSnow->SetName(L"Snow");

	Vec2 vSnowPos = GetPos();
	vSnowPos.y -= GetScale().y / 2.f;

	pSnow->SetPos(vSnowPos);
	pSnow->SetScale(Vec2(20.f, 20.f));

	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pSnow);

	LOG(LOG_TYPE::DBG_WARNING, L"미사일 발사");

	//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);
}

void CPlayer::Jump()
{
	Vec2 vGV = m_RigidBody->GetGravityVelocity();

	if(0.f < vGV.y)
		m_RigidBody->SetGravityVelocity(Vec2(0.f, 0.f));

	m_RigidBody->Jump();
}


