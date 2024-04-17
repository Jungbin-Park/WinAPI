#pragma once
#include "CObj.h"
class CBoss :
    public CObj
{
private:
    int             m_HP;

    bool            m_Dead;

    CTexture*       m_Atlas;
    CTexture*       m_HitAtlas;

    Vec2            m_Data;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    bool            m_Ground;
    bool            m_Down;

public:
    CCollider* GetCollider() { return m_Collider; }
    CAnimator* GetAnimator() { return m_Animator; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    CFSM* GetFSM() { return m_FSM; }
    bool IsDown() { return m_Down; }

    void SetDown(bool _Val) { m_Down = _Val; }

public:
    void Jump();

    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CBoss)

private:
    void Ground();
    void Air();

public:
    CBoss();
    ~CBoss();
};

