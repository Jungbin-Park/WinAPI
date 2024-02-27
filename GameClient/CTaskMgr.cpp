#include "pch.h"
#include "CTaskMgr.h"

// 처리해야 되는 일들을 즉시 처리하지 않고 작업들을 모아뒀다가
// 시간 동기화를 위해 이번 프레임이 완전히 마무리되고 나서 일을 수행

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		m_vecTask[i].Type;
	}
}
