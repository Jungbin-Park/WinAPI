#pragma once
#include "CObj.h"

class CPlayerLife :
    public CObj
{
public:
    CPlayerLife();
    ~CPlayerLife();

private:
    CAnimator* m_Animator;

    bool        m_PlayOnce;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현

    CLONE(CPlayerLife)
public:
};

