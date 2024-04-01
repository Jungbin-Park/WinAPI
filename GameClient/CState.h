#pragma once
#include "CEntity.h"

#include "CFSM.h"

class CState :
    public CEntity
{
private:
    CFSM* m_Owner;

protected:
    CObj* GetObj() { return m_Owner->GetOwner(); }
    CFSM* GetFSM() { return m_Owner; }

    template<typename T>
    T& GetBlackboardData(const wstring& _DataName)
    {
        return m_Owner->GetBlackboardData<T>(_DataName);
    }

public:
    virtual void Enter() = 0; // 상태 진입시 할 일
    virtual void FinalTick() = 0; // 상태를 유지하고 있을때 할일
    virtual void Exit() = 0;    // 상태를 벗어날 때

public:
    CState();
    ~CState();

    friend class CFSM;
};

