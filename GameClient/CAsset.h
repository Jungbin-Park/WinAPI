#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    wstring     m_Key;          // 로딩할 때 사용한 키
    wstring     m_RelativePath; // 상대경로

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

public:
    CLONE_DISABLE(CAsset);
    virtual int Load(const wstring& _strFilePath) = 0;      // 추상클래스

public:
    CAsset();
    ~CAsset();

    friend class CAssetMgr;

};

