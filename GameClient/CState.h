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

    void* GetBlackboardData(const wstring& _DataName)
    {
        //return m_Owner->GetBlackboardData(_DataName);
    }

public:
    virtual void Enter() = 0; // ���� ���Խ� �� ��
    virtual void FinalTick() = 0; // ���¸� �����ϰ� ������ ����
    virtual void Exit() = 0;    // ���¸� ��� ��

public:
    CState();
    ~CState();

    friend class CFSM;
};

