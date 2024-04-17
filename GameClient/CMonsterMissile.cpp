#include "pch.h"
#include "CMonsterMissile.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMonsterMissile::CMonsterMissile()
	: m_Speed(200.f)
	, m_Direction(eDirection::None)
	, m_PlayOnce(false)
	, m_Hit(false)
{
	// 컴포넌트 설정
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(64.f, 64.f));

	// Animation
	CTexture* Atlas = CAssetMgr::GetInst()->LoadTexture(L"FireTex", L"texture\\Monster\\Enemy\\Rana_Missile.png");

	
	m_Animator->CreateAnimation(L"SHOOT_LEFT", Atlas, Vec2(0.f, 250.f), Vec2(128.f, 125.f), 4, 10);
	m_Animator->CreateAnimation(L"SHOOT_RIGHT", Atlas, Vec2(0.f, 0.f), Vec2(128.f, 125.f), 4, 10);
	m_Animator->CreateAnimation(L"HIT_LEFT", Atlas, Vec2(0.f, 375.f), Vec2(128.f, 125.f), 4, 10);
	m_Animator->CreateAnimation(L"HIT_RIGHT", Atlas, Vec2(0.f, 125.f), Vec2(128.f, 125.f), 4, 10);

	m_Animator->FindAnimation(L"SHOOT_LEFT")->Save(L"animation\\monstermissile\\");
	m_Animator->FindAnimation(L"SHOOT_RIGHT")->Save(L"animation\\monstermissile\\");
	m_Animator->FindAnimation(L"HIT_LEFT")->Save(L"animation\\monstermissile\\");
	m_Animator->FindAnimation(L"HIT_RIGHT")->Save(L"animation\\monstermissile\\");
	

	/*m_Animator->LoadAnimation(L"animation\\skill\\SHOOT_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\skill\\SHOOT_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\skill\\HIT.anim");*/

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(500.f);
	m_RigidBody->SetInitialWalkSpeed(600.f);
	m_RigidBody->SetMissileSpeed(600.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(false);
	m_RigidBody->SetMaxGravitySpeed(400.f);

	// Sound
}

CMonsterMissile::~CMonsterMissile()
{
}

void CMonsterMissile::tick()
{
	CObj::tick();

	Vec2 vPos = GetPos();

	if (!m_PlayOnce)
	{
		m_PlayOnce = true;

		if (m_Direction == eDirection::Left)
		{
			m_Animator->Play(L"SHOOT_LEFT", true);
		}
		else if (m_Direction == eDirection::Right)
		{
			m_Animator->Play(L"SHOOT_RIGHT", true);
		}
	}

	if (!m_Hit)
	{
		if (m_Direction == eDirection::Left)
		{
			vPos.x -= m_Speed * DT;
		}
		else if (m_Direction == eDirection::Right)
		{
			vPos.x += m_Speed * DT;
		}
	}
	


	CAnimation* sCurAnim = m_Animator->GetCurAnim();

	if (sCurAnim->GetName() == L"HIT_LEFT" || sCurAnim->GetName() == L"HIT_RIGHT")
	{
		if (sCurAnim->IsFinish())
		{
			Destroy();
		}
	}

	SetPos(vPos);
}

void CMonsterMissile::shoot()
{
}

void CMonsterMissile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	m_Hit = true;

	if (m_Direction == eDirection::Left)
	{
		m_Animator->Play(L"HIT_LEFT", true);
	}
	else if (m_Direction == eDirection::Right)
	{
		m_Animator->Play(L"HIT_RIGHT", true);
	}
}

void CMonsterMissile::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CMonsterMissile::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}





