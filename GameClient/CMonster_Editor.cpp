#include "pch.h"
#include "CMonster_Editor.h"

#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CMonster.h"

#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"

CMonster_Editor::CMonster_Editor()
	: m_TestMonster(nullptr)
	, m_Monster(nullptr)
{
}

CMonster_Editor::~CMonster_Editor()
{
}

void CMonster_Editor::begin()
{
	CLevel::begin();
}

void CMonster_Editor::tick()
{
	CLevel::tick();

	// 콜라이더 그리기
	if (KEY_TAP(KEY::LBTN))
	{
		m_TestMonster = new CMonster();
		m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		m_TestMonster->SetName(L"TestMon");
		AddObject(LAYER_TYPE::MONSTER, m_TestMonster);
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_TestInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_TestMonster->SetPos((m_TestInfo.StartPos + m_TestInfo.EndPos) * 0.5f);
		m_TestMonster->SetScale(m_TestInfo.EndPos - m_TestInfo.StartPos);

		Vec2 tpScale = m_TestMonster->GetScale();
		m_TestMonster->GetCollider()->SetScale(tpScale);
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_TestMonster->Destroy();
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

		float x = (m_Info.StartPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.StartPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.StartPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.StartPos.y);

		m_Monster = new CMonster(Vec2(x, y), Vec2(width, height));
		m_vecEditMon.push_back(m_Monster);
		AddObject(LAYER_TYPE::MONSTER, m_Monster);
	}

	else if (KEY_TAP(KEY::O))
	{
		SaveToFile(L"monster\\monster.mon");
	}
	else if (KEY_TAP(KEY::P))
	{
		m_vecEditMon.clear();
		LoadFromFile(L"monster\\monster.mon");
	}


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CMonster_Editor::Enter()
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

void CMonster_Editor::Exit()
{
	DeleteAllObjects();
}

void CMonster_Editor::SaveToFile(const wstring& _RelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"wb");

	size_t len = m_vecEditMon.size();
	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos = m_vecEditMon[i]->GetPos();
		Vec2 vScale = m_vecEditMon[i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CMonster_Editor::LoadFromFile(const wstring& _RelativePath)
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

		m_Monster = new CMonster(vPos, vScale);
		m_vecEditMon.push_back(m_Monster);
		AddObject(LAYER_TYPE::MONSTER, m_Monster);
	}

	fclose(pFile);
}
