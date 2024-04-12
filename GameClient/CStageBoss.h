#pragma once
#include "CObj.h"

class CStageBoss :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:

    CLONE(CStageBoss)
public:
    CStageBoss();
    ~CStageBoss();
};

