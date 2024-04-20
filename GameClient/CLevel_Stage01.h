 #pragma once
#include "CLevel.h"

class CPlayer;
class CMonster;
class CPlatform;
class CWall;
class CSound;
class CPlayerLife;

class CLevel_Stage01 
	: public CLevel
{
private:
	CPlatform*			m_Platform;
	CWall*				m_Wall;
	CPlayerLife*		m_LifeUI;

	vector<CObj*>		m_vecClone;

	vector<CPlatform*>	m_vecEditPlat;
	vector<CWall*>		m_vecEditWall;

	int					m_CurRound;
	int					m_Score;
	int					m_PlayerLife;

private:
	void Start();
	void Clear(int _Level);
	void RoundClear(int _Level);

	void LoadPlat(const wstring& _RelativePath);
	void LoadWall(const wstring& _RelativePath);

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	int GetScore() { return m_Score; }
	int GetLife() { return m_PlayerLife; }

	void AddScore(int _Score) 
	{ 
		m_Score += _Score;
		LOG(LOG_TYPE::DBG_LOG, L"Score +1");
	}
	void SubLife() { m_PlayerLife--; }

public:
	CLevel_Stage01();
	~CLevel_Stage01();
};

