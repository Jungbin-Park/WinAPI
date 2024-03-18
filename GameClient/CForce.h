#pragma once
#include "CObj.h"

class CForce :
    public CObj
{
private:
    float   m_Force;    // 힘의 크기
    float   m_Range;    // 힘의 범위
    float   m_Time;     // 힘이 유지되는 시간

    float   m_Age;

public:
    void SetForce(float _Force, float _Range, float _Time)
    {
        m_Force = _Force;
        m_Range = _Range;
        m_Time = _Time;
    }

public:
    virtual void tick() override;

private:
    void AddForce(LAYER_TYPE _type);

    CLONE(CForce);

public:
    CForce();
    ~CForce();
};

