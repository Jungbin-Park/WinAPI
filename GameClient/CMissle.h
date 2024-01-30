#pragma once
#include "CObj.h"

class CMissle :
    public CObj
{
private:
    float       m_Speed;

private:
    virtual void tick() override;

public:
    virtual CMissle* Clone() { return new CMissle(*this); }

public:
    CMissle();
    ~CMissle();
};

