#pragma once
#include "CObj.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObj
{
public:
    enum class eState
    {
        IDLE,
        MOVE,
        ATTACK,
        JUMP,
    };

    enum class eDirection
    {
        Left,
        Right,
    };

private: 
    float       m_Speed;
    CTexture*   m_PlayerImg;

    int         m_JumpCount;
    int         m_CurJumpCount;
    
    CCollider*  m_BodyCol;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

    eState      m_State;
    eDirection  m_Direction;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

private:
    void Idle();
    void Move();
    void Attack();

    void Shoot();
    void Jump();

    void RestoreJumpCount()
    {
        m_CurJumpCount = 0;
    }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

