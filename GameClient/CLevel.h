#pragma once
#include "CEntity.h"

class CObj;

class CLevel : public CEntity
{
private:
    vector<CObj*>   m_vecObj;

public:
    // 시점 함수
    void begin();       // 레벨이 시작될 때 한 번 호출
    void tick();        // 매 프레임마다 호출
    void finaltick();   // 매 프레임마다 호출
    void render();      // 매 프레임마다 호출

public:
    void AddObject(CObj* _Obj)  { m_vecObj.push_back(_Obj); }

public:
    virtual CLevel* Clone() = 0;

public:
    CLevel();
    ~CLevel();
};

