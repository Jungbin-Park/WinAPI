#pragma once
#include "CLevel.h"

class CTile;

class CLevel_Editor :
    public CLevel
{
private:
    CTile* m_EditTile;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Editor();
    ~CLevel_Editor();

};

