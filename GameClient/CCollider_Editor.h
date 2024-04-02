#pragma once
#include "CLevel.h"

class CTile;
class CPlatform;
class CCamera;

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
	void SaveToFile(const wstring& _strRelativePath);


private:
	CTile*			m_EditTile;

	CPlatform*		m_TestPlatform;
	CInfo			m_TestInfo;
};

