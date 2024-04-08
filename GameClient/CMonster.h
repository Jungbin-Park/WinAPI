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

    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;
    CFSM*       m_FSM;

public:
    CCollider* GetCollider() { return m_Collider; }

public:
    virtual void begin() override;
    virtual void tick() override;
    //virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CMonster)

public:
    CMonster();
    CMonster(Vec2(_Pos), Vec2(_Scale));
    ~CMonster();
};

