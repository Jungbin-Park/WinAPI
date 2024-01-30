#pragma once
#include "CEntity.h"

class CObj;

class CLevel : public CEntity
{
private:
    vector<CObj*>   m_vecObj;

public:
    // ���� �Լ�
    void begin();       // ������ ���۵� �� �� �� ȣ��
    void tick();        // �� �����Ӹ��� ȣ��
    void finaltick();   // �� �����Ӹ��� ȣ��
    void render();      // �� �����Ӹ��� ȣ��

public:
    void AddObject(CObj* _Obj)  { m_vecObj.push_back(_Obj); }

public:
    virtual CLevel* Clone() = 0;

public:
    CLevel();
    ~CLevel();
};

