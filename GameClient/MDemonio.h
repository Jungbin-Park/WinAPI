#pragma once
#include "CMonster.h"

class MDemonio :
    public CMonster
{
public:
    MDemonio();
    MDemonio(Vec2(_Pos), Vec2(_Scale));
    ~MDemonio();

private:
    float           m_DetectRange;  // Å½Áö ¹üÀ§
    float           m_Speed;

    Vec2            m_Data;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    eDirection      m_Direction;

public:
    void SetDirection(eDirection _Dir) { m_Direction = _Dir; }

    CCollider* GetCollider() { return m_Collider; }
    CAnimator* GetAnimator() { return m_Animator; }
    eDirection GetDirection() { return m_Direction; }
    CFSM* GetFSM() { return m_FSM; }

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(MDemonio)
};

