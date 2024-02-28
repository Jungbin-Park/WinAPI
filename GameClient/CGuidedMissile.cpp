#include "pch.h"
#include "CGuidedMissile.h"

CGuidedMissile::CGuidedMissile()
	: m_Target(nullptr)
{

}

CGuidedMissile::~CGuidedMissile()
{

}

void CGuidedMissile::tick()
{
	// 추적 대상이 유효한 지 확인
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// 추적 대상을 향하는 각도를 구함

	CMissile::tick();
}

void CGuidedMissile::FindTarget()
{
	
}
