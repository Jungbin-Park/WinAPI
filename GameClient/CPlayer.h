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
    virtual void tick(); // ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
    virtual void render();

public:
    virtual CObj* Clone() override { return new CPlayer(*this); }; // { return new CObj(*this); }

public:
    CPlayer();
    ~CPlayer();
};

