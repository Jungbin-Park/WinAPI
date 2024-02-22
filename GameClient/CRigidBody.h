#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
public:
    virtual void finaltick() override;

private:
    CRigidBody();
    ~CRigidBody();
};

