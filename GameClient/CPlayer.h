#pragma once
#include "CObj.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CSnowObj;

class CPlayer :
    public CObj
{
public:
    enum class eState
    {
        IDLE,
        MOVE,
        ATTACK,
    };

private: 
    float           m_Speed;

    int             m_JumpCount;
    int             m_CurJumpCount;

    CSnowObj*       m_OverlappedSnowObj;
    
    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;

    eState          m_State;
    eDirection      m_Direction;

    bool            m_bDead;
    bool            m_bClear;

    bool            m_StopLeft;
    bool            m_StopRight;

    bool            m_Ground;

    bool            m_PushSnow;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

private:
    void Jump();

    void Ground();
    void Air();
    void SetWall();
    void SetWallOff();
    
public:
    void RoundClear();

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

