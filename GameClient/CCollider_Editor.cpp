#include "pch.h"
#include "CCollider_Editor.h"

#include "CKeyMgr.h"
#include "CTile.h"

#include "CPathMgr.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CBackground.h"

#include "CUI.h"
#include "CButton.h"

CCollider_Editor::CCollider_Editor()
	: m_EditTile(nullptr)
{
	SetName(L"editor");
}

CCollider_Editor::~CCollider_Editor()
{
}

void CCollider_Editor::begin()
{
	CLevel::begin();
}

void CCollider_Editor::tick()
{
	CLevel::tick();

	// 마우스 클릭 발생 시, 타일 오브젝트에게 알림
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	m_EditTile->Clicked(qKeyMgr::GetInst()->GetMousePos());
	//}


	// 콜라이더 그리기
	if (KEY_TAP(KEY::LBTN))
	{
		m_TestPlatform = new CPlatform();
		m_Info.startPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestInfo.startPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestPlatform->SetPos(m_TestInfo.startPos);
		m_TestPlatform->SetName(L"Test");
		AddObject(LAYER_TYPE::PLATFORM, m_TestPlatform);

	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_TestInfo.EndPos = CCamera::GetInst()->GetRenderPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestPlatform->SetScale(m_TestInfo.EndPos);
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_TestPlatform->Destroy();
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		float x = (m_Info.startPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.startPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.startPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.startPos.y);

		m_Platform = new qPlatform(Vec2(x, y), Vec2(width, height));
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}

	else if (KEY_TAP(KEY::O))
	{
		SaveToFile(L"platform\\platform.plat");
	}
	else if (KEY_TAP(KEY::P))
	{
		m_vecEditPlat.clear();
		LoadFromFile(L"platform\\platform.plat");
	}



	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CCollider_Editor::Enter()
{
	//m_EditTile = new qTile;
	//m_EditTile->SetPos(Vec2(100.f, 100.f));

	//m_EditTile->SetRowCol(10, 10);
	//m_EditTile->SetAtlasTex(qAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	//AddObject(LAYER_TYPE::TILE, m_EditTile);


	//Background
	CObj* pBack = new CBackground;
	pBack->SetName(L"Stage1");
	pBack->SetPos(0.0f, 0.f);
	pBack->SetScale(1.3f, 1.3f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

}

void CCollider_Editor::Exit()
{
	DeleteAllObjects();
}


void CCollider_Editor::SaveToFile(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"wb");

	size_t len = m_vecEditPlat.size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos = m_vecEditPlat[i]->GetPos();
		Vec2 vScale = m_vecEditPlat[i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}
