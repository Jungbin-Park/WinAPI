#pragma once
#include "CLevel.h"

class CPlatform;
class CWall;

class CLevel_Stage01 
	: public CLevel
{
private:
	CPlatform*			m_Platform;
	CWall*				m_Wall;

	vector<CPlatform*>	m_vecEditPlat;
	vector<CWall*>		m_vecEditWall;

private:
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

