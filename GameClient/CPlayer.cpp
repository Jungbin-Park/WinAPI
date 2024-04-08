#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CGuidedMissile.h"
#include "CSnow.h"

#include "CDbgRender.h"

void BeGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded!!");
}

void BeAir()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Aired!!");
}

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
	, m_JumpCount(1)
	, m_CurJumpCount(0)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::Right)
{
	// Player의 컴포넌트 설정
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(80.f, 128.f));
	m_BodyCol->SetActive(true);


	//// Animation 추가
	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"PlayerLeftTex", L"texture\\Player\\Nick_Left1.bmp");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"PlayerRightTex", L"texture\\Player\\Nick_Right1.bmp");

	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(1120.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"AIR_LEFT", pAtlasL, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_RIGHT", pAtlasR, Vec2(480.f, 0.f), Vec2(160.f, 160.f), 1, 10);


	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"AIR_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"AIR_RIGHT")->Save(L"animation\\player\\");


	// 오프셋 조정
	//m_Animator->FindAnimation(L"IDLE_RIGHT")->GetFrame(1).Offset = Vec2(1.f, 0.f); 

	// Animation 로드
	/*m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");*/
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\ATTACK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\ATTACK_RIGHT.anim");
	//m_Animator->LoadAnimation(L"animation\\player\\AIR_LEFT.anim");
	//m_Animator->LoadAnimation(L"animation\\player\\AIR_RIGHT.anim");
	
	m_Animator->Play(L"IDLE_RIGHT", true);

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetJumpSpeed(600.f);
		
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)	// 에셋은 공유해서 쓰는 개념이기 때문에 그대로 복사해도 됨. 굳이 같은 이미지를 새로 또 로딩할 필요가 없음
	, m_JumpCount(_Other.m_JumpCount)
	, m_CurJumpCount(_Other.m_CurJumpCount)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::Right)
{
	// 부모의 복사생성자를 통해 컴포넌트들의 복사가 이루어졌다면
	// 복사된 컴포넌트들을 찾아서 가리키기만 하면 됨.
	m_BodyCol = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
	// Callback 설정
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CPlayer::Air);
	m_RigidBody->SetWallDelegate(this, (DELEGATE)&CPlayer::SetWall);
	m_RigidBody->SetWallOffDelegate(this, (DELEGATE)&CPlayer::SetWallOff);
}

