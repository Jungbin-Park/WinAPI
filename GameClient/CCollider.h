#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2    m_OffsetPos;    // 소유 오브젝트로부터 상대적인 좌표
    Vec2    m_Scale;

    Vec2    m_FinalPos;    // 최종 좌표 ( 소유 오브젝트 포지션 + 오프셋 Pos )

    bool    m_Active;
    UINT    m_CollisionCount;

public:
    void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    Vec2 GetFinalPos() { return m_FinalPos; }
    Vec2 GetScale() { return m_Scale; }

    void SetActive(bool _Set) { m_Active = _Set; }

private:
    void BeginOverlap(CCollider* _OtherCollider);
    void OnOverlap(CCollider* _OtherCollider);
    void EndOverlap(CCollider* _OtherCollider);

public:
    virtual void finaltick() override;
    virtual CCollider* Clone() { return new CCollider; }

public:
    CCollider();
    ~CCollider();

    friend class CCollisionMgr;
};

