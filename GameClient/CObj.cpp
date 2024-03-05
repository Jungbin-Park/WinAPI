#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CTaskMgr.h"

#include "CComponent.h"
#include "CAnimator.h"



CObj::CObj()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
	, m_Animator(nullptr)
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
	if (nullptr == m_Animator)
		return;

	m_Animator->render();
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

	// 오브젝트에 추가된 컴포넌트가 Animator면 별도의 포인터로 따로 가리킨다.
	m_Animator = dynamic_cast<CAnimator*>(_Component);

	return _Component;
}


