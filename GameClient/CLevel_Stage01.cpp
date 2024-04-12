#include "pch.h"
#include "CLevel_Stage01.h"
#include "CCollider_Editor.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"

#include "CForce.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CSnowObj.h"

#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CStageBoss.h"

CLevel_Stage01::CLevel_Stage01()
	: m_Platform(nullptr)
{
}

CLevel_Stage01::~CLevel_Stage01()
{
	Safe_Del_Vec(m_vecClone);
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

	// 몬스터 전체 목록을 받아옴
	/*CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMonster = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);*/

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::COLLIDER_EDITOR);
	}

	if (KEY_TAP(KEY::_1))
	{
		Clear(1);
	}

	if (KEY_TAP(KEY::_2))
	{
		Clear(2);
	}

	if (KEY_TAP(KEY::_3))
	{
		Clear(3);
	}

}

void CLevel_Stage01::Enter()
{
	// ============================
	//			플랫폼 생성
	// ============================

	LoadPlat(L"platform\\platform.plat");
	LoadWall(L"wall\\wall.wall");


	// ============================
	//    배경 추가 (1440 * 996)
	// ============================

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

	pObject = new CStageBoss;
	pObject->SetName(L"StageBoss");
	pObject->SetPos(720.f, -2490.f);
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

	// ============================
	//		  레벨 충돌 설정
	// ============================

	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::PLATFORM);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::WALL);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::SNOW);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::PLAYER);

	Start(1);
}

void CLevel_Stage01::Exit()
{
	// 레벨에 있는 모든 오브젝트 삭제
	DeleteAllObjects();

	// Dontdestroy 할 것들은 예외처리
}


void CLevel_Stage01::Start(int _Level)
{
	switch (_Level)
	{
	case 1:
	{
		// ============================
		//		  플레이어 추가
		// ============================

		CObj* pObject = new CPlayer;
		pObject->SetName(L"Player");
		pObject->SetPos(200.f, 860.f);
		pObject->SetScale(80.f, 128.f);
		AddObject(LAYER_TYPE::PLAYER, pObject);
		//SpawnObject(this, LAYER_TYPE::PLAYER, pObject);

		// 클론 생성
		for (size_t i = 0; i < 4; i++)
		{
			CObj* pPlayerClone = pObject->Clone();
			m_vecClone.push_back(pPlayerClone);
		}

		// ============================
		//			몬스터 추가
		// ============================

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(100.f, 400.f);
		pObject->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pObject);

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(700.f, 800.f);
		pObject->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pObject);

		break;
	}
	case 2:
	{
		// ============================
		//		  플레이어 추가
		// ============================
		CObj* pClone = m_vecClone.back();
		m_vecClone.pop_back();
		pClone->SetName(L"Player");
		pClone->SetPos(200.f, -136.f);
		//AddObject(LAYER_TYPE::PLAYER, pClone);
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);

		// ============================
		//			몬스터 추가
		// ============================

		break;
	}
	case 3:
	{
		// ============================
		//		  플레이어 추가
		// ============================
		CObj* pClone = m_vecClone.back();
		m_vecClone.pop_back();
		pClone->SetName(L"Player");
		pClone->SetPos(200.f, -1132.f);
		//AddObject(LAYER_TYPE::PLAYER, pClone);
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);

		// ============================
		//			몬스터 추가
		// ============================
		
		break;
	}
	case 4:
	{
		// ============================
		//		  플레이어 추가
		// ============================
		CObj* pClone = m_vecClone.back();
		m_vecClone.pop_back();
		pClone->SetName(L"Player");
		pClone->SetPos(200.f, -2128.f);
		//AddObject(LAYER_TYPE::PLAYER, pClone);
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);


		// ============================
		//			몬스터 추가
		// ============================
		break;
	}
	default:
		break;
	}
}

void CLevel_Stage01::Clear(int _Level)
{
	switch (_Level)
	{
	case 1:
	{
		// 카메라 이동
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -498.f));

		// 플레이어 날아가는 애니메이션
		dynamic_cast<CPlayer*>(FindObjectByName(L"Player"))->RoundClear();

		// 2라운드 시작
		Start(2);
		
		break;
	}
	case 2:
	{
		// 카메라 이동
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -1494.f));

		// 플레이어 날아가는 애니메이션
		dynamic_cast<CPlayer*>(FindObjectByName(L"Player"))->RoundClear();

		// 3라운드 시작
		Start(3);
		
		break;
	}
	case 3:
	{
		// 카메라 이동
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -2490.f));

		// 플레이어 날아가는 애니메이션
		dynamic_cast<CPlayer*>(FindObjectByName(L"Player"))->RoundClear();

		// 보스 라운드 시작
		Start(4);
		
		break;
	}
	case 4:
	{
		
		break;
	}
	case 0:
	{
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, 498.f));
		break;
	}
	default:
		break;
	}
}

// =============================
//			벽, 바닥 
// =============================

void CLevel_Stage01::LoadPlat(const wstring& _RelativePath)
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
		m_Platform->SetName(L"Platform");
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}

	fclose(pFile);
}

void CLevel_Stage01::LoadWall(const wstring& _RelativePath)
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
		m_Wall->SetName(L"Wall");
		m_vecEditWall.push_back(m_Wall);
		AddObject(LAYER_TYPE::WALL, m_Wall);
	}

	fclose(pFile);
}


