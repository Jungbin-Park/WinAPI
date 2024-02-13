#include "pch.h"
#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CCollider::CCollider()
	: m_Active(true)
	, m_bOverlap(false)
{
}

CCollider::~CCollider()
{
}


void CCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	if (m_Active)
	{
		// 충돌체를 보유하고 있는 오브젝트의 소속 레이어에 자신을 등록시킨다.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);
	}

	if (m_bOverlap)
	{
		DrawDebugRect(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
	}
	else
	{
		DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
	}
	
}

void CCollider::OnOverlap(CCollider* _OtherCollider)
{
	m_bOverlap = true;

	_OtherCollider->GetOwner();
}