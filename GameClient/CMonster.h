#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    virtual void tick() override;
    virtual CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

