#pragma once
#include "CState.h"

class MBallState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(MBallState);
public:
    MBallState();
    ~MBallState();
};

