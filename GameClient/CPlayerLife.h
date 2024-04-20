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
    virtual void tick(); // ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����

    CLONE(CPlayerLife)
public:
};

