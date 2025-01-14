#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{   
private:
    HDC         m_hDC;
    HBITMAP     m_hBit;
    BITMAP      m_Info;

public:
    virtual int Load(const wstring& _strFilePath) override;
    int Create(UINT _Width, UINT _Height);

public:
    HDC GetDC() { return m_hDC; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }


public:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

