#pragma once
#include "CObj.h"

#include "CTileMap.h"

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

    UINT GetTileRow() { return m_TileMap->GetRow(); }
    UINT GetTileCol() { return m_TileMap->GetCol(); }

    void Clicked(Vec2 _vMousePos);

private:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    void SaveToFile(const wstring& _FullPath);
    void LoadFromFile(const wstring& _FullPath);
    CLONE(CTile);

public:
    CTile();
    //CTile(const CTile& _Other);
    ~CTile();
};

