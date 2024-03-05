#pragma once
#include "CEntity.h"

struct tAnimFrm
{

};

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*      m_Animator;     // Animation을 소유하고 있는 Animator

public:
    void finaltick();
    void render();


public:
    CLONE(CAnimation);

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

