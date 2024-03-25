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
    Vec2    m_Velocity;             // 속도 ( 방향, 크기 )
    Vec2    m_VelocityByGravity;    // 중력에 의해서 증가하는 속도
    Vec2    m_AddVelocity;          // 최종 속도에 누적될 속도

    float   m_Mass;                 // 질량
    Vec2    m_Force;                // 힘 (어느 방향으로 힘을 주는지)

    float   m_InitWalkSpeed;        // 최소 보장 속력
    float   m_MaxWalkSpeed;         // 최대 제한 속력
    float   m_MaxGravitySpeed;      // 중력으로 발생한 낙하 속도 제한

    float   m_Friction;             // 마찰력

    float   m_GravityAccel;         // 중력가속도(모든 물체에게 동일하게 적용)
    bool    m_UseGravity;           // 중력 On/Off
    bool    m_Ground;               // 땅 위에 서 있는지 체크
    float   m_JumpSpeed;            // 점프 속력

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

