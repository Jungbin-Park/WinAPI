#pragma once
#include "CState.h"

class PIdleState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(PIdleState);
public:
    PIdleState();
    ~PIdleState();
};

