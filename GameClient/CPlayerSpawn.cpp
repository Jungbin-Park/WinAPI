#include "pch.h"
#include "CPlayerSpawn.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTexture.h"

CPlayerSpawn::CPlayerSpawn()
	: m_Owner(nullptr)
	, m_PlayOnce(false)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	CTexture* Atlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerSpawn", L"texture\\Player\\PlayerSpawn.png");

	m_Animator->CreateAnimation(L"SPAWN", Atlas, Vec2(0.f, 0.f), Vec2(160.f, 165.f), 3, 10);
	m_Animator->FindAnimation(L"SPAWN")->Save(L"animation\\player\\");
	//m_Animator->LoadAnimation(L"animation\\player\\SPAWN.anim");

}

CPlayerSpawn::~CPlayerSpawn()
{
}

void CPlayerSpawn::begin()
{
	
}

void CPlayerSpawn::tick()
{
	CObj::tick();

	static float Time = 0.f;
	Time += DT;

	Vec2 Pos = GetPos();
	Vec2 playerPos = m_Owner->GetPos();

	if (!m_PlayOnce)
	{
		m_PlayOnce = true;

		m_Animator->Play(L"SPAWN", true);
	}

	SetPos(playerPos);

	if (Time >= 2.f)
	{
		Destroy();
		Time = 0.f;
	}
}
