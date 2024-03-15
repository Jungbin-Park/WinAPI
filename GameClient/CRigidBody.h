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
    Vec2    m_Velocity; // �ӵ� ( ����, ũ�� )
    float   m_Mass;     // ����
    Vec2    m_Force;    // �� (��� �������� ���� �ִ���)

    float   m_InitWalkSpeed;
    float   m_MaxWalkSpeed;

public:
    void AddForce(Vec2 _vForce) { m_Force += _vForce; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }
    void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }

    float GetMass() { return m_Mass; }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);
public:
    CRigidBody();
    ~CRigidBody();
};

