#include "pch.h"
#include "CRigidBody.h"


CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxWalkSpeed(0.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finaltick()
{
	Vec2 vObjPos = GetOwner()->GetPos();

	// F = M x A, F / M = A
	Vec2 vAccel = m_Force / m_Mass;

	// 가속도 더해줌
	m_Velocity += vAccel * DT;

	// 최대 속도 제한
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// 거리 = 속도 x 시간
	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);

	// force 다시 0으로 초기화
	m_Force = Vec2(0.f, 0.f);

	// DebugRender
	DrawDebugLine(PEN_TYPE::PEN_RED, vObjPos, vObjPos + m_Velocity, 0.f);
}