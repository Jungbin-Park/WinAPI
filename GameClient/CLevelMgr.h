#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];	
	CLevel*		m_pCurrentLevel;	// ���� level pointer
	// ������ ���� -> �θ�(�Ŵ���) �����ͷ� �ڽ�(����) �����͸� ����ų �� ����

public:
	CObj* FindObjectByName(const wstring& _strName);
	
public:
	void init();
	void progress();
	void render();

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
};

