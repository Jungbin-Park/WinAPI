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

public:
    void finaltick();
    void render();

    void Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);

public:
    CLONE(CAnimation);

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

