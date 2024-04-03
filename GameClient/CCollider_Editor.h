#pragma once
#include "CLevel.h"

class CTile;
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
	void SaveToFile(const wstring& _RelativePath);
	void LoadFromFile(const wstring& _RelativePath);


private:
	CTile*			m_EditTile;

	CPlatform*		m_Platform;
	CPlatform*		m_TestPlatform;

	CInfo			m_Info;
	CInfo			m_TestInfo;

	vector<CPlatform*> m_vecEditPlat;
};

