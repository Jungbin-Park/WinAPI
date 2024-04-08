#pragma once
#include "CLevel.h"

class CMonster;
class CCamera;

struct CInfo
{
	Vec2 StartPos;
	Vec2 EndPos;
};

class CMonster_Editor :
    public CLevel
{
public:
	CMonster_Editor();
	~CMonster_Editor();


private:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	void SaveToFile(const wstring& _RelativePath);
	void LoadFromFile(const wstring& _RelativePath);


private:
	CMonster*		m_TestMonster;
	CMonster*		m_Monster;

	CInfo			m_Info;
	CInfo			m_TestInfo;

	vector<CMonster*> m_vecEditMon;
};

