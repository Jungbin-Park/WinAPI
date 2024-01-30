#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CObj.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{

}

void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// 현재 레벨 지정
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// 레벨에 물체 추가하기
	CObj* pObject = new CObj;
	pObject->SetPos(640.f, 384.f);
	pObject->SetScale(100.f, 100.f);

	m_pCurrentLevel->AddObject(pObject);
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
