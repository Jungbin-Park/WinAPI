#pragma once
#include "CState.h"
class BJumpState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(BJumpState);
public:
    BJumpState();
    ~BJumpState();
};

