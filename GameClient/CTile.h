#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
private:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CTile);

public:
    CTile();
    //CTile(const CTile& _Other);
    ~CTile();
};

