#pragma once
#include "CObj.h"

class CTexture;

class CMonster :
    public CObj
{
private:
    int         m_HP;

    CTexture*   m_Img;

    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

public:
    virtual void tick() override;
    //virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;

    virtual CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

