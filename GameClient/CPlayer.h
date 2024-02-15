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
    virtual void tick(); // ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
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

