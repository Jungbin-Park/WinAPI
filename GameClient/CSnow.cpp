#include "pch.h"
#include "CSnow.h"

#include "CCollider.h"
#include "CTimeMgr.h"

CSnow::CSnow()
	: m_Speed(500.f)
	, m_Angle(PI * 2.f)
{
	// Missile�� ������Ʈ ����
	m_Collider = (CCollider*)AddComponent(new CCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(20.f, 20.f));
}

CSnow::~CSnow()
{
}

void CSnow::tick()
{
	Vec2 vPos = GetRenderPos();

	Vec2 vDir = Vec2(cosf(m_Angle), -sinf(m_Angle));

	vPos += vDir * m_Speed * DT;

	SetPos(vPos);
}

void CSnow::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// ������ ���� ������(ȭ�� Ŭ����)
	Ellipse(DC, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vPos.x + vScale.x * 0.5f)
		, (int)(vPos.y + vScale.y * 0.5f));
}


