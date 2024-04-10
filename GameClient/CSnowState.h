#pragma once
#include "CState.h"

class CSnowState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CSnowState);
public:
    CSnowState();
    ~CSnowState();
};

