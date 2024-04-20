#include "pch.h"
#include "CPlayerLife.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTexture.h"
#include "CLevel_Stage01.h"
#include "CLevelMgr.h"

CPlayerLife::CPlayerLife()
	: m_PlayOnce(false)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	CTexture* Atlas = CAssetMgr::GetInst()->LoadTexture(L"Life", L"texture\\Player\\Life.bmp");

	m_Animator->CreateAnimation(L"LIFE3", Atlas, Vec2(0.f, 0.f), Vec2(166.f, 50.f), 1, 10);
	m_Animator->CreateAnimation(L"LIFE2", Atlas, Vec2(0.f, 0.f), Vec2(110.f, 50.f), 1, 10);
	m_Animator->CreateAnimation(L"LIFE1", Atlas, Vec2(0.f, 0.f), Vec2(56.f, 50.f), 1, 10);


	m_Animator->FindAnimation(L"LIFE3")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"LIFE2")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"LIFE1")->Save(L"animation\\player\\");
}

CPlayerLife::~CPlayerLife()
{
}

void CPlayerLife::begin()
{
}

void CPlayerLife::tick()
{
	CObj::tick();

	CLevel* Level = CLevelMgr::GetInst()->GetCurrentLevel();
	int Life = dynamic_cast<CLevel_Stage01*>(Level)->GetLife();

	if (Life == 3)
	{
		m_Animator->Play(L"LIFE3", false);
	}
	else if (Life == 2)
	{
		m_Animator->Play(L"LIFE2", false);
	}
	else if (Life == 1)
	{
		m_Animator->Play(L"LIFE1", false);
	}
}
