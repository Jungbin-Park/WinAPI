#pragma once
#include "CObj.h"

class CForce :
    public CObj
{
private:
    float   m_Force;    // ���� ũ��
    float   m_Range;    // ���� ����
    float   m_Time;     // ���� �����Ǵ� �ð�

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

