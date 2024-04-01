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
	// �ߺ��� �̸� ����
	return m_pCurrentLevel->FindObjectByName(_strName);
}

void CLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;
	// TaskMgr�� �����Լ�(func�� ����Ǿ� �ִ�) ChangeLevel�� �Ѱ��ش�.
	::ChangeLevel(LEVEL_TYPE::STAGE_01);
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// ���� �ȿ� �ִ� ��ü���� �� �����Ӹ��� �� ���� ����
	m_pCurrentLevel->tick();		// ������Ʈ�� �� ���� ����
	m_pCurrentLevel->finaltick();	// ������Ʈ�� �� ���� ����
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
		LOG(LOG_TYPE::DBG_ERROR, L"���� ������ �����Ϸ��� ������ �����մϴ�.");
		return;
	}

	// ���� �������� Exit �Ѵ�.
	if (m_pCurrentLevel)
		m_pCurrentLevel->Exit();

	// ���ο� ������ �������� �ּҰ��� ��ü�Ѵ�.
	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];
	assert(m_pCurrentLevel);

	// ����� ���ο� ������ Enter�Ѵ�.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}