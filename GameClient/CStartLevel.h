#pragma once
#include "CLevel.h"

class CTexture;

class CStartLevel :
    public CLevel
{
private:
	CTexture* m_Img;
	CTexture* m_Logo;

public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	CStartLevel();
	~CStartLevel();
};

