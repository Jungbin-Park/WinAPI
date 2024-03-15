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

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	// Player의 컴포넌트 설정
	m_HeadCol = (CCollider*)AddComponent(new CCollider);
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -40.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 20.f));
	m_BodyCol->SetScale(Vec2(30.f, 60.f));
	m_BodyCol->SetActive(true);


	//// Animation 추가
	//CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"PlayerLeftTex", L"texture\\Player\\Nick_Left.bmp");
	//CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"PlayerRightTex", L"texture\\Player\\Nick_Right.bmp");

	//m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	//m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(896.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	//m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(128.f, 0.f), Vec2(128.f, 128.f), 3, 10);
	//m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(512.f, 0.f), Vec2(128.f, 128.f), 3, 10);

	//m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");

	//m_Animator->FindAnimation(L"IDLE_RIGHT")->GetFrame(1).Offset = Vec2(1.f, 0.f); 
	

	// Animation 로드
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");
	
	m_Animator->Play(L"IDLE_RIGHT", true);

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
}

void CPlayer::tick()
{
	Vec2 vPos = GetPos();

	// 왼쪽키가 눌린적이 있으면(눌려있으면) 왼쪽으로 1픽셀 이동
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::LEFT))
	{
		m_Animator->Play(L"WALK_LEFT", true);
	}
	else if (KEY_RELEASED(KEY::LEFT))
	{
		m_Animator->Play(L"IDLE_LEFT", true);
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_RigidBody->AddForce(Vec2(1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::RIGHT))
	{
		m_Animator->Play(L"WALK_RIGHT", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		m_Animator->Play(L"IDLE_RIGHT", true);
	}

	if (KEY_PRESSED(KEY::UP))
	{
		//vPos.y -= m_Speed * DT;
	}
	else if (KEY_TAP(KEY::UP))
	{
		//m_Animator->Play(L"WALK_UP", true);
	}
	else if (KEY_RELEASED(KEY::UP))
	{
		//m_Animator->Play(L"IDLE_UP", true);
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		//vPos.y += m_Speed * DT;
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		//m_Animator->Play(L"WALK_DOWN", true);
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		//m_Animator->Play(L"IDLE_DOWN", true);
	}

	// Space 키가 눌리면 미사일을 쏜다.
	if (KEY_TAP(KEY::SPACE))
	{
		CMissile* pMissile = new CGuidedMissile;
		pMissile->SetName(L"Missile");

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

		LOG(LOG_TYPE::DBG_WARNING, L"미사일 발사");

		//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);
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


