#pragma once
#include "CObj.h"

class CStage02 :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:

    CLONE(CStage02)
public:
    CStage02();
    ~CStage02();
};

