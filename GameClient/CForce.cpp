#include "pch.h"
#include "CForce.h"


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
	// 레벨에서 Force 주변에 있는 물체들에게 힘을 적용시킨다.

	DrawDebugCircle(PEN_TYPE::PEN_BLUE, GetPos(), Vec2(m_Range, m_Range), 0.f);

	m_Age += DT;

	if (m_Time < m_Age)
	{
		Destroy();
	}
}



