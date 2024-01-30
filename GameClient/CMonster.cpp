#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"

CMonster::CMonster()
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(120.f, 120.f));
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
}
