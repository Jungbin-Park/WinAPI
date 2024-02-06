#pragma once
#include "CEntity.h"

class CObj;
class CCollider;

class CLevel : public CEntity
{
private:
    vector<CObj*>       m_arrObj[(UINT)LAYER_TYPE::END];
    vector<CCollider*>  m_arrCollider[(UINT)LAYER_TYPE::END];

public:
    // 시점 함수
    void begin();       // 레벨이 시작될 때 한 번 호출
    void tick();        // 매 프레임마다 호출
    void finaltick();   // 매 프레임마다 호출
    void render();      // 매 프레임마다 호출

public:
    void AddObject(LAYER_TYPE _Layer, CObj* _Obj);
    void RegisterCollider(CCollider* _Collider);

    const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer)
    {
        return m_arrCollider[(UINT)_Layer];
    }

public:
    virtual CLevel* Clone() = 0;

public:
    CLevel();
    ~CLevel();
};

