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
    virtual void begin();       // 레벨이 시작될 때 한 번 호출
    virtual void tick();        // 매 프레임마다 호출
    virtual void finaltick();   // 매 프레임마다 호출
    virtual void render();      // 매 프레임마다 호출

    virtual void Enter() = 0;   // 레벨이 전환되고 처음 초기화 작업
    virtual void Exit() = 0;    // 레벨이 끝날 때 할 일

public:
    void AddObject(LAYER_TYPE _Layer, CObj* _Obj);
    void RegisterCollider(CCollider* _Collider);
    CObj* FindObjectByName(const wstring& _Name);
    CObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

    // const reference : 수정할 수 없이 + 복사 비용 줄이기 위해
    const vector<CObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer){ return m_arrCollider[(UINT)_Layer]; }

protected:
    void DeleteAllObjects();
    void DeleteObjects(LAYER_TYPE _LayerType);

public:
    CLONE_DISABLE(CLevel);

public:
    CLevel();
    ~CLevel();
};

