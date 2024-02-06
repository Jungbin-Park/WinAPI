#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2    m_OffsetPos;    // ���� ������Ʈ�κ��� ������� ��ǥ
    Vec2    m_Scale;

    Vec2    m_FinalPos;    // ���� ��ǥ (���� ������Ʈ ������ + ������ Pos)

    bool    m_Active;

public:
    void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetActive(bool _Set) { m_Active = _Set; }

public:
    virtual void finaltick() override;
    virtual CCollider* Clone() { return new CCollider; }

public:
    CCollider();
    ~CCollider();
};

