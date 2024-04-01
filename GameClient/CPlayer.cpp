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
	// Player�� ������Ʈ ����
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(64.f, 110.f));
	m_BodyCol->SetActive(true);


	//// Animation �߰�
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"PlayerLeftTex", L"texture\\Player\\Nick_Left.bmp");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"PlayerRightTex", L"texture\\Player\\Nick_Right.bmp");

	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(896.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(128.f, 0.f), Vec2(128.f, 128.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(512.f, 0.f), Vec2(128.f, 128.f), 3, 10);

	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");


	// ������ ����
	//m_Animator->FindAnimation(L"IDLE_RIGHT")->GetFrame(1).Offset = Vec2(1.f, 0.f); 

	// Animation �ε�
	/*m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");*/
	
	m_Animator->Play(L"IDLE_RIGHT", true);

	// ��ü(Rigidbody) ����
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// �߷� ���� ����
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);

	
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)	// ������ �����ؼ� ���� �����̱� ������ �״�� �����ص� ��. ���� ���� �̹����� ���� �� �ε��� �ʿ䰡 ����
	, m_JumpCount(_Other.m_JumpCount)
	, m_CurJumpCount(_Other.m_CurJumpCount)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	// �θ��� ��������ڸ� ���� ������Ʈ���� ���簡 �̷�����ٸ�
	// ����� ������Ʈ���� ã�Ƽ� ����Ű�⸸ �ϸ� ��.
	m_BodyCol = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
	// Callback ����
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::RestoreJumpCount);
}

void CPlayer::tick()
{
	// ���� ��ǥ ����� ���ؼ� CObj�� tick()�� ���� �������־�� ��
	CObj::tick();

	Vec2 vPos = GetPos();

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�
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

	// Space Ű�� ������ �̻����� ���.
	if (KEY_TAP(KEY::SPACE))
	{
		if (m_JumpCount > m_CurJumpCount)
		{
			Jump();
			m_CurJumpCount += 1;
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

void CPlayer::Shoot()
{
	CMissile* pMissile = new CGuidedMissile;
	pMissile->SetName(L"Missile");

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));

	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

	LOG(LOG_TYPE::DBG_WARNING, L"�̻��� �߻�");

	//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);
}

void CPlayer::Jump()
{
	Vec2 vGV = m_RigidBody->GetGravityVelocity();

	if(0.f < vGV.y)
		m_RigidBody->SetGravityVelocity(Vec2(0.f, 0.f));

	m_RigidBody->Jump();
}


