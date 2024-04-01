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
	CTile* pTile = new CTile;
	pTile->SetRowCol(10, 10);
	pTile->SetAtlasTex(CAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	AddObject(LAYER_TYPE::TILE, pTile);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
}


