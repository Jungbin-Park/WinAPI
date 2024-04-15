#pragma once
#include "CState.h"

class MIdleState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(MIdleState);
public:
    MIdleState();
    ~MIdleState();
};

