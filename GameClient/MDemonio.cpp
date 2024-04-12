#include "pch.h"
#include "MDemonio.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

#include "CSnow.h"
#include "CSnowObj.h"

#include "CFSM.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CMoveState.h"
#include "CSnowState.h"
#include "CJumpState.h"

MDemonio::MDemonio()
	: m_Direction(eDirection::None)
{
}

MDemonio::MDemonio(Vec2(_Pos), Vec2(_Scale))
{
}

MDemonio::~MDemonio()
{
}

void MDemonio::begin()
{
}

void MDemonio::tick()
{
	CMonster::tick();
}
