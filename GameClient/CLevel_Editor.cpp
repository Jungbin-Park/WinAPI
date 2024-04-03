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

	// ���콺 Ŭ�� �߻� ��, Ÿ�� ������Ʈ���� �˸�
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
	// ������ ���� �޴� �߰�
	SetMenu(CEngine::GetInst()->GetMainWnd(), m_hMenu);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution(), true);

	// Ÿ�� �߰�
	m_EditTile = new CTile;
	m_EditTile->SetPos(Vec2(100.f, 100.f));

	m_EditTile->SetRowCol(10, 10);
	m_EditTile->SetAtlasTex(CAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	AddObject(LAYER_TYPE::TILE, m_EditTile);
}

void CLevel_Editor::Exit()
{
	// ������ ���� �޴� ����
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

	// Ž��â �ʱ� ��ġ ����
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

	// Ž��â �ʱ� ��ġ ����
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
		// ���̾�α� �ʱ�ȭ �۾� �޼���
		// ���� ������ �����ͼ� ������ ������ �´��� Ȯ��
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		// ������ ������ �ִ� Tile Object �� ������ �����ͼ�, EditControl �� ������ �Է�
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
			// ���̾�α� �ʱ�ȭ �۾� �޼���
			// ���� ������ �����ͼ� ������ ������ �´��� Ȯ��
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// ������ ������ �ִ�  EditControl �� ������ �����ͼ�, Tile Object �� ����
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


