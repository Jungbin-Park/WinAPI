#pragma once
#include "CState.h"

class CMoveState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CMoveState);
public:
    CMoveState();
    ~CMoveState();
};

