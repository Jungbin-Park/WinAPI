#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

// ó���ؾ� �Ǵ� �ϵ��� ��� ó������ �ʰ� �۾����� ��Ƶ״ٰ�
// �ð� ����ȭ�� ���� �̹� �������� ������ �������ǰ� ���� ���� ����

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	// GC ���� Ŭ����
	ClearGC();

	// Task ó��
	ExecuteTask();
}

void CTaskMgr::ClearGC()
{
	Safe_Del_Vec(m_GC);

	m_GC.clear();
}

void CTaskMgr::ExecuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			CLevel* pSpawnLevel = (CLevel*)m_vecTask[i].Param1;
			LAYER_TYPE Layer = (LAYER_TYPE)m_vecTask[i].Param2;
			CObj* pObj = (CObj*)m_vecTask[i].Param3;

			if (CLevelMgr::GetInst()->GetCurrentLevel() != pSpawnLevel)
			{
				delete pObj;
			}
			pSpawnLevel->AddObject(Layer, pObj);
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pObj = (CObj*)m_vecTask[i].Param1;
			if (pObj->m_bDead)
				continue;
			pObj->m_bDead = true;
			// GC���� ����
			m_GC.push_back(pObj);
		}
		break;
		case TASK_TYPE::CHANGE_LEVEL:
		{

		}
		break;
		}
	}

	m_vecTask.clear();
}
