#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;  // 보유중인 애니메이션
    CAnimation*                 m_CurAnim;  // 현재 재생할 애니메이션

    bool                        m_Repeat;

public:
    virtual void finaltick() override;
    void render();

    void CreateAnimation(const wstring& _AnimName, CTexture* _Atlas
        , Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);

    CAnimation* FindAnimation(const wstring& _AnimName);
    void LoadAnimation(const wstring& _strRelativeFilePath);

    void Play(const wstring& _AnimName, bool _Repeat);


public:
    CLONE(CAnimator);
    CAnimator();
    CAnimator(const CAnimator& _Other);
    ~CAnimator();
};

