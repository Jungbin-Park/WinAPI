#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CMissile.h"


CMonster::CMonster()
	: m_HP(5)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(120.f, 120.f));
	m_Collider->SetActive(true);
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
}

void CMonster::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(DC, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vPos.x + vScale.x * 0.5f)
		, (int)(vPos.y + vScale.y * 0.5f));
}

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
