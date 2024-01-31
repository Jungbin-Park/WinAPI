#include "pch.h"
#include "CCollider.h"


CCollider::CCollider()
{

}

CCollider::~CCollider()
{

}

void CCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;



	DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
}