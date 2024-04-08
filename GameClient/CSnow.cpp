#include "pch.h"
#include "CSnow.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CSnow::CSnow()
	: m_Speed(200.f)
	, m_Direction(eDirection::None)
	, m_PlayOnce(false)
{
	// 컴포넌트 설정
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(30.f, 40.f));
	
	// Animation
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SnowTex", L"texture\\Player\\Snow.png");
	CTexture* hAtlas = CAssetMgr::GetInst()->LoadTexture(L"HitTex", L"texture\\Player\\Hit.png");

	/*m_Animator->CreateAnimation(L"SHOOT_LEFT", pAtlas, Vec2(0.f, 0.f), Vec2(96.f, 78.f), 2, 10);
	m_Animator->CreateAnimation(L"SHOOT_RIGHT", pAtlas, Vec2(0.f, 78.f), Vec2(96.f, 78.f), 2, 10);
	m_Animator->CreateAnimation(L"HIT", hAtlas, Vec2(0.f, 0.f), Vec2(90.f, 90.f), 1, 10);

	m_Animator->FindAnimation(L"SHOOT_LEFT")->Save(L"animation\\skill\\");
	m_Animator->FindAnimation(L"SHOOT_RIGHT")->Save(L"animation\\skill\\");
	m_Animator->FindAnimation(L"HIT")->Save(L"animation\\skill\\");*/

	m_Animator->LoadAnimation(L"animation\\skill\\SHOOT_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\skill\\SHOOT_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\skill\\HIT.anim");

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(500.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(400.f);


	// Sound

}

CSnow::~CSnow()
{
}


void CSnow::tick()
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

	CAnimation* sCurAnim = m_Animator->GetCurAnim();

	if (sCurAnim->GetName() == L"HIT")
	{
		if (sCurAnim->IsFinish())
		{
			Destroy();
		}
	}

	SetPos(vPos);
	
}

void CSnow::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	m_Animator->Play(L"HIT", false);
}

void CSnow::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CSnow::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}



