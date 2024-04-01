#include "pch.h"
#include "CLevel_Editor.h"

#include "CKeyMgr.h"
#include "CTile.h"

CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
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

	// 마우스 클릭 발생 시, 타일 오브젝트에게 알림
	if (KEY_TAP(KEY::LBTN))
	{
		m_EditTile->Clicked(CKeyMgr::GetInst()->GetMousePos());
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	m_EditTile = new CTile;
	m_EditTile->SetPos(Vec2(100.f, 100.f));

	m_EditTile->SetRowCol(10, 10);
	m_EditTile->SetAtlasTex(CAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	AddObject(LAYER_TYPE::TILE, m_EditTile);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
}


