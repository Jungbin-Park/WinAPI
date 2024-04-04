#pragma once
#include "CObj.h"
class CStage03 :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:

    CLONE(CStage03)
public:
    CStage03();
    ~CStage03();
};

