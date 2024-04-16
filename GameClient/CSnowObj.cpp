#include "pch.h"
#include "CSnowObj.h"

#include "CLevel_Stage01.h"
#include "CLevelMgr.h"

#include "CTaskMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CDbgRender.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMiniBoss.h"

#include "CFSM.h"

CSnowObj::CSnowObj()
	: m_Owner(nullptr)
	, m_Speed(1000.f)
	, m_Active(false)
	, m_WallHitCount(0)
	, m_SnowHitCount(1)
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
	m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(120.f, 140.f));
	m_Collider->SetActive(true);


	// ===============================
	//		  Animation 추가
	// ===============================
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SnowObjTex", L"texture\\Monster\\SnowObj2.png");
	CTexture* pAtlas2 = CAssetMgr::GetInst()->LoadTexture(L"SnowRollTex", L"texture\\Monster\\SnowRoll.png");
	CTexture* Atlas1= CAssetMgr::GetInst()->LoadTexture(L"Snow1Tex", L"texture\\Monster\\Snow1.png");
	CTexture* Atlas2 = CAssetMgr::GetInst()->LoadTexture(L"Snow2Tex", L"texture\\Monster\\Snow2.png");
	CTexture* Atlas3 = CAssetMgr::GetInst()->LoadTexture(L"Snow3Tex", L"texture\\Monster\\Snow3.png");
	CTexture* BoomAtlas = CAssetMgr::GetInst()->LoadTexture(L"BOOMTex", L"texture\\Monster\\Boom.png");
	
	m_Animator->CreateAnimation(L"IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(156.f, 156.f), 1, 10);
	m_Animator->CreateAnimation(L"SNOWROLL", pAtlas2, Vec2(0.f, 0.f), Vec2(156.f, 156.f), 2, 10);
	m_Animator->CreateAnimation(L"Snow1", Atlas1, Vec2(0.f, 0.f), Vec2(156.f, 156.f), 1, 10);
	m_Animator->CreateAnimation(L"Snow2", Atlas2, Vec2(0.f, 0.f), Vec2(156.f, 156.f), 1, 10);
	m_Animator->CreateAnimation(L"Snow3", Atlas3, Vec2(0.f, 0.f), Vec2(156.f, 156.f), 1, 10);
	m_Animator->CreateAnimation(L"BOOM", BoomAtlas, Vec2(0.f, 0.f), Vec2(110.f, 110.f), 4, 10);

	m_Animator->FindAnimation(L"IDLE")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"SNOWROLL")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"Snow1")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"Snow2")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"Snow3")->Save(L"animation\\snowobj\\");
	m_Animator->FindAnimation(L"BOOM")->Save(L"animation\\snowobj\\");


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
	static float Time = 0.f;
	
	if (!m_bBoom)
	{
		Time += DT;

		if (Time >= 3.f)
		{
			if (!m_bRoll)
				m_SnowHitCount--;
			Time = 0.0f;
		}

		if (m_WallHitCount == 3)
		{
			m_WallHitCount = 0;
			Boom();
		}

		if (m_Active)
		{
			if (m_SnowHitCount < 5)
				m_Active = false;

			Vec2 vPos = GetPos();

			vPos.x += m_Dir.x * m_Speed * DT;
			SetPos(vPos);
			m_Owner->SetPos(vPos + Vec2(0.f, -18.f));
		}
		else
		{
			m_Owner->SetPos(GetPos());

			if (m_SnowHitCount == 0)
			{
				// 몬스터 Idle State로 전환
				if (m_Owner != nullptr)
				{
					CMonster* cMon = dynamic_cast<CMonster*>(m_Owner);
					if (cMon != nullptr)
						cMon->SetSnow(false);

					CMiniBoss* cMBoss = dynamic_cast<CMiniBoss*>(m_Owner);
					if (cMBoss != nullptr)
						cMBoss->SetSnow(false);
				}
					

				Destroy();
			}
			else if (m_SnowHitCount == 1)
			{
				m_Animator->Play(L"Snow1", false);
			}
			else if (m_SnowHitCount == 2)
			{
				m_Animator->Play(L"Snow1", false);
			}
			else if (m_SnowHitCount == 3)
			{
				m_Animator->Play(L"Snow2", false);
			}
			else if (m_SnowHitCount == 4)
			{
				m_Animator->Play(L"Snow3", false);
			}
			else if (m_SnowHitCount >= 5)
			{
				m_Animator->Play(L"IDLE", false);
				m_Active = true;
			}
		}
	}

	if (m_Animator->GetCurAnim()->GetName() == L"BOOM"
		&& m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
		
}

void CSnowObj::Shoot(Vec2 _Dir)
{
	if (!m_Active)
		return;

	m_bRoll = true;
	m_Dir = _Dir;
	m_Animator->Play(L"SNOWROLL", true);
}

void CSnowObj::Boom()
{
	m_Animator->Play(L"BOOM", false);
	CLevel_Stage01* curLevel = dynamic_cast<CLevel_Stage01*>(CLevelMgr::GetInst()->GetCurrentLevel());
	curLevel->AddScore();
	m_Owner->Destroy();
	m_bBoom = true;
}

void CSnowObj::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	if (m_Active && _OtherObj->GetName() == L"Wall")
	{
		if (m_WallHitCount < 3 && !m_bBoom)
		{
			m_WallHitCount++;
			m_Dir.x *= -1;
		}
	}

	if (_OtherObj->GetName() == L"Snow")
	{
		if (m_SnowHitCount < 6)
			m_SnowHitCount++;
	}
}

void CSnowObj::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CSnowObj::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}
