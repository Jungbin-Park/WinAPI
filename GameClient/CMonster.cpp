#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CRigidBody.h"

#include "CMissile.h"


CMonster::CMonster()
	: m_HP(5)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(120.f, 120.f));

	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMass(2.f);
	m_RigidBody->SetInitialWalkSpeed(0.f);
	m_RigidBody->SetMaxWalkSpeed(400.f);
	m_RigidBody->SetFriction(2000.f);

	m_Img = CAssetMgr::GetInst()->LoadTexture(L"Monster", L"texture\\Fighter.bmp");
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
}

void CMonster::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	/*TransparentBlt(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
					   , (int)(vPos.y - m_Img->GetHeight() / 2.f)
					   , m_Img->GetWidth(), m_Img->GetHeight()
					   , m_Img->GetDC(), 0, 0
					   , m_Img->GetWidth(), m_Img->GetHeight(), RGB(255, 0, 255));*/


	static float alpha = 0;
	static float dir = 1;

	alpha += DT * 400.f * dir;

	if (255.f <= alpha)
	{
		dir *= -1.f;
	}
	else if (alpha <= 0.f)
	{
		dir *= -1.f;
	}

	// AlphaBlending  
	// ������ ���� ����� �ƿ� ���ϴ� Transparent�ʹ� �ٸ��� 
	// AlphaBlend�� (������ RGB x Alpha) + (������ ���� x (1-Alpha)) ���� ������ش�.
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha;	// ����(0~255)
	bf.AlphaFormat = AC_SRC_ALPHA;	// �ҽ��� ���Ű��� �̿��ϰڴ�.
	

	AlphaBlend(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
				 , (int)(vPos.y - m_Img->GetHeight() / 2.f)
				 , m_Img->GetWidth(), m_Img->GetHeight()
				 , m_Img->GetDC(), 0, 0, m_Img->GetWidth(), m_Img->GetHeight(), bf);
}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherClldier)
{
	CMissile* pMissile = dynamic_cast<CMissile*>(_OtherObj);

	if (_OtherObj->GetName() == L"Missile")
	{
		--m_HP;

		if (0 >= m_HP)
		{
			Destroy();
		}
	}
}
