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
	// 추적 대상이 있는지 확인
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// 탐색을 했는데도 아직 타겟이 없다면
	if (nullptr == m_Target)
	{
		SetAngle(PI / 2.f);
	}
	else 
	{
		// 미사일이 추적할 대상을 향하는 각도를 구해서 각도 설정을 해준다.
		float fSlide = GetPos().GetDistance(m_Target->GetPos());	// 빗변
		float fDown = m_Target->GetPos().x - GetPos().x;			// 밑변
		float fHeight = m_Target->GetPos().y - GetPos().y;			// 높이

		// 아크코사인 함수에 코사인 비율값을 넣어 각도를 구한다.
		float fAngle = acosf(fDown / fSlide);

		// 몬스터의 위치가 미사일보다 아래에 있다면, 코사인 비율에 대한 각도가 더 큰 값이 나와야 하는데
		// 아크코사인 함수의 리턴 범위가 -180~180이기 때문에, 전가 360도에서 리턴도니 값을 빼서 반대편의 큰 각도를 알아낸다.
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
		// 플레이어를 탐색
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		m_Target = pCurLevel->FindObjectByName(L"Player");
	}
	else if (LAYER_TYPE::PLAYER_MISSILE == GetLayerType())
	{
		// 몬스터 전체 목록을 받아옴
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecMonster = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

		// 미사일의 위치
		Vec2 vMissilePos = GetPos();

		float fMinDist = m_Range;

		for (size_t i = 0; i < vecMonster.size(); i++)
		{
			// 몬스터와 미사일의 거리를 구한다
			float fDist = vMissilePos.GetDistance(vecMonster[i]->GetPos());

			if (fDist < fMinDist)
			{
				fMinDist = fDist;
				m_Target = vecMonster[i];
			}
		}
	}
}
