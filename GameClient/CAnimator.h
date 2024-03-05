#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;  // 보유중인 애니메이션
    CAnimation*                 m_CurAnim;  // 현재 재생할 애니메이션

public:
    virtual void finaltick() override;
    void render();

    void CreateAnimation(const wstring& _AnimName, CTexture* _Atlas
        , Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);

public:
    CLONE(CAnimator);
    CAnimator();
    ~CAnimator();
};

