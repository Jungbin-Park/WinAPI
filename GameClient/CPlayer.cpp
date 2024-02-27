#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMissile.h"
#include "CCollider.h"

#include "CDbgRender.h"

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
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
		CMissile* pMissile = new CMissile;
		pMissile->SetName(L"Missile");

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

		//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);
	}

	SetPos(vPos);
}


void CPlayer::render()
{
	Vec2 vPos = GetPos();

	float fWidth = (float)m_PlayerImg->GetWidth();
	float fHeight = (float)m_PlayerImg->GetHeight();

	/*BitBlt(DC, vPos.x - fWidth / 2.f
		, vPos.y - fHeight / 2.f
		, fWidth, fHeight
		, m_PlayerImg->GetDC()
		, 0, 0, SRCCOPY);*/

	TransparentBlt(DC
		, int(vPos.x - fWidth / 2.f)
		, int(vPos.y - fHeight / 2.f)
		, (int)fWidth, (int)fHeight
		, m_PlayerImg->GetDC()
		, 0, 0, (int)fWidth, (int)fHeight
		, RGB(255, 0, 255));
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


