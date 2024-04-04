#pragma once
#include "CObj.h"

class CStage01 :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:
    
    CLONE(CStage01)
public:
    CStage01();
    ~CStage01();
};

