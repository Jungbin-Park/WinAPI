#include "pch.h"
#include "CLevelMgr.h"

#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CPlayer.h"
#include "CMonster.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}

void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// 현재 레벨 지정
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// 레벨에 플레이어 추가
	CObj* pObject = new CPlayer;
	pObject->SetPos(640.f, 384.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);

	// 몬스터 추가
	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.f, 200.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// 레벨 안에 있는 물체들이 매 프레임마다 할 일을 정의
	m_pCurrentLevel->tick();

	m_pCurrentLevel->finaltick();
	
	m_pCurrentLevel->render();
}

void CLevelMgr::render()
{
	m_pCurrentLevel->render();
}
