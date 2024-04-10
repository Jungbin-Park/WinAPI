#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CRigidBody.h"

CPlatform::CPlatform()
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CPlatform::CPlatform(Vec2(_Pos), Vec2(_Scale))
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::~CPlatform()
{

}

void CPlatform::tick()
{
	CObj::tick();
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		float pPrevYPos = _OtherObj->GetPrevPos().y + _OtherObj->GetScale().y / 2;
		float yPos = GetPos().y - GetScale().y / 2;

		if (pPrevYPos < yPos)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetName() == L"Monster")
	{
		float pPrevYPos = _OtherObj->GetPrevPos().y + _OtherObj->GetScale().y / 2;
		float yPos = GetPos().y - GetScale().y / 2;

		if (pPrevYPos < yPos)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetName() == L"SnowObj")
	{
		float pPrevYPos = _OtherObj->GetPrevPos().y + _OtherObj->GetScale().y / 2;
		float yPos = GetPos().y - GetScale().y / 2;

		if (pPrevYPos < yPos)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(true);
		}
	}
	
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
	}

	if (_OtherObj->GetName() == L"Monster")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
	}

	if (_OtherObj->GetName() == L"SnowObj")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
	}
}
