#pragma once
#include "CObj.h"

class CTexture;

class CMonster :
    public CObj
{
private:
    int             m_HP;
    float           m_DetectRange;  // Å½Áö ¹üÀ§
    float           m_Speed;
    bool            m_bDead;
    bool            m_bSnow;

    Vec2            m_Data;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    eDirection      m_Direction;

    bool            m_StopLeft;
    bool            m_StopRight;

    bool            m_Ground;
    bool            m_Wall;

public:
    void SetDirection(eDirection _Dir) { m_Direction = _Dir; }
    void SetSnow(bool _Val) { m_bSnow = _Val; }

    CCollider* GetCollider() { return m_Collider; }
    CAnimator* GetAnimator() { return m_Animator; }
    eDirection GetDirection() { return m_Direction; }
    bool IsGround() { return m_Ground; }
    bool IsStopLeft() { return m_StopLeft; }
    bool IsStopRight() { return m_StopRight; }
    bool IsWall() { return m_Wall; }
    bool IsSnow() { return m_bSnow; }


public:
    void Jump();

    virtual void begin() override;
    virtual void tick() override;
    //virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CMonster)

private:
    void Ground();
    void Air();
    void SetWall();
    void SetWallOff();


public:
    CMonster();
    CMonster(Vec2(_Pos), Vec2(_Scale));
    ~CMonster();
};

