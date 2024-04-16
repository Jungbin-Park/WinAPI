#pragma once
#include "CState.h"

class MSnowState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(MSnowState);
public:
    MSnowState();
    ~MSnowState();
};

