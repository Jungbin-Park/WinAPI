#pragma once
#include "CLevel.h"

class CWall;
class CPlatform;
class CCamera;

struct CInfo
{
	Vec2 StartPos;
	Vec2 EndPos;
};

class CCollider_Editor :
    public CLevel
{
public:
	CCollider_Editor();
	~CCollider_Editor();


private:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	void SavePlat(const wstring& _RelativePath);
	void SaveWall(const wstring& _RelativePath);
	void LoadPlat(const wstring& _RelativePath);
	void LoadWall(const wstring& _RelativePath);


private:
	CPlatform*		m_Platform;
	CPlatform*		m_TestPlatform;

	CWall*			m_Wall;
	CWall*			m_TestWall;

	CInfo			m_Info;
	CInfo			m_TestInfo;

	vector<CPlatform*>	m_vecEditPlat;
	vector<CWall*>		m_vecEditWall;
};

