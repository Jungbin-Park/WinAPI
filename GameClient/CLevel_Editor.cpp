#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"

#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTile.h"


CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
	, m_hMenu(nullptr)
{
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_GAMECLIENT));
}

CLevel_Editor::~CLevel_Editor()
{
	DestroyMenu(m_hMenu);
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

	else if (KEY_TAP(KEY::T))
	{
		m_EditTile->SaveToFile(L"tile\\TestTile.tile");
	}

	else if (KEY_TAP(KEY::Y))
	{
		m_EditTile->LoadFromFile(L"tile\\TestTile.tile");
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	// 에디터 전용 메뉴 추가
	SetMenu(CEngine::GetInst()->GetMainWnd(), m_hMenu);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution(), true);

	// 타일 추가
	m_EditTile = new CTile;
	m_EditTile->SetPos(Vec2(100.f, 100.f));

	m_EditTile->SetRowCol(10, 10);
	m_EditTile->SetAtlasTex(CAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	AddObject(LAYER_TYPE::TILE, m_EditTile);
}

void CLevel_Editor::Exit()
{
	// 에디터 전용 메뉴 제거
	SetMenu(CEngine::GetInst()->GetMainWnd(), nullptr);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution(), false);

	DeleteAllObjects();
}

void CLevel_Editor::OpenSaveTile()
{
	wchar_t szSelect[256] = {};

	OPENFILENAME ofn = {};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	ofn.lpstrFilter = L"Tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// 탐색창 초기 위치 지정
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += L"tile\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		m_EditTile->SaveToFile(szSelect);
	}
}

void CLevel_Editor::OpenLoadTile()
{
	wchar_t szSelect[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	ofn.lpstrFilter = L"Tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// 탐색창 초기 위치 지정
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += L"tile\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		m_EditTile->LoadFromFile(szSelect);
	}
}

// Dialog Procedure Function
INT_PTR CALLBACK TileInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
	{
		// 다이얼로그 초기화 작업 메세지
		// 현재 레벨을 가져와서 에디터 레벨이 맞는지 확인
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		// 에디터 레벨에 있는 Tile Object 의 정보를 가져와서, EditControl 에 데이터 입력
		CTile* pTile = pEditorLevel->GetEditTile();
		Vec2 vPos = pTile->GetPos();
		UINT Row = pTile->GetTileRow();
		UINT Col = pTile->GetTileCol();

		SetDlgItemInt(hDlg, IDC_ROW, Row, true);
		SetDlgItemInt(hDlg, IDC_COL, Col, true);

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, 256, L"%f", vPos.x);
		SetDlgItemText(hDlg, IDC_TILEX, szBuff);

		swprintf_s(szBuff, 256, L"%f", vPos.y);
		SetDlgItemText(hDlg, IDC_TILEY, szBuff);
	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// 다이얼로그 초기화 작업 메세지
			// 현재 레벨을 가져와서 에디터 레벨이 맞는지 확인
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// 에디터 레벨에 있는  EditControl 의 정보를 가져와서, Tile Object 에 적용
			CTile* pTile = pEditorLevel->GetEditTile();

			UINT Row = 0, Col = 0;
			Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
			Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);

			pTile->SetRowCol(Row, Col);

			wchar_t szBuff[256] = {};
			Vec2 vPos;

			GetDlgItemText(hDlg, IDC_TILEX, szBuff, 256);
			vPos.x = (float)_wtof(szBuff);

			GetDlgItemText(hDlg, IDC_TILEY, szBuff, 256);
			vPos.y = (float)_wtof(szBuff);

			pTile->SetPos(vPos);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


