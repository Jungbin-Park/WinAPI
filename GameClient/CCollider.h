#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    


public:
    virtual void finaltick() override;
    virtual CCollider* Clone() { return new CCollider; }

public:
    CCollider();
    ~CCollider();
};

