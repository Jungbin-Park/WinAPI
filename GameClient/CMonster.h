#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier) override;

    virtual CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

