#pragma once
#include "CMonster.h"

class MRana :
    public CMonster
{
public:
    MRana();
    MRana(Vec2(_Pos), Vec2(_Scale));
    ~MRana();

private:
    Vec2            m_Data;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    eDirection      m_Direction;

public:
    CLONE(MRana)


};

