#pragma once
#include "CEntity.h"

// 한 장면의 프레임
struct tAnimFrm
{
    Vec2    StartPos;
    Vec2    SliceSize;
    float   Duration;   // 프레임 유지 시간
};

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_Animator;     // Animation을 소유하고 있는 Animator
    CTexture*           m_Atlas;        // Animation 이미지를 보유하고 있는 Atlas Texture
    vector<tAnimFrm>    m_vecFrm;       // 각 프레임 정보

    float               m_Time;         // 누적시간 체크

    int                 m_CurFrmIdx;    // 현재 프레임
    bool                m_bFinish;      // 애니메이션 재생이 종료됨을 알림

public:
    void finaltick();
    void render();

    void Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
    bool IsFinish() { return m_bFinish; }

    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

public:
    CLONE(CAnimation);

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

