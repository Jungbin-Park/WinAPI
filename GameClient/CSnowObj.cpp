#include "pch.h"
#include "CSnowObj.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CDbgRender.h"

#include "CPlayer.h"

CSnowObj::CSnowObj()
	: m_Speed(1000.f)
	, m_HitCount(0)
	, m_Dir(Vec2(0.f, 0.f))
	, m_Direction(eDirection::None)
	, m_StopLeft(false)
	, m_StopRight(false)
	, m_bRoll(false)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_Collider->SetName(L"SnowObj Collider");
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(120.f, 120.f));
	m_Collider->SetActive(true);


	// ===============================
	//		  Animation 추가
	// ===============================
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SnowObjTex", L"texture\\Monster\\SnowObj2.png");
	CTexture* pAtlas2 = CAssetMgr::GetInst()->LoadTexture(L"SnowRollTex", L"texture\\Monster\\SnowRoll.png");

	m_Animator->CreateAnimation(L"IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(130.f, 155.f), 1, 10);
	m_Animator->CreateAnimation(L"SNOWROLL", pAtlas2, Vec2(0.f, 0.f), Vec2(130.f, 155.f), 2, 10);


	m_Animator->FindAnimation(L"IDLE")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"SNOWROLL")->Save(L"animation\\snowobj\\");


	//m_Animator->LoadAnimation(L"animation\\snowobj\\IDLE.anim");


	// ===============================
	//      강체(Rigidbody) 설정
	// ===============================
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(0.f);


	// ===============================
	//         중력 관련 설정
	// ===============================
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(10000.f);
	m_RigidBody->SetGravityVelocity(Vec2(0.f, 50.f));
	m_RigidBody->SetGravityAccel(10000.f);

	m_Animator->Play(L"IDLE", false);
}

CSnowObj::~CSnowObj()
{
}

void CSnowObj::begin()
{
}

void CSnowObj::tick()
{
	CObj::tick();

	if (m_HitCount == 3)
		Destroy();

	Vec2 vPos = GetPos();
	vPos.x += m_Dir.x * m_Speed * DT;
	SetPos(vPos);
}

void CSnowObj::Shoot(Vec2 _Dir)
{
	m_Dir = _Dir;
	m_Animator->Play(L"SNOWROLL", true);
}

void CSnowObj::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	if (_OtherObj->GetName() == L"Wall")
	{
		m_HitCount++;
		m_Dir.x *= -1;
	}
}

void CSnowObj::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CSnowObj::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}
