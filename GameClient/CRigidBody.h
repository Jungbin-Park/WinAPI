#pragma once
#include "CComponent.h"

// vector : 크기, 방향
// scalar : 크기

// 속도 ( velocity )
// 속력 ( Speed )

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity; // 속도 ( 방향, 크기 )
    float   m_Mass;     // 질량
    Vec2    m_Force;    // 힘 (어느 방향으로 힘을 주는지)

    float   m_InitWalkSpeed;
    float   m_MaxWalkSpeed;

    float   m_Friction; // 마찰력

public:
    void AddForce(Vec2 _vForce) { m_Force += _vForce; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }
    void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }

    float GetMass() { return m_Mass; }
    float GetInitialWalkSpeed() { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
    float GetFriction() { return m_Friction; }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);
public:
    CRigidBody();
    ~CRigidBody();
};

