#pragma once
#include "CComponent.h"

typedef void(*CALL_BACK)(void);         // ��ȯ Ÿ���� void �̰� ���ڸ� ���� �ʴ� CALL_BACK ������
typedef void(CObj::*DELEGATE)(void);

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
    bool    m_Wall;                 // ���� �꿴���� üũ
    float   m_JumpSpeed;            // ���� �ӷ�

    Vec2    m_MissileDir;
    float   m_MissileSpeed;

    // Ground On/Off ȣ���ų �Լ� ������(�Լ��� �ּҸ� �޾Ƴ��ٰ� �ʿ��� ������ ȣ��)
    // CallBack : �����Լ�������
    CALL_BACK   m_GroundFunc;
    CALL_BACK   m_AirFunc;
    
    // Delegate : ����Լ�������   (��ü�� �־�� ��)
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

