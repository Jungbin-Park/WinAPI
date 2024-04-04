#include "pch.h"
#include "CLevel_Stage01.h"
#include "CCollider_Editor.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CForce.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"

#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"

CLevel_Stage01::CLevel_Stage01()
{
}

CLevel_Stage01::~CLevel_Stage01()
{
	
}



void CLevel_Stage01::begin()
{
	CLevel::begin();
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 0.2f);
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.2f);
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		/*Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = CCamera::GetInst()->GetRealPos(vMousePos);

		CForce* pForce = new CForce;
		pForce->SetPos(vPos);
		pForce->SetForce(1000.f, 300.f, 0.3f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);*/
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::COLLIDER_EDITOR);
	}

	
	if (KEY_TAP(KEY::P))
	{
		m_vecEditPlat.clear();
		LoadFromFile(L"platform\\platform.plat");
	}

	if (KEY_TAP(KEY::_1))
	{
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, 498.f));
	}

	if (KEY_TAP(KEY::_2))
	{
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -498.f));
	}

	if (KEY_TAP(KEY::_3))
	{
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -1494.f));
	}
}

void CLevel_Stage01::Enter()
{
	// 플랫폼 생성
	LoadFromFile(L"platform\\platform.plat");

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


	// 레벨에 플레이어 추가
	pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(640.f, 600.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	/*CObj* pPlayerClone = pObject->Clone();
	pPlayerClone->SetPos(800.f, 400.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);*/

	// 몬스터 추가
	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.f, 200.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);


	// 플랫폼 생성
	pObject = new CPlatform;
	pObject->SetName(L"Platform1");
	pObject->SetPos(Vec2(720.f, 900.f));
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
}

void CLevel_Stage01::Exit()
{
	// 레벨에 있는 모든 오브젝트 삭제한다
	DeleteAllObjects();

	// Dontdestroy 할 것들은 예외처리
}

void CLevel_Stage01::LoadFromFile(const wstring& _RelativePath)
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
