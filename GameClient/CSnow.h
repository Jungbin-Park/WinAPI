#pragma once
#include "CObj.h"
class CSnow :
    public CObj
{
private:
    float       m_Speed;
    float       m_Angle;    // ¶óµð¾È

    CCollider* m_Collider;

protected:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetAngle(float _Angle) { m_Angle = _Angle; }

    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; }

    CCollider* GetCollider() { return m_Collider; }

protected:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CSnow);

public:
    CSnow();
    ~CSnow();
};

