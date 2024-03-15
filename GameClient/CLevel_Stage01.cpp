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

		CForce* pForce = new CForce;
		pForce->SetPos(vMousePos);
		pForce->SetForce(1000.f, 500.f, 2.f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}
}
