#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{
    
}

CAssetMgr::~CAssetMgr()
{
    Safe_Del_Map(m_mapTex);
    Safe_Del_Map(m_mapSound);
}

void CAssetMgr::init()
{

}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _strRelativePath)
{
    // 이미 해당 키로 등록된 텍스쳐가 있으면
    CTexture* pTex = FindTexture(_Key);
    if (nullptr != pTex)
    {
        return pTex;
    }

    // Full Path로 만들기
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 객체 생성
    // 텍스쳐 로딩
    pTex = new CTexture;
    if (FAILED(pTex->Load(strFilePath)))
    {
        MessageBox(nullptr, _strRelativePath.c_str(), L"텍스쳐 로딩 실패", MB_OK);
        delete pTex;

        return nullptr;
    }

    // map에 로딩된 텍스쳐를 등록
    m_mapTex.insert(make_pair(_Key, pTex));

    // 텍스쳐 에셋에 본인의 키값과 상대경로를 알려줌
    pTex->m_Key = _Key;
    pTex->m_RelativePath = _strRelativePath;

    return pTex;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
    // 이미 해당 키로 등록된 텍스쳐가 있으면
    assert(!FindTexture(_Key));

    // 텍스쳐 객체 생성
    CTexture* pTex = new CTexture;
    if (FAILED(pTex->Create(_Width, _Height)))
    {
        MessageBox(nullptr, _Key.c_str(), L"텍스쳐 생성 실패", MB_OK);
        delete pTex;
        return nullptr;
    }

    // map에 로딩된 텍스쳐를 등록
    m_mapTex.insert(make_pair(_Key, pTex));

    // 텍스쳐 에셋에 본인의 키값을 알려줌
    pTex->m_Key = _Key;

    return pTex;
}

CTexture* CAssetMgr::FindTexture(const wstring& _Key)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

    if (iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}
