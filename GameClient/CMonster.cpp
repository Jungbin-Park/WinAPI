#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CMissile.h"

CMonster::CMonster()
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

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	CMissile* pMissile = dynamic_cast<CMissile*>(_OtherObj);

	if (pMissile != nullptr)
	{
		int a = 0;
		//delete this;
	}

	if (_OtherObj->GetName() == L"Missile")
	{
		int a = 0;
	}
}
