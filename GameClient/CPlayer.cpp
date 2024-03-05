#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CGuidedMissile.h"

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	// Player�� ������Ʈ ����
	m_HeadCol = (CCollider*)AddComponent(new CCollider);
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -40.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 20.f));
	m_BodyCol->SetScale(Vec2(30.f, 60.f));
	m_BodyCol->SetActive(true);


	m_PlayerImg = CAssetMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Fighter.bmp");
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
	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y += m_Speed * DT;
	}

	// Space Ű�� ������ �̻����� ���.
	if (KEY_TAP(KEY::SPACE))
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


