#include "pch.h"
#include "CPlatform.h"

#include "CMiniBoss.h"
#include "CFSM.h"

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
		float pPlatPos = GetPos().y + GetScale().y;

		if (pPrevFootPos < pNowFootPos && pNowFootPos < pPlatPos)
		{
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetLayerType() == LAYER_TYPE::MONSTER)
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y + GetScale().y;

		if (_OtherObj->GetName() == L"MiniBoss")
		{
			dynamic_cast<CMiniBoss*>(_OtherObj)->GetFSM()->ChangeState(L"Wake");
		}

		if (pPrevFootPos < pNowFootPos && pNowFootPos < pPlatPos)
		{
			pRB->SetGround(true);
		}

	}
	else if (_OtherObj->GetLayerType() == LAYER_TYPE::BOSS)
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y + GetScale().y;

		if (pPrevFootPos < pNowFootPos && pNowFootPos < pPlatPos)
		{
			pRB->SetGround(true);
		}
	}
	else if (_OtherObj->GetName() == L"SnowObj")
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
		float pPlatPos = GetPos().y + GetScale().y;

		if (pNowFootPos < pPlatPos)
		{
			pRB->SetGround(false);
		}
	}
	else if (_OtherObj->GetLayerType() == LAYER_TYPE::MONSTER)
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y + GetScale().y;

		if (pNowFootPos < pPlatPos)
		{
			pRB->SetGround(false);
		}
	}
	else if (_OtherObj->GetLayerType() == LAYER_TYPE::BOSS)
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y + GetScale().y;

		if (pNowFootPos < pPlatPos)
		{
			pRB->SetGround(false);
		}
	}
	else if (_OtherObj->GetName() == L"SnowObj")
	{
		/*Vec2 pPrevYPos = _OtherObj->GetPrevPos();
		Vec2 pNowYPos = _OtherObj->GetPos();

		if (pPrevYPos.y >= pNowYPos.y)
		{
			CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
			pRB->SetGround(false);
		}*/
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		float pPrevFootPos = _OtherObj->GetPrevPos().y + (_OtherObj->GetScale().y * 0.5f);
		float pNowFootPos = _OtherObj->GetPos().y + (_OtherObj->GetScale().y * 0.5f);
		Vec2 platPos = GetPos();
		float pPlatPos = GetPos().y + GetScale().y;

		if (pNowFootPos < pPlatPos)
		{
			pRB->SetGround(false);
		}
	}
}
