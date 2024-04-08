#include "pch.h"
#include "CWall.h"

#include "CCollider.h"
#include "CRigidBody.h"

CWall::CWall()
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CWall::CWall(Vec2(_Pos), Vec2(_Scale))
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CWall::~CWall()
{
}

void CWall::tick()
{
	CObj::tick();
}

void CWall::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetWall(true);

	}
	else if (_OtherObj->GetName() == L"Monster")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetWall(true);
	}
	else if (_OtherObj->GetName() == L"Snow")
	{
		_OtherObj->Destroy();
	}
}

void CWall::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CWall::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetWall(false);

	}
	else if (_OtherObj->GetName() == L"Monster")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetWall(false);
	}
}


