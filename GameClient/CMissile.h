#pragma once
#include "CObj.h"

class CMissile :
    public CObj
{
private:
    float       m_Speed;
    CCollider*  m_Collider;

private:
    virtual void tick() override;
    virtual void render() override;

public:
    virtual CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

