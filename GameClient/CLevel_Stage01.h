#pragma once
#include "CLevel.h"

class CPlayer;
class CMonster;
class CPlatform;
class CWall;

class CLevel_Stage01 
	: public CLevel
{
private:
	CPlatform*			m_Platform;
	CWall*				m_Wall;

	vector<CObj*>		m_vecClone;

	vector<CPlatform*>	m_vecEditPlat;
	vector<CWall*>		m_vecEditWall;

	int					m_CurRound;

private:
	void Start(int _Level);
	void Clear(int _Level);

	void LoadPlat(const wstring& _RelativePath);
	void LoadWall(const wstring& _RelativePath);

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLevel_Stage01();
	~CLevel_Stage01();
};

