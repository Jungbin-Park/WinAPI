#pragma once
#include "CEntity.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

class CComponent;
class CCollider;
class CAnimator;
class CFSM;

class CObj : public CEntity
{
private:
    Vec2                    m_Pos;      // 위치
    Vec2                    m_Scale;    // 크기
    vector<CComponent*>     m_vecCom;   // 보유 컴포넌트들

    LAYER_TYPE              m_Type;     // 소속 레이어

public:
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
    void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }

    CComponent* AddComponent(CComponent* _Component);

    template<typename T>    // 어떤 종류의 컴포넌트를 달라고 할 지 알 수 없으므로 템플릿
    T* GetComponent()
    {
        // 템플릿은 헤더에 구현
        for (size_t i = 0; i < m_vecCom.size(); i++)
        {
            T* pComponent = dynamic_cast<T*>(m_vecCom[i]);

            if (pComponent)
            {
                return pComponent;
            }
        }

        return nullptr;
    }

public:
    virtual void begin();
    virtual void tick();            // 오브젝트가 매 프레임마다 해야할 작업을 구현
    virtual void finaltick() final; // 오브젝트가 소유한 컴포넌트가 매 프레임마다 해야할 작업을 구현
    virtual void render();

public:
    virtual CObj* Clone() = 0; // { return new CObj(*this); }

public:
    CObj();
    ~CObj();

    friend class CLevel;
};

