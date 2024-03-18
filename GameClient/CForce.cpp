#include "pch.h"
#include "CForce.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CRigidBody.h"


CForce::CForce()
	: m_Force(0.f)
	, m_Range(0.f)
	, m_Time(0.f)
	, m_Age(0.f)
{

}

CForce::~CForce()
{

}

void CForce::tick()
{
	AddForce(LAYER_TYPE::MONSTER);
	AddForce(LAYER_TYPE::PLAYER);

	DrawDebugCircle(PEN_TYPE::PEN_BLUE, GetPos(), Vec2(m_Range, m_Range), 0.f);

	m_Age += DT;

	if (m_Time < m_Age)
	{
		Destroy();
	}
}

void CForce::AddForce(LAYER_TYPE _type)
{
	// �������� Force �ֺ��� �ִ� ��ü�鿡�� ���� �����Ų��.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecObj = pCurLevel->GetObjects(_type);

	for (size_t i = 0; i < vecObj.size(); i++)
	{
		float fDist = GetPos().GetDistance(vecObj[i]->GetPos());
		if (fDist <= m_Range)
		{
			CRigidBody* pComponent = vecObj[i]->GetComponent<CRigidBody>();
			if (nullptr == pComponent)
				continue;

			// ��ü�� Force �� �������� 1�� ����� �������� ���´�
			// ��ü�� Force �� �ּ��� 0�� ����� �������� ���´�. Force�� Range�� ����� Ratio�� 0�̴�.
			float fRatio = Saturate(1.f - fDist / m_Range);
			float Force = m_Force * fRatio;

			Vec2 vForce = vecObj[i]->GetPos() - GetPos();
			if (!vForce.IsZero())
			{
				vForce.Normalize();
				vForce *= Force;
				pComponent->AddForce(vForce);
			}
		}
	}
}



