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
	, m_JumpSpeed(600.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
	m_Ground = false;
}

void CRigidBody::finaltick()
{
	Vec2 vObjPos = GetOwner()->GetPos();

	// F = M x A, F / M = A
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ� ������
	m_Velocity += vAccel * DT;

	// �ִ� �ӵ� ����
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// �ּ� �ӵ� ����
	if (m_InitWalkSpeed != 0.f && m_Velocity.Length() < 10.f && !vAccel.IsZero())
	{
		Vec2 vForceDir = m_Force;
		vForceDir.Normalize();
		m_Velocity = vForceDir * m_InitWalkSpeed;
	}

	// ���� RigidBody�� ����� ���� �����鼭, �ӵ��� �ִ� ���
	// ������ ���ؼ� ���� �ӵ��� ���δ�
	if (m_Force.IsZero())
	{
		float Speed = m_Velocity.Length();
		Speed -= m_Friction * DT;

		// ������ ���ؼ� �ӵ��� ������ ���� ���� ���� ������
		// ���ҵ� �ӷ��� ũ�Ⱑ ������ ���� �ʰ� �����Ѵ�.
		if (Speed < 0)
			Speed = 0.f;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= Speed;
	}

	// �߷� ���ӵ��� ���� �ӵ� ����
	if (m_UseGravity && !m_Ground)
	{
		m_VelocityByGravity += Vec2(0.f, 1.f) * m_GravityAccel * DT;

		if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity *= m_MaxGravitySpeed;
		}
	}

	// ���� �ӵ� 
	Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;


	// ���� �ӵ��� ���� �̵�
	// �Ÿ� = �ӵ� x �ð�
	vObjPos += vFinalVelocity * DT;

	GetOwner()->SetPos(vObjPos);

	// �̹� ������ �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
	m_AddVelocity = Vec2(0.f, 0.f);

	// DebugRender
	//DrawDebugLine(PEN_TYPE::PEN_RED, vObjPos, vObjPos + vFinalVelocity, 0.f);
}