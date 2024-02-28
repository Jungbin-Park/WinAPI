#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CTaskMgr.h"

#include "CComponent.h"



CObj::CObj()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
{

}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecCom);
}

void CObj::begin()
{

}

void CObj::tick()
{
	
}

void CObj::finaltick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->finaltick();
	}
}

void CObj::render()
{
	HDC dc = CEngine::GetInst()->GetSubDC();

	// 렌더링 과정 문제점(화면 클리어)
	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);
}

void CObj::Destroy()
{
	tTask task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param1 = (DWORD_PTR)this;

	CTaskMgr::GetInst()->AddTask(task);
}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	return _Component;
}


