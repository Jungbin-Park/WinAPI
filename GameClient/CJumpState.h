#pragma once
#include "CState.h"

class CJumpState :
    public CState
{
private:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CJumpState);
public:
    CJumpState();
    ~CJumpState();
};

