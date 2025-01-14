#include "pch.h"
#include "CRigidBody.h"


CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxWalkSpeed(0.f)
	, m_MaxGravitySpeed(0.f)
	, m_Friction(600.f)
	, m_GravityAccel(980.f)
	, m_UseGravity(false)
	, m_Ground(false)
	, m_JumpSpeed(300.f)
	, m_MissileSpeed(500.f)
	, m_GroundFunc(nullptr)
	, m_AirFunc(nullptr)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
	, m_Wall(false)
	, m_WallInst(nullptr)
	, m_WallDelegate(nullptr)
	, m_WallOffInst(nullptr)
	, m_WallOffDelegate(nullptr)
	, m_AirInst(nullptr)
	, m_AirDelegate(nullptr)
	, m_Active(true)
{
}

CRigidBody::CRigidBody(const CRigidBody& _Other)
	: CComponent(_Other)
	, m_Mass(_Other.m_Mass)
	, m_InitWalkSpeed(_Other.m_InitWalkSpeed)
	, m_MaxWalkSpeed(_Other.m_MaxWalkSpeed)
	, m_MaxGravitySpeed(_Other.m_MaxGravitySpeed)
	, m_Friction(_Other.m_Friction)
	, m_GravityAccel(_Other.m_GravityAccel)
	, m_UseGravity(_Other.m_UseGravity)
	, m_Ground(_Other.m_Ground)
	, m_JumpSpeed(_Other.m_JumpSpeed)
	, m_MissileSpeed(_Other.m_MissileSpeed)
	, m_GroundFunc(nullptr)
	, m_AirFunc(nullptr)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
	, m_Wall(false)
	, m_WallInst(nullptr)
	, m_WallDelegate(nullptr)
	, m_WallOffInst(nullptr)
	, m_WallOffDelegate(nullptr)
	, m_AirInst(nullptr)
	, m_AirDelegate(nullptr)
	, m_Active(true)
{

}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
	SetGround(false);
}

void CRigidBody::Jump(Vec2 _Dir)
{
	m_VelocityByGravity += _Dir * m_MissileSpeed;
	SetGround(false);
}

void CRigidBody::Shoot(Vec2 _Dir)
{
	m_Velocity += _Dir * m_MissileSpeed;
}

void CRigidBody::finaltick()
{
	if (m_Active)
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

		// 최소 속도 보정
		if (m_InitWalkSpeed != 0.f && m_Velocity.Length() < 10.f && !vAccel.IsZero())
		{
			Vec2 vForceDir = m_Force;
			vForceDir.Normalize();
			m_Velocity = vForceDir * m_InitWalkSpeed;
		}

		// 만약 RigidBody에 적용된 힘이 없으면서, 속도는 있는 경우
		// 마찰에 의해서 현재 속도를 줄인다
		if (m_Force.IsZero())
		{
			float Speed = m_Velocity.Length();
			Speed -= m_Friction * DT;

			// 마찰에 의해서 속도가 역으로 생길 수는 없기 때문에
			// 감소된 속력의 크기가 음수가 되지 않게 보저한다.
			if (Speed < 0)
				Speed = 0.f;

			if (!m_Velocity.IsZero())
				m_Velocity.Normalize();

			m_Velocity *= Speed;
		}

		// 중력 가속도에 의한 속도 증가
		if (m_UseGravity && !m_Ground)
		{
			m_VelocityByGravity += Vec2(0.f, 1.f) * m_GravityAccel * DT;

			if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
			{
				m_VelocityByGravity.Normalize();
				m_VelocityByGravity *= m_MaxGravitySpeed;
			}
		}

		// 최종 속도 
		Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;


		// 현재 속도에 따른 이동
		// 거리 = 속도 x 시간
		vObjPos += vFinalVelocity * DT;

		GetOwner()->SetPos(vObjPos);

		// 이번 프레임 힘 초기화
		m_Force = Vec2(0.f, 0.f);
		m_AddVelocity = Vec2(0.f, 0.f);

		// DebugRender
		DrawDebugLine(PEN_TYPE::PEN_RED, vObjPos, vObjPos + m_VelocityByGravity, 0.f);
	}

}