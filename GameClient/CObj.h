#pragma once
#include "CEntity.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CCamera.h"

class CComponent;
class CCollider;
class CAnimator;
class CRigidBody;
class CFSM;

enum class eDirection
{
    None,
    Left,
    Right,
};

class CObj : public CEntity
{
private:
    Vec2                    m_Pos;      // 위치
    Vec2                    m_PrevPos;  // 이전 프레임에서의 위치
    Vec2                    m_Scale;    // 크기
    vector<CComponent*>     m_vecCom;   // 보유 컴포넌트들

    CAnimator*              m_Animator;
    eDirection              m_Direction;

    LAYER_TYPE              m_Type;     // 소속 레이어
    bool                    m_bDead;    // 삭제 예정상태

    
public:
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
    void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }
    void SetDirection(eDirection _Dir) { m_Direction = _Dir; }

    void Dead(bool _Val) { m_bDead = _Val; }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetPrevPos() { return m_PrevPos; }
    Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
    Vec2 GetScale() { return m_Scale; }
    LAYER_TYPE GetLayerType() { return m_Type; }
    eDirection GetDirection() { return m_Direction; }

    bool IsDead() { return m_bDead; }

    void Destroy();

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

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}

public:
    virtual CObj* Clone() = 0;

public:
    CObj();
    CObj(const CObj& _Other);
    ~CObj();

    friend class CLevel;
    friend class CTaskMgr;
};

