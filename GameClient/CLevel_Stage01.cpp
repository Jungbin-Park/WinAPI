#include "pch.h"
#include "CLevel_Stage01.h"

#include "CKeyMgr.h"
#include "CForce.h"

#include "CCollisionMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"

CLevel_Stage01::CLevel_Stage01()
{
}

CLevel_Stage01::~CLevel_Stage01()
{
	
}

void CLevel_Stage01::begin()
{
	CLevel::begin();
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 0.2f);
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.2f);
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		/*Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = CCamera::GetInst()->GetRealPos(vMousePos);

		CForce* pForce = new CForce;
		pForce->SetPos(vPos);
		pForce->SetForce(1000.f, 300.f, 0.3f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);*/
	}
}

void CLevel_Stage01::Enter()
{
	// ������ �÷��̾� �߰�
	CObj* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(640.f, 600.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	/*CObj* pPlayerClone = pObject->Clone();
	pPlayerClone->SetPos(800.f, 400.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);*/

	// ���� �߰�
	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.f, 200.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);


	// �÷��� ����
	pObject = new CPlatform;
	pObject->SetName(L"Platform1");
	pObject->SetPos(Vec2(800.f, 550.f));
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	pObject = new CPlatform;
	pObject->SetName(L"Platform2");
	pObject->SetPos(Vec2(600.f, 700.f));
	AddObject(LAYER_TYPE::PLATFORM, pObject);


	// ���� �浹 �����ϱ�
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
}

void CLevel_Stage01::Exit()
{
	// ������ �ִ� ��� ������Ʈ �����Ѵ�

	// Dontdestroy �� �͵��� ����ó��
}
