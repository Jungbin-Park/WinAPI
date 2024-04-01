#include "pch.h"
#include "CFSM.h"

#include "CState.h"

CFSM::CFSM()
{
}

CFSM::~CFSM()
{
}

void CFSM::finaltick()
{
	if (nullptr == m_CurState)
		return; 

	m_CurState->FinalTick();
}

void CFSM::AddState(const wstring& _strStateName, CState* _State)
{
	assert(!FindState(_strStateName));

	// 상태의 소유자(FSM) 세팅하기
	_State->m_Owner = this;

	// 상태 추가
	m_mapState.insert(make_pair(_strStateName, _State));
}

CState* CFSM::FindState(const wstring& _strStateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_strStateName);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CFSM::ChangeState(const wstring& _strNextStateName)
{
	if (!m_CurState && (_strNextStateName == m_CurState->GetName()))
		return;

	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);

	assert(m_CurState);

	m_CurState->Enter();
}




