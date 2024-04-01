 #include "pch.h"
#include "CLevelMgr.h"
#include "CLevel_Stage01.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}

CObj* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	// 중복된 이름 조심
	return m_pCurrentLevel->FindObjectByName(_strName);
}

void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;
	// TaskMgr로 전역함수(func에 선언되어 있는) ChangeLevel를 넘겨준다.
	::ChangeLevel(LEVEL_TYPE::STAGE_01);
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// 레벨 안에 있는 물체들이 매 프레임마다 할 일을 정의
	m_pCurrentLevel->tick();		// 오브젝트가 할 일을 수행
	m_pCurrentLevel->finaltick();	// 컴포넌트가 할 일을 수행
}

void CLevelMgr::render()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevelType)
{
	if (m_arrLevel[(UINT)_NextLevelType] == m_pCurrentLevel)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"현재 레벨과 변경하려는 레벨이 동일합니다.");
		return;
	}

	// 기존 레벨에서 Exit 한다.
	if (m_pCurrentLevel)
		m_pCurrentLevel->Exit();

	// 새로운 레벨로 포인터의 주소값을 교체한다.
	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];
	assert(m_pCurrentLevel);

	// 변경된 새로운 레벨로 Enter한다.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}