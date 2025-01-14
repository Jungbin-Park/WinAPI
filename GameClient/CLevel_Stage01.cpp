#include "pch.h"
#include "CLevel_Stage01.h"
#include "CCollider_Editor.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"

#include "CForce.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "MRana.h"
#include "CBoss.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CSnowObj.h"
#include "CPlayerSpawn.h"
#include "CPlayerLife.h"

#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CStageBoss.h"

#include "CSound.h"

CLevel_Stage01::CLevel_Stage01()
	: m_Platform(nullptr)
	, m_Wall(nullptr)
	, m_LifeUI(nullptr)
	, m_CurRound(1)
	, m_Score(0)
	, m_PlayerLife(3)
{
	
}

CLevel_Stage01::~CLevel_Stage01()
{
	Safe_Del_Vec(m_vecClone);

	DeleteAllObjects();
}


void CLevel_Stage01::begin()
{
	CLevel::begin();
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 0.2f);
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.2f);

	CCamera::GetInst()->SetCamFixedDelegate(this, (CAMDELEGATE)&CLevel_Stage01::Start);
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::LOGO_END);
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

	if (m_Score >= 4)
		RoundClear(m_CurRound);

	m_LifeUI->SetPos( CCamera::GetInst()->GetLookAt() + Vec2(550.f, -450.f));

	if (m_PlayerLife == 0)
	{
		ChangeLevel(LEVEL_TYPE::LOGO_END);
	}

}

void CLevel_Stage01::Enter()
{
	// ============================
	//		 플랫폼, 벽 생성
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
	//		Player Life
	// ============================
	m_LifeUI = new CPlayerLife;
	m_LifeUI->SetName(L"LifeUI");
	AddObject(LAYER_TYPE::UI, m_LifeUI);
	


	// ============================
	//		  레벨 충돌 설정
	// ============================

	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_MISSILE);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::PLATFORM);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::WALL);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::WALL);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::SNOW);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::BOSS);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::SNOW, LAYER_TYPE::BOSS);

	m_CurRound = 1;
	m_PlayerLife = 3;
	Start();
}

void CLevel_Stage01::Exit()
{
	
	// 레벨에 있는 모든 오브젝트 삭제

	DeleteAllObjects();

	// Dontdestroy 할 것들은 예외처리

	Safe_Del_Vec(m_vecClone);

	CCamera::GetInst()->SetLookAt(Vec2(720.f, 498.f));
}


void CLevel_Stage01::Start()
{
	switch (m_CurRound)
	{
	case 1:
	{
		m_Score = 0;

		// ============================
		//		  플레이어 추가
		// ============================

		CObj* pObject = new CPlayer;
		pObject->SetName(L"Player");
		pObject->SetPos(200.f, 860.f);
		pObject->SetScale(80.f, 128.f);
		AddObject(LAYER_TYPE::PLAYER, pObject);
		//SpawnObject(this, LAYER_TYPE::PLAYER, pObject);
		dynamic_cast<CPlayer*>(pObject)->SetInvisible(true);

		CPlayerSpawn* SpawnEffect = new CPlayerSpawn;
		SpawnEffect->SetName(L"SpawnEffect");
		Vec2 ePos = pObject->GetPos();
		SpawnEffect->SetPos(ePos);
		SpawnEffect->SetOwner(pObject);

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, SpawnEffect);

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
		pObject->SetPos(100.f, 700.f);
		pObject->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pObject);

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(1300.f, 400.f);
		pObject->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pObject);

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(1300.f, 700.f);
		pObject->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pObject);

		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Stage01", L"sound\\Music\\Stage01.wav");
		pSound->SetVolume(100.f);
		pSound->PlayToBGM(true);

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
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);
		dynamic_cast<CPlayer*>(pClone)->SetInvisible(true);

		CPlayerSpawn* SpawnEffect = new CPlayerSpawn;
		SpawnEffect->SetName(L"SpawnEffect");
		Vec2 ePos = pClone->GetPos();
		SpawnEffect->SetPos(ePos);
		SpawnEffect->SetOwner(pClone);

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, SpawnEffect);


		// ============================
		//			몬스터 추가
		// ============================
		
		CObj* pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(600.f, -896.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(700.f, -596.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(200.f, -596.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new CMonster;
		pObject->SetName(L"Monster");
		pObject->SetPos(800.f, -296.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Stage02", L"sound\\Music\\Stage02.wav");
		pSound->SetVolume(100.f);
		pSound->PlayToBGM(true);

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
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);
		dynamic_cast<CPlayer*>(pClone)->SetInvisible(true);

		CPlayerSpawn* SpawnEffect = new CPlayerSpawn;
		SpawnEffect->SetName(L"SpawnEffect");
		Vec2 ePos = pClone->GetPos();
		SpawnEffect->SetPos(ePos);
		SpawnEffect->SetOwner(pClone);

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, SpawnEffect);


		// ============================
		//			몬스터 추가
		// ============================
		CObj* pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(400.f, -1900.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(1000.f, -1900.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(100.f, -1200.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		pObject = new MRana;
		pObject->SetName(L"Rana");
		pObject->SetPos(1300.f, -1200.f);
		pObject->SetScale(100.f, 100.f);
		SpawnObject(this, LAYER_TYPE::MONSTER, pObject);

		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Stage01", L"sound\\Music\\Stage01.wav");
		pSound->SetVolume(100.f);
		pSound->PlayToBGM(true);

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
		SpawnObject(this, LAYER_TYPE::PLAYER, pClone);
		dynamic_cast<CPlayer*>(pClone)->SetInvisible(true);

		CPlayerSpawn* SpawnEffect = new CPlayerSpawn;
		SpawnEffect->SetName(L"SpawnEffect");
		Vec2 ePos = pClone->GetPos();
		SpawnEffect->SetPos(ePos);
		SpawnEffect->SetOwner(pClone);

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, SpawnEffect);


		// ============================
		//			보스 추가
		// ============================
		CObj* pObject = new CBoss;
		pObject->SetName(L"Boss");
		pObject->SetPos(1200.f, -2750.f);
		pObject->SetScale(400.f, 400.f);
		SpawnObject(this, LAYER_TYPE::BOSS, pObject);

		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Boss", L"sound\\Music\\Boss.wav");
		pSound->SetVolume(100.f);
		pSound->PlayToBGM(true);

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
		m_Score = 0;
		m_CurRound = 2;
		
		break;
	}
	case 2:
	{
		// 카메라 이동
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -1494.f));

		// 플레이어 날아가는 애니메이션
		dynamic_cast<CPlayer*>(FindObjectByName(L"Player"))->RoundClear();

		// 3라운드 시작
		m_Score = 0;
		m_CurRound = 3;
		
		break;
	}
	case 3:
	{
		// 카메라 이동
		CCamera::GetInst()->SetCameraDes(Vec2(720.f, -2490.f));

		// 플레이어 날아가는 애니메이션
		dynamic_cast<CPlayer*>(FindObjectByName(L"Player"))->RoundClear();

		// 보스 라운드 시작
		m_Score = 0;
		m_CurRound = 4;
		
		break;
	}
	case 4:
	{
		// Clear 레벨로 전환
		ChangeLevel(LEVEL_TYPE::LOGO_CLEAR);


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

void CLevel_Stage01::RoundClear(int _Level)
{
	Clear(_Level);
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

	m_vecEditPlat.clear();

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

	m_vecEditWall.clear();

	fclose(pFile);
}


