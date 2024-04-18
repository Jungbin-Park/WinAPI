#pragma once

class CTexture;
class CSound;

class CAssetMgr
{
	SINGLE(CAssetMgr);
private:
	map<wstring, CTexture*> m_mapTex;
	map<wstring, CSound*>	m_mapSound;

public:
	void init();

	CTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);
	CTexture* FindTexture(const wstring& _Key);

	CSound* LoadSound(const wstring& _Key, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _Key);
};

