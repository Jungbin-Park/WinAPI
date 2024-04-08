#include "pch.h"
#include "CCollider_Editor.h"

#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CCollider.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"

CCollider_Editor::CCollider_Editor()
	: m_Platform(nullptr)
	, m_TestPlatform(nullptr)
{
	//SetName(L"editor");
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

	// ===========================
	//		  플랫폼 그리기
	// ===========================
	if (KEY_TAP(KEY::LBTN))
	{
		m_TestPlatform = new CPlatform();
		m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		
		m_TestPlatform->SetName(L"TestPlatform");
		AddObject(LAYER_TYPE::PLATFORM, m_TestPlatform);
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_TestInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestPlatform->SetPos((m_TestInfo.StartPos + m_TestInfo.EndPos) * 0.5f) ;
		m_TestPlatform->SetScale(m_TestInfo.EndPos - m_TestInfo.StartPos);
		
		Vec2 tpScale = m_TestPlatform->GetScale();
		m_TestPlatform->GetCollider()->SetScale(tpScale);
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_TestPlatform->Destroy();
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		float x = (m_Info.StartPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.StartPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.StartPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.StartPos.y);

		m_Platform = new CPlatform(Vec2(x, y), Vec2(width, height));
		m_Platform->SetName(L"Platform");
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}


	// ===========================
	//		   벽 그리기
	// ===========================
	if (KEY_TAP(KEY::RBTN))
	{
		m_TestWall = new CWall();
		m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		m_TestWall->SetName(L"TestWall");
		AddObject(LAYER_TYPE::WALL, m_TestWall);
	}
	else if (KEY_PRESSED(KEY::RBTN))
	{
		m_TestInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestWall->SetPos((m_TestInfo.StartPos + m_TestInfo.EndPos) * 0.5f);
		m_TestWall->SetScale(m_TestInfo.EndPos - m_TestInfo.StartPos);

		Vec2 tpScale = m_TestWall->GetScale();
		m_TestWall->GetCollider()->SetScale(tpScale);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		m_TestWall->Destroy();
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		float x = (m_Info.StartPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.StartPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.StartPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.StartPos.y);

		m_Wall = new CWall(Vec2(x, y), Vec2(width, height));
		m_Wall->SetName(L"Wall");
		m_vecEditWall.push_back(m_Wall);
		AddObject(LAYER_TYPE::WALL, m_Wall);
	}

	else if (KEY_TAP(KEY::O))
	{
		SavePlat(L"platform\\platform.plat");
		SaveWall(L"wall\\wall.wall");
	}
	else if (KEY_TAP(KEY::P))
	{
		m_vecEditPlat.clear();
		m_vecEditWall.clear();
		LoadPlat(L"platform\\platform.plat");
		LoadWall(L"wall\\wall.wall");
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CCollider_Editor::Enter()
{
	// 배경 추가 (1440 * 996)
	CObj* pObject = new CStage01;
	pObject->SetName(L"Stage1");
	pObject->SetPos(720.f, 498.f);
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CStage02;
	pObject->SetName(L"Stage2");
	pObject->SetPos(720.f, -498.f);
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CStage03;
	pObject->SetName(L"Stage3");
	pObject->SetPos(720.f, -1494.f);
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

}

void CCollider_Editor::Exit()
{
	DeleteAllObjects();
}


void CCollider_Editor::SavePlat(const wstring& _strRelativePath)
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

void CCollider_Editor::SaveWall(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"wb");

	size_t len = m_vecEditWall.size();
	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos = m_vecEditWall[i]->GetPos();
		Vec2 vScale = m_vecEditWall[i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CCollider_Editor::LoadPlat(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	size_t len;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos, vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		m_Platform = new CPlatform(vPos, vScale);
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}

	fclose(pFile);
}

void CCollider_Editor::LoadWall(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	size_t len;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos, vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		m_Wall = new CWall(vPos, vScale);
		m_vecEditWall.push_back(m_Wall);
		AddObject(LAYER_TYPE::WALL, m_Wall);
	}

	fclose(pFile);
}
