#pragma once
#include "CEntity.h"

// �� ����� ������
struct tAnimFrm
{
    Vec2    StartPos;
    Vec2    SliceSize;
    float   Duration;   // ������ ���� �ð�
};

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_Animator;     // Animation�� �����ϰ� �ִ� Animator
    CTexture*           m_Atlas;        // Animation �̹����� �����ϰ� �ִ� Atlas Texture
    vector<tAnimFrm>    m_vecFrm;       // �� ������ ����

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

