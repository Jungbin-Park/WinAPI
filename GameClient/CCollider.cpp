#include "pch.h"
#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CCollider::CCollider()
	: m_Active(false)
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
		// �浹ü�� �����ϰ� �ִ� ������Ʈ�� �Ҽ� ���̾ �ڽ��� ��Ͻ�Ų��.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);
	}

	DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
}