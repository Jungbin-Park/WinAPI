#pragma once
#include "CState.h"
class BDownState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(BDownState);
public:
    BDownState();
    ~BDownState();
};

