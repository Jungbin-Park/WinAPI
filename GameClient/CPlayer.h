#pragma once
#include "CObj.h"

class CCollider;

class CPlayer :
    public CObj
{
private:
    float       m_Speed;

    CCollider* m_Collider;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현
    virtual void render();

public:
    virtual CObj* Clone() override { return new CPlayer(*this); }; // { return new CObj(*this); }

public:
    CPlayer();
    ~CPlayer();
};

