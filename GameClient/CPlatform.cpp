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
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y;

		if (pPrevFootPos < pNowFootPos && pNowFootPos < pPlatPos)
		{
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetName() == L"Monster")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 pPrevYPos = _OtherObj->GetPrevPos();
		Vec2 pNowYPos = _OtherObj->GetPos();
		Vec2 pFootPos = _OtherObj->GetPos() + _OtherObj->GetScale().y / 2;
		Vec2 pPlatPos = GetPos();

		if (pPrevYPos.y < pNowYPos.y && pFootPos.y < pPlatPos.y)
		{
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetName() == L"SnowObj")
	{
		/*CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 pPrevPos = _OtherObj->GetPrevPos();
		Vec2 pNowPos = _OtherObj->GetPos();
		Vec2 pPlatPos = GetPos();

		if (pPrevPos.y < pNowPos.y && pNowPos.y < pPlatPos.y)
		{
			pRB->SetGround(true);
		}
		else if (pNowPos.y > pPlatPos.y)
		{
			_OtherObj->SetPos(Vec2(pNowPos.x, pPlatPos.y - GetScale().y * 0.5f - _OtherObj->GetScale().y * 0.5f));
			pRB->SetGround(true);
		}*/
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y;

		if (pPrevFootPos < pNowFootPos && pNowFootPos < pPlatPos)
		{
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
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y;

		if (pNowFootPos < pPlatPos)
		{
			pRB->SetGround(false);
		}
	}
	else if (_OtherObj->GetName() == L"Monster")
	{
		Vec2 pPrevYPos = _OtherObj->GetPrevPos();
		Vec2 pNowYPos = _OtherObj->GetPos();

		if (pPrevYPos.y >= pNowYPos.y)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(false);
		}
	}
	else if (_OtherObj->GetName() == L"SnowObj")
	{
		Vec2 pPrevYPos = _OtherObj->GetPrevPos();
		Vec2 pNowYPos = _OtherObj->GetPos();

		if (pPrevYPos.y >= pNowYPos.y)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(false);
		}

	}
}
