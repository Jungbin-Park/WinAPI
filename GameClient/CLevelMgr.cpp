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
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	CObj* pObject = new CObj;
	pObject->SetPos(640.f, 384.f);
	pObject->SetScale(100.f, 100.f);

	m_pCurrentLevel->AddObject(pObject);
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// ���� �ȿ� �ִ� ��ü���� �� �����Ӹ��� �� ���� ����
	m_pCurrentLevel->tick();

	m_pCurrentLevel->finaltick();
	
	m_pCurrentLevel->render();
}

void CLevelMgr::render()
{
	m_pCurrentLevel->render();
}
