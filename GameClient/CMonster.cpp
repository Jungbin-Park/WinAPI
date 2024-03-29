#include "pch.h"
#include "CMonster.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

#include "CMissile.h"



CMonster::CMonster()
	: m_HP(5)
	, m_Img(nullptr)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(120.f, 120.f));
	m_Collider->SetActive(true);
	
	m_RigidBody->SetMass(2.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);


	//Animation
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"MonsterLeftTex", L"texture\\Monster\\Enemy\\Demonio_Left.png");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"MonsterRightTex", L"texture\\Monster\\Enemy\\Demonio_Right.png");

	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(512.f, 0.f), Vec2(128.f, 128.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(128.f, 0.f), Vec2(128.f, 128.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(128.f, 0.f), Vec2(128.f, 128.f), 3, 10);

	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\monster\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\monster\\");

	m_Animator->Play(L"IDLE_RIGHT", true);

	// Rigidbody
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(980.f);
	m_RigidBody->SetJumpSpeed(600.f);

}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
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
	CMissile* pMissile = dynamic_cast<CMissile*>(_OtherObj);

	if (_OtherObj->GetName() == L"Missile")
	{
		--m_HP;

		if (0 >= m_HP)
		{
			Destroy();
		}
	}
}
