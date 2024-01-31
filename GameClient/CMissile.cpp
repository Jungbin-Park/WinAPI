#include "pch.h"
#include "CMissile.h"

#include "CCollider.h"

CMissile::CMissile()
	: m_Speed(500.f)
{
	// Missile의 컴포넌트 설정
	m_Collider = (CCollider*)AddComponent(new CCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(20.f, 20.f));
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	Vec2 vPos = GetPos();
	vPos.y -= DT * m_Speed;
	SetPos(vPos);
}

void CMissile::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 렌더링 과정 문제점(화면 클리어)
	Ellipse(DC, vPos.x - vScale.x * 0.5f
		, vPos.y - vScale.y * 0.5f
		, vPos.x + vScale.x * 0.5f
		, vPos.y + vScale.y * 0.5f);
}
