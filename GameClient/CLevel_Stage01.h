#pragma once
#include "CLevel.h"

class CPlatform;

class CLevel_Stage01 
	: public CLevel
{
private:
	CPlatform* m_Platform;

	vector<CPlatform*> m_vecEditPlat;

private:
	void LoadFromFile(const wstring& _RelativePath);

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLevel_Stage01();
	~CLevel_Stage01();
};

