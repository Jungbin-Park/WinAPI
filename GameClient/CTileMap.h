#pragma once
#include "CComponent.h"

struct tTileInfo
{
    int ImgIdx;

    tTileInfo()
        : ImgIdx(0)
    {}
};

class CTileMap :
    public CComponent
{
private:
    UINT                m_Row;          // 행
    UINT                m_Col;          // 열
    Vec2                m_TileSize;     // 타일 개당 사이즈

    CTexture*           m_AtlasTex;     // 타일이 사용하는 아틀라스 텍스쳐
    UINT                m_MaxImgRow;    // 아틀라스 텍스쳐가 보유하고 있는 타일 이미지 세로(행) 개수
    UINT                m_MaxImgCol;    // 아틀라스 텍스쳐가 보유하고 있는 타일 이미지 가로(열) 개수

    vector<tTileInfo>   m_vecTileInfo;

public:
    void SetRow(UINT _Row);
    void SetCol(UINT _Col);
    void SetRowCol(UINT _Row, UINT _Col);

    UINT GetRow() { return m_Row; }
    UINT GetCol() { return m_Col; }

    void SetAtlasTex(CTexture* _Atlas);
    CTexture* GetAtlasTex() { return m_AtlasTex; }

    void Clicked(Vec2 _vMousePos);

public:
    virtual void finaltick() override;
    void render();

    void SaveToFile(FILE* _File);
    void LoadFromFile(FILE* _File);

private:
    void render_grid();
    void render_tile();

public:
    CLONE(CTileMap);
    CTileMap();
    //CTileMap(const CTileMap& _Collider);
    ~CTileMap();

};

