#pragma once
#include "CEntity.h"

class CObj;

class CLevel : public CEntity
{
private:
    vector<CObj*>   m_arrObj[(UINT)LAYER_TYPE::END];

public:
    // ���� �Լ�
    void begin();       // ������ ���۵� �� �� �� ȣ��
    void tick();        // �� �����Ӹ��� ȣ��
    void finaltick();   // �� �����Ӹ��� ȣ��
    void render();      // �� �����Ӹ��� ȣ��

public:
    void AddObject(LAYER_TYPE _Layer, CObj* _Obj);

public:
    virtual CLevel* Clone() = 0;

public:
    CLevel();
    ~CLevel();
};

