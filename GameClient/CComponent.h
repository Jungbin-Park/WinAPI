#pragma once
#include "CEntity.h"

#include "CObj.h"

class CComponent :
    public CEntity
{
private:
    CObj*       m_Owner;    // 컴포넌트를 소유하고 있는 오브젝트

public:
    virtual void finaltick() = 0;
    virtual CComponent* Clone() = 0;

public:
    CComponent();
    ~CComponent();

    friend class CObj;
};

