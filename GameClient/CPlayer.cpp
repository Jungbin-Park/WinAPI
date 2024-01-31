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
	// Player�� ������Ʈ ����
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider = GetComponent<CCollider>();

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(120.f, 120.f));
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

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�
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

	// Space Ű�� ������ �̻����� ���.
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


