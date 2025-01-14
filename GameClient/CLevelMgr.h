#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];	
	CLevel*		m_pCurrentLevel;	// 현재 level pointer
	// 다형성 적용 -> 부모(매니저) 포인터로 자식(레벨) 포인터를 가리킬 수 있음

public:
	CObj* FindObjectByName(const wstring& _strName);

private:
	void ChangeLevel(LEVEL_TYPE _NextLevelType);
	
public:
	void init();
	void progress();
	void render();

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }

	friend class CTaskMgr;
};

