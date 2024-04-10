#pragma once
#include "CObj.h"

class CSnowObj :
    public CObj
{
public:
    CSnowObj();
    ~CSnowObj();

private:
    float           m_Speed;
    int             m_HitCount;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;

    Vec2            m_Dir;
    eDirection      m_Direction;

    bool            m_Ground;

    bool            m_StopLeft;
    bool            m_StopRight;

    bool            m_bRoll;

public:
    CRigidBody* GetRigidBody() { return m_RigidBody; }

    CLONE(CSnowObj)

public:
    void Shoot(Vec2 _Dir);

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;



};

