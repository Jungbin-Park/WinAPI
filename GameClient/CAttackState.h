#pragma once
#include "CState.h"

class CAttackState :
    public CState
{
private:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CAttackState);
public:
    CAttackState();
    ~CAttackState();
};

