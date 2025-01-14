#pragma once
#include "CState.h"

class BIdleState :
    public CState
{
private:
    CSound* m_Sound;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(BIdleState);
public:
    BIdleState();
    ~BIdleState();
};

