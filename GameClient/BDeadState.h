#pragma once
#include "CState.h"
class BDeadState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(BDeadState);
public:
    BDeadState();
    ~BDeadState();
};

