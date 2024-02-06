#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMissile.h"
#include "CCollider.h"

#include "CDbgRender.h"

CPlayer::CPlayer()
	: m_Speed(500.f)
{
	// Player의 컴포넌트 설정
	m_HeadCol = (CCollider*)AddComponent(new CCollider);
	m_BodyCol = (CCollider*)AddComponent(new CCollider);

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -80.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(60.f, 60.f));
	m_BodyCol->SetActive(true);
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
	if (KEY_PRESSED(LEFT))
	{
		vPos.x -= m_Speed * DT;
	}

	if (KEY_PRESSED(RIGHT))
	{
		vPos.x += m_Speed * DT;
	}

	if (KEY_PRESSED(UP))
	{
		vPos.y -= m_Speed * DT;
	}

	if (KEY_PRESSED(DOWN))
	{
		vPos.y += m_Speed * DT;
	}

	// Space 키가 눌리면 미사일을 쏜다.
	if (KEY_TAP(SPACE))
	{
		CMissile* pMissle = new CMissile;

		Vec2 vMisslePos = GetPos();
		vMisslePos.y -= GetScale().y / 2.f;

		pMissle->SetPos(vMisslePos);
		pMissle->SetScale(Vec2(20.f, 20.f));

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(LAYER_TYPE::PLAYER_MISSILE, pMissle);

		//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);
	}

	SetPos(vPos);
}


void CPlayer::render()
{
	CObj::render();
}


