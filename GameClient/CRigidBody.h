#pragma once
#include "CComponent.h"

// vector : ũ��, ����
// scalar : ũ��

// �ӵ� ( velocity )
// �ӷ� ( Speed )

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity;             // �ӵ� ( ����, ũ�� )
    Vec2    m_VelocityByGravity;    // �߷¿� ���ؼ� �����ϴ� �ӵ�
    Vec2    m_AddVelocity;          // ���� �ӵ��� ������ �ӵ�

    float   m_Mass;                 // ����
    Vec2    m_Force;                // �� (��� �������� ���� �ִ���)

    float   m_InitWalkSpeed;        // �ּ� ���� �ӷ�
    float   m_MaxWalkSpeed;         // �ִ� ���� �ӷ�
    float   m_MaxGravitySpeed;      // �߷����� �߻��� ���� �ӵ� ����

    float   m_Friction;             // ������

    float   m_GravityAccel;         // �߷°��ӵ�(��� ��ü���� �����ϰ� ����)
    bool    m_UseGravity;           // �߷� On/Off
    bool    m_Ground;               // �� ���� �� �ִ��� üũ
    float   m_JumpSpeed;            // ���� �ӷ�

public:
    void AddForce(Vec2 _vForce) { m_Force += _vForce; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }
    void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }
    void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

    void Jump();
    void SetGravityVelocity(Vec2 _Velocity) { m_VelocityByGravity = _Velocity; }

    float GetMass() { return m_Mass; }
    float GetInitialWalkSpeed() { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
    float GetFriction() { return m_Friction; }
    Vec2  GetGravityVelocity() { return m_VelocityByGravity; }

    void UseGravity(bool _Use) 
    { 
        m_UseGravity = _Use; 
        if (!m_UseGravity) 
            m_VelocityByGravity = Vec2(0.f, 0.f); 
    }

    void SetGround(bool _Ground)
    {
        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);
        }
    }

    bool IsGround() { return m_Ground; }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);
public:
    CRigidBody();
    ~CRigidBody();
};

