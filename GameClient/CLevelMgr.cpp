 #include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Editor.h"
#include "CCollider_Editor.h"
#include "CLevel_Stage01.h"
#include "CStartLevel.h"
#include "CEndLevel.h"


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
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::COLLIDER_EDITOR] = new CCollider_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::LOGO_START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;
	m_arrLevel[(UINT)LEVEL_TYPE::LOGO_END] = new CEndLevel;
	
	// �ʱ� ���� ����
	// TaskMgr�� �����Լ�(func�� ����Ǿ� �ִ�) ChangeLevel�� �Ѱ��ش�.
	//::ChangeLevel(LEVEL_TYPE::COLLIDER_EDITOR);
	::ChangeLevel(LEVEL_TYPE::LOGO_START);
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

CObj* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	// �ߺ��� �̸� ����
	return m_pCurrentLevel->FindObjectByName(_strName);
}