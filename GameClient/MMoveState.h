#pragma once
#include "CState.h"

class MMoveState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(MMoveState);
public:
    MMoveState();
    ~MMoveState();
};

