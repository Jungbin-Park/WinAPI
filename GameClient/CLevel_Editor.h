#pragma once
#include "CLevel.h"

class CTile;

class CLevel_Editor :
    public CLevel
{
private:
    CTile* m_EditTile;
    HMENU  m_hMenu;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTile* GetEditTile() { return m_EditTile; }
    void OpenSaveTile();
    void OpenLoadTile();

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

