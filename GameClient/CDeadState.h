#pragma once
#include "CState.h"

class CDeadState :
    public CState
{
private:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CDeadState);
public:
    CDeadState();
    ~CDeadState();
};

