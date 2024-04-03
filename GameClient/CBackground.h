#pragma once
#include "CObj.h"
class CBackground :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:
    
    CLONE(CBackground)
public:
    CBackground();
    ~CBackground();
};

