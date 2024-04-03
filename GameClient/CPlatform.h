#pragma once
#include "CObj.h"

class CPlatform :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    CCollider* GetCollider() { return m_Collider; }

public:
    virtual void tick();
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CPlatform)
public:
    CPlatform();
    CPlatform(Vec2(_StartPos), Vec2(_EndPos));
    ~CPlatform();
};

