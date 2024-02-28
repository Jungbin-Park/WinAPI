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
    // ���� �Լ�
    void begin();       // ������ ���۵� �� �� �� ȣ��
    void tick();        // �� �����Ӹ��� ȣ��
    void finaltick();   // �� �����Ӹ��� ȣ��
    void render();      // �� �����Ӹ��� ȣ��

public:
    void AddObject(LAYER_TYPE _Layer, CObj* _Obj);
    void RegisterCollider(CCollider* _Collider);
    CObj* FindObjectByName(const wstring& _Name);
    CObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

    // const reference : ������ �� ���� + ���� ��� ���̱� ����
    const vector<CObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer){ return m_arrCollider[(UINT)_Layer]; }

public:
    virtual CLevel* Clone() = 0;

public:
    CLevel();
    ~CLevel();
};

