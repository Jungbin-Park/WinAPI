#pragma once
#include "CState.h"
class BDownState :
    public CState
{
private:
    bool m_bShoot1;
    bool m_bShoot2;
    bool m_bShoot3;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(BDownState);

private:
    void Shoot();

public:
    BDownState();
    ~BDownState();
};

