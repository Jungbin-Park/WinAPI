#pragma once
#include "CComponent.h"

typedef void(*CALL_BACK)(void);         // 반환 타입이 void 이고 인자를 받지 않는 CALL_BACK 재정의
typedef void(CObj::*DELEGATE)(void);

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
    bool    m_Wall;                 // 벽에 닿였을때 체크
    float   m_JumpSpeed;            // 점프 속력

    Vec2    m_MissileDir;
    float   m_MissileSpeed;

    // Ground On/Off 호출시킬 함수 포인터(함수의 주소를 받아놨다가 필요한 순간에 호출)
    // CallBack : 전역함수포인터
    CALL_BACK   m_GroundFunc;
    CALL_BACK   m_AirFunc;
    
    // Delegate : 멤버함수포인터   (객체가 있어야 함)
    CObj*       m_GroundInst;
    DELEGATE    m_GroundDelegate;

    CObj*       m_AirInst;
    DELEGATE    m_AirDelegate;

    CObj*       m_WallInst;
    DELEGATE    m_WallDelegate;

    CObj*       m_WallOffInst;
    DELEGATE    m_WallOffDelegate;

public:
    void AddForce(Vec2 _vForce) { m_Force += _vForce; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }
    void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }
    void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetMissileSpeed(float _Speed) { m_MissileSpeed = _Speed; }

    void Jump();
    void Shoot(Vec2 _Dir);
    void SetGravityVelocity(Vec2 _Velocity) { m_VelocityByGravity = _Velocity; }

    float GetMass() { return m_Mass; }
    float GetInitialWalkSpeed() { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
    float GetFriction() { return m_Friction; }
    Vec2  GetGravityVelocity() { return m_VelocityByGravity; }

    void SetGroundFunc(void(*_pFunc)(void)) { m_GroundFunc = _pFunc; }
    void SetAirFunc(void(*_pFunc)(void)) { m_AirFunc = _pFunc; }

    void SetGroundDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_GroundInst = _Inst;
        m_GroundDelegate = _MemFunc;
    }
    
    void SetAirDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_AirInst = _Inst;
        m_AirDelegate = _MemFunc;
    }

    void SetWallDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_WallInst = _Inst;
        m_WallDelegate = _MemFunc;
    }

    void SetWallOffDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_WallOffInst = _Inst;
        m_WallOffDelegate = _MemFunc;
    }

    void UseGravity(bool _Use) 
    { 
        m_UseGravity = _Use; 
        if (!m_UseGravity) 
            m_VelocityByGravity = Vec2(0.f, 0.f); 
    }

    void SetGround(bool _Ground)
    {
        if (m_Ground == _Ground)
            return;

        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);

            if (nullptr != m_GroundFunc)
                m_GroundFunc();

            if (m_GroundInst && m_GroundDelegate)      
                (m_GroundInst->*m_GroundDelegate)();
        }
        else
        {
            if (nullptr != m_AirFunc)
                m_AirFunc();

            if (m_AirInst && m_AirDelegate)
                (m_AirInst->*m_AirDelegate)();
        }
    }

    void SetWall(bool _Wall)
    {
        if (m_Wall == _Wall)
            return;

        m_Wall = _Wall;

        if (m_Wall)
        {
            if (m_WallInst && m_WallDelegate)
                (m_WallInst->*m_WallDelegate)();
        }
        else
        {
            if (m_WallOffInst && m_WallOffDelegate)
                (m_WallOffInst->*m_WallOffDelegate)();
        }
    }

    bool IsGround() { return m_Ground; }
    bool IsWall() { return m_Wall; }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);
public:
    CRigidBody();
    CRigidBody(const CRigidBody& _Other);
    ~CRigidBody();
};

