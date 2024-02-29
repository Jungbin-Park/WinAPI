#include "pch.h"
#include "CGuidedMissile.h"

#include "CLevel.h"
#include "CLevelMgr.h"

CGuidedMissile::CGuidedMissile()
	: m_Target(nullptr)
	, m_Range(1000.f)
{

}

CGuidedMissile::~CGuidedMissile()
{

}

void CGuidedMissile::tick()
{
	// ���� ����� �ִ��� Ȯ��
	if (!IsValid(m_Target))
	{
		FindTarget();
	}

	// Ž���� �ߴµ��� ���� Ÿ���� ���ٸ�1
	if (m_Target)
	{
		// �̻����� ������ ����� ���ϴ� ������ ���ؼ� ���� ������ ���ش�.
		float fSlide = GetPos().GetDistance(m_Target->GetPos());	// ����
		float fDown = m_Target->GetPos().x - GetPos().x;			// �غ�
		float fHeight = m_Target->GetPos().y - GetPos().y;			// ����

		// ��ũ�ڻ��� �Լ��� �ڻ��� �������� �־� ������ ���Ѵ�.
		float fAngle = acosf(fDown / fSlide);

		// ������ ��ġ�� �̻��Ϻ��� �Ʒ��� �ִٸ�, �ڻ��� ������ ���� ������ �� ū ���� ���;� �ϴµ�
		// ��ũ�ڻ��� �Լ��� ���� ������ -180~180�̱� ������, ���� 360������ ���ϵ��� ���� ���� �ݴ����� ū ������ �˾Ƴ���.
		if (GetPos().y < m_Target->GetPos().y)
		{
			fAngle = PI * 2.f - fAngle;
		}

		SetAngle(fAngle);
	}
	else 
	{
		SetAngle(PI / 2.f);
	}

	CMissile::tick();
}



void CGuidedMissile::FindTarget()
{
	if (LAYER_TYPE::MONSTER_MISSILE == GetLayerType())
	{
		// �÷��̾ Ž��
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		m_Target = pCurLevel->FindObjectByName(L"Player");
	}
	else if (LAYER_TYPE::PLAYER_MISSILE == GetLayerType())
	{
		// ���� ��ü ����� �޾ƿ�
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecMonster = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

		// �̻����� ��ġ
		Vec2 vMissilePos = GetPos();

		float fMinDist = m_Range;
		m_Target = nullptr;

		for (size_t i = 0; i < vecMonster.size(); i++)
		{
			if (vecMonster[i]->IsDead())
				continue;

			// ���Ϳ� �̻����� �Ÿ��� ���Ѵ�
			float fDist = vMissilePos.GetDistance(vecMonster[i]->GetPos());

			if (fDist < fMinDist)
			{
				fMinDist = fDist;
				m_Target = vecMonster[i];
			}
		}
	}
}

void CGuidedMissile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Monster")
		Destroy();
}
