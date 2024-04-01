#pragma once
#include "CObj.h"

class CTileMap;

class CTile :
    public CObj
{
private:
    CTileMap* m_TileMap;

public:
    void SetRow(UINT _Row);
    void SetCol(UINT _Col);
    void SetRowCol(UINT _Row, UINT _Col);

    void SetAtlasTex(CTexture* _Atlas);

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

