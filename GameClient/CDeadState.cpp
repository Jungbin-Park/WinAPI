#include "pch.h"
#include "CDeadState.h"


CDeadState::CDeadState()
{
}

CDeadState::~CDeadState()
{
}


void CDeadState::Enter()
{
	GetFSM()->GetOwner()->Dead(true);
}

void CDeadState::FinalTick()
{
}

void CDeadState::Exit()
{
}



