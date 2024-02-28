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
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// Ž���� �ߴµ��� ���� Ÿ���� ���ٸ�
	if (nullptr == m_Target)
	{
		SetAngle(PI / 2.f);
	}
	else 
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

		for (size_t i = 0; i < vecMonster.size(); i++)
		{
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