void CPlayer::tick()
{
	// 이전 좌표 기록을 위해서 CObj의 tick()을 먼저 구현해주어야 함
	CObj::tick();

	// ================================
	//				Move
	// ================================

	Vec2 vPos = GetPos();

	if (m_Ground)
	{
		if (KEY_TAP(KEY::LEFT) && m_RigidBody->IsGround())
		{
			m_State = eState::MOVE;
			m_Direction = eDirection::Left;
			m_Animator->Play(L"WALK_LEFT", true);
		}
		else if (KEY_PRESSED(KEY::LEFT) && !m_StopLeft)
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Left;
			vPos.x -= m_Speed * DT;
		}
		else if (KEY_RELEASED(KEY::LEFT) && m_RigidBody->IsGround())
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::Left;
			m_Animator->Play(L"IDLE_LEFT", true);
		}


		if (KEY_TAP(KEY::RIGHT) && m_RigidBody->IsGround())
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Right;
			m_Animator->Play(L"WALK_RIGHT", true);
		}
		else if (KEY_PRESSED(KEY::RIGHT) && !m_StopRight)
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Right;
			vPos.x += m_Speed * DT;
		}
		else if (KEY_RELEASED(KEY::RIGHT) && m_RigidBody->IsGround())
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::Right;
			m_Animator->Play(L"IDLE_RIGHT", true);
		}
	}
	else
	{
		if (KEY_TAP(KEY::LEFT))
		{
			m_State = eState::MOVE;
			m_Direction = eDirection::Left;
			m_Animator->Play(L"AIR_LEFT", true);
		}
		else if (KEY_PRESSED(KEY::LEFT) && !m_StopLeft)
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Left;
			vPos.x -= m_Speed * DT;
		}
		else if (KEY_RELEASED(KEY::LEFT))
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::Left;
			m_Animator->Play(L"AIR_LEFT", true);
		}


		if (KEY_TAP(KEY::RIGHT))
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Right;
			m_Animator->Play(L"AIR_RIGHT", true);
		}
		else if (KEY_PRESSED(KEY::RIGHT) && !m_StopRight)
		{
			m_State = CPlayer::eState::MOVE;
			m_Direction = eDirection::Right;
			vPos.x += m_Speed * DT;
		}
		else if (KEY_RELEASED(KEY::RIGHT))
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::Right;
			m_Animator->Play(L"AIR_RIGHT", true);
		}
	}

	

	// ==============================
	//			   Jump
	// ==============================

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_JumpCount > m_CurJumpCount)
		{
			Jump();

			m_CurJumpCount += 1;

			switch (m_Direction)
			{
			case eDirection::Left:
				m_Animator->Play(L"JUMP_LEFT", false);
				break;
			case eDirection::Right:
				m_Animator->Play(L"JUMP_RIGHT", false);
				break;
			default:
				break;
			}
		}
	}

	SetPos(vPos);

	// ==============================
	//			  Missle
	// ==============================

	if (KEY_TAP(KEY::CTRL) && m_RigidBody->IsGround() && m_State != eState::ATTACK)
	{
		m_State = CPlayer::eState::ATTACK;

		LOG(LOG_TYPE::DBG_WARNING, L"미사일 발사");

		switch (m_Direction)
		{
		case eDirection::Left:
		{
			m_Animator->Play(L"ATTACK_LEFT", false);

			CSnow* pSnow = new CSnow;
			pSnow->SetName(L"Snow");

			Vec2 vSnowPos = GetPos();
			vSnowPos.x -= GetScale().x / 2.f;
			//vSnowPos.y -= GetScale().y / 2.f;

			pSnow->SetPos(vSnowPos);
			pSnow->SetScale(Vec2(30.f, 40.f));
			
			pSnow->GetRigidBody()->SetMissileSpeed(600.f);

			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pSnow);
			//pSnow->GetRigidBody()->AddForce(Vec2(-1000.f, 0.f));
			pSnow->SetDirection(eDirection::Left);
			pSnow->GetRigidBody()->Shoot(Vec2(-1.f, -0.5f));
			break;
		}
		case eDirection::Right:
		{
			m_Animator->Play(L"ATTACK_RIGHT", false);

			CSnow* pSnow = new CSnow;
			pSnow->SetName(L"Snow");

			Vec2 vSnowPos = GetPos();
			vSnowPos.x += GetScale().x / 2.f;
			//vSnowPos.y -= GetScale().y / 2.f;

			pSnow->SetPos(vSnowPos);
			pSnow->SetScale(Vec2(30.f, 40.f));
			
			pSnow->GetRigidBody()->SetMissileSpeed(600.f);

			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pSnow);
			//pSnow->GetRigidBody()->AddForce(Vec2(1000.f, 0.f));
			pSnow->SetDirection(eDirection::Right);
			pSnow->GetRigidBody()->Shoot(Vec2(1.f, -0.5f));

			break;
		}
		default:
			break;
		}

	}


	if (m_Animator->GetCurAnim()->IsFinish())
	{
		if (m_Animator->GetCurAnim()->GetName() == L"ATTACK_LEFT"
			|| m_Animator->GetCurAnim()->GetName() == L"ATTACK_RIGHT")
		{
			m_State = eState::IDLE;
			switch (m_Direction)
			{
			case eDirection::None:
				break;
			case eDirection::Left:
				m_Animator->Play(L"IDLE_LEFT", true);
				break;
			case eDirection::Right:
				m_Animator->Play(L"IDLE_RIGHT", true);
				break;
			default:
				break;
			}
		}
	}
}


void CPlayer::Jump()
{
	Vec2 vGV = m_RigidBody->GetGravityVelocity();

	if(0.f < vGV.y)
		m_RigidBody->SetGravityVelocity(Vec2(0.f, 0.f));

	m_RigidBody->Jump();

}

void CPlayer::Ground()
{
	m_CurJumpCount = 0;
	m_Ground = true;
	switch (m_Direction)
	{
	case eDirection::None:
		break;
	case eDirection::Left:
		m_Animator->Play(L"IDLE_LEFT", false);
		break;
	case eDirection::Right:
		m_Animator->Play(L"IDLE_RIGHT", false);
		break;
	default:
		break;
	}
}

void CPlayer::Air()
{
	m_Ground = false;
}

void CPlayer::SetWall()
{
	if (m_Direction == eDirection::Left)
	{
		LOG(LOG_TYPE::DBG_WARNING, L"Stop Left!!");
		m_StopLeft = true;
	}
	else if (m_Direction == eDirection::Right)
	{
		LOG(LOG_TYPE::DBG_WARNING, L"Stop Right!!");
		m_StopRight = true;
	}
}

void CPlayer::SetWallOff()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Wall Off!!");
	m_StopLeft = false;
	m_StopRight = false;
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

