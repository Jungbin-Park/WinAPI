#include "pch.h"
#include "CLevel_Editor.h"

#include "CKeyMgr.h"
#include "CTile.h"

CLevel_Editor::CLevel_Editor()
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
	CLevel::begin();
}

void CLevel_Editor::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	CObj* pTile = new CTile;
	AddObject(LAYER_TYPE::TILE, pTile);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
}


