#pragma once
#include "CObj.h"

class CTexture;

class CMonster :
    public CObj
{
private:
    int         m_HP;
    float       m_DetectRange;  // Å½Áö ¹üÀ§
    float       m_Speed;

    Vec2        m_Data;

    CTexture*   m_Img;

    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;
    CFSM*       m_FSM;

public:
    virtual void begin() override;
    virtual void tick() override;
    //virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;

    virtual CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

