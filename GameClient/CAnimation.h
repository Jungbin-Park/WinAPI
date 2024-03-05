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
    CAnimator*      m_Animator;     // Animation�� �����ϰ� �ִ� Animator

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

