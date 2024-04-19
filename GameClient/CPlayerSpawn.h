#pragma once
#include "CObj.h"

class CPlayerSpawn :
    public CObj
{
public:
    CPlayerSpawn();
    ~CPlayerSpawn();

private:
    CAnimator*  m_Animator;
    CObj*       m_Owner;

    bool        m_PlayOnce;

public:
    virtual void begin();
    virtual void tick(); // 오브젝트가 매 프레임마다 해야할 작업을 구현

    CLONE(CPlayerSpawn)
public:
    void SetOwner(CObj* _Owner) { m_Owner = _Owner; }

    CObj* GetOwner() { return m_Owner; }

};

