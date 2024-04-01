#pragma once
#include "CComponent.h"

enum class DATA_TYPE
{
    INT,
    FLOAT,
    VEC2,
    OBJECT,
};

struct tBlackboardData
{
    DATA_TYPE   Type;
    void*       pData;
};

class CState;

// FSM (Finite State Machine)
class CFSM :
    public CComponent
{
private:
    static map<wstring, tBlackboardData>    m_mapGlobalData; // 전역 데이터

private:
    map<wstring, tBlackboardData>           m_mapData;  // 각 객체가 가지는 데이터
    map<wstring, CState*>                   m_mapState; // 상태들
    CState*                                 m_CurState; // 현재 상태

public:
    void AddState(const wstring& _strStateName, CState* _State);
    CState* FindState(const wstring& _strStateName);
    void ChangeState(const wstring& _strNextStateName);

public:
    virtual void finaltick() override;

public:
    CLONE(CFSM);
    CFSM();
    ~CFSM();
};

