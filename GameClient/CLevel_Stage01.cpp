#include "pch.h"
#include "CLevel_Stage01.h"

#include "CKeyMgr.h"
#include "CForce.h"

CLevel_Stage01::CLevel_Stage01()
{
}

CLevel_Stage01::~CLevel_Stage01()
{
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = CCamera::GetInst()->GetRealPos(vMousePos);

		CForce* pForce = new CForce;
		pForce->SetPos(vPos);
		pForce->SetForce(1000.f, 300.f, 0.3f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}
}
