#pragma once
#include "CObj.h"

class CWall :
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

    CLONE(CWall)
public:
    CWall();
    CWall(Vec2(_Pos), Vec2(_Scale));
    ~CWall();
};

