#pragma once
#include "CObj.h"

class CMonster;

class CSnowObj :
    public CObj
{
public:
    CSnowObj();
    ~CSnowObj();

private:
    CMonster*       m_Owner;

    bool            m_Active;
    float           m_Speed;
    int             m_WallHitCount;
    int             m_SnowHitCount;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;

    Vec2            m_Dir;
    eDirection      m_Direction;

    bool            m_Ground;

    bool            m_StopLeft;
    bool            m_StopRight;

    bool            m_bRoll;
    bool            m_bBoom;

public:
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    CAnimator* GetAnimator() { return m_Animator; }
    CMonster* GetOwner() { return m_Owner; }

    bool IsActive() { return m_Active; }
    bool IsRoll() { return m_bRoll; }

    void SetOwner(CMonster* _Owner) { m_Owner = _Owner; }

    CLONE(CSnowObj)

public:
    void Shoot(Vec2 _Dir);

private:
    void Boom();

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;



};

