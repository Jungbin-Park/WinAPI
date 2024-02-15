#pragma once
#include "CObj.h"

class CCollider;

class CPlayer :
    public CObj
{
private: 
    float       m_Speed;

    CTexture*   m_PlayerImg;
    
    CCollider*  m_HeadCol;
    CCollider*  m_BodyCol;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현
    virtual void render();

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    virtual CObj* Clone() override { return new CPlayer(*this); }; // { return new CObj(*this); }

public:
    CPlayer();
    ~CPlayer();
};

