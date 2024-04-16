#pragma once
#include "CState.h"

class MWakeState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(MWakeState);
public:
    MWakeState();
    ~MWakeState();
};

