#include "pch.h"
#include "CMissle.h"


CMissle::CMissle()
	: m_Speed(1000.f)
{
}

CMissle::~CMissle()
{
}

void CMissle::tick()
{
	Vec2 vPos = GetPos();
	vPos.y -= DT * m_Speed;
	SetPos(vPos);
}
