#pragma once
#include "CObj.h"

class CAnimator;


class CSnow :
    public CObj
{
private:
    float       m_Speed;

    eDirection  m_Direction;

    CCollider*  m_Collider;
    CRigidBody* m_RigidBody;

    CAnimator*  m_Animator;

    bool        m_PlayOnce;

public:
    void SetDirection(eDirection _Dir) { m_Direction = _Dir; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

    float GetSpeed() { return m_Speed; }
    CCollider* GetCollider() { return m_Collider; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

protected:
    virtual void tick() override;

public:
    CLONE(CSnow);

public:
    CSnow();
    ~CSnow();
};

