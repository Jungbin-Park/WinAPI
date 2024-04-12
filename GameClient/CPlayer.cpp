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
#include "CSnowObj.h"
#include "CMonster.h"

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
	, m_JumpCount(1)
	, m_CurJumpCount(0)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::Right)
	, m_bDead(false)
	, m_bClear(false)
	, m_StopLeft(false)
	, m_StopRight(false)
	, m_Ground(false)
	, m_PushSnow(false)
	, m_OverlappedSnowObj(nullptr)
{
	// Player의 컴포넌트 설정
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_Collider->SetName(L"Player Collider");
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(80.f, 128.f));
	m_Collider->SetActive(true);


	// ===============================
	//		  Animation 추가
	// ===============================

	CTexture* pAtlasL = CAssetMgr::GetInst()->LoadTexture(L"PlayerLeftTex", L"texture\\Player\\Nick_Left1.bmp");
	CTexture* pAtlasR = CAssetMgr::GetInst()->LoadTexture(L"PlayerRightTex", L"texture\\Player\\Nick_Right1.bmp");
	/*
	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlasL, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlasR, Vec2(1120.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlasL, Vec2(160.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlasR, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"AIR_LEFT", pAtlasL, Vec2(640.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"AIR_RIGHT", pAtlasR, Vec2(480.f, 0.f), Vec2(160.f, 160.f), 1, 10);
	m_Animator->CreateAnimation(L"DEAD", pAtlasL, Vec2(0.f, 480.f), Vec2(156.f, 150.f), 7, 5);
	m_Animator->CreateAnimation(L"PUSH_LEFT", pAtlasL, Vec2(640.f, 640.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"PUSH_RIGHT", pAtlasR, Vec2(160.f, 640.f), Vec2(160.f, 160.f), 3, 10);
	m_Animator->CreateAnimation(L"CLEAR", pAtlasL, Vec2(0.f, 1120.f), Vec2(160.f, 160.f), 2, 1);

	m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"AIR_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"AIR_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"DEAD")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"PUSH_LEFT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"PUSH_RIGHT")->Save(L"animation\\player\\");
	m_Animator->FindAnimation(L"CLEAR")->Save(L"animation\\player\\");
	
	*/
	

	// 오프셋 조정
	//m_Animator->FindAnimation(L"DEAD")->GetFrame(1).Offset = Vec2(1.f, 0.f); 

	// Animation 로드
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\ATTACK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\ATTACK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\AIR_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\AIR_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\DEAD.anim");
	m_Animator->LoadAnimation(L"animation\\player\\PUSH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\PUSH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\CLEAR.anim");
	
	m_Animator->Play(L"IDLE_RIGHT", true);

	// 강체(Rigidbody) 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetGravityAccel(1000.f);
	m_RigidBody->SetJumpSpeed(600.f);
		
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)	// 에셋은 공유해서 쓰는 개념이기 때문에 그대로 복사해도 됨. 굳이 같은 이미지를 새로 또 로딩할 필요가 없음
	, m_JumpCount(_Other.m_JumpCount)
	, m_CurJumpCount(0)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::Right)
	, m_bDead(false)
	, m_bClear(false)
	, m_StopLeft(false)
	, m_StopRight(false)
	, m_Ground(false)
	, m_PushSnow(false)
	, m_OverlappedSnowObj(nullptr)
{
	// 부모의 복사생성자를 통해 컴포넌트들의 복사가 이루어졌다면
	// 복사된 컴포넌트들을 찾아서 가리키기만 하면 됨.
	m_Collider = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();

	// Callback 설정
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::Ground);
	m_RigidBody->SetAirDelegate(this, (DELEGATE)&CPlayer::Air);
	m_RigidBody->SetWallDelegate(this, (DELEGATE)&CPlayer::SetWall);
	m_RigidBody->SetWallOffDelegate(this, (DELEGATE)&CPlayer::SetWallOff);
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

	if (m_bClear)
		vPos.y -= 1000.f * DT;

	if (vPos.y < -4000.f)
		Destroy();

	if (m_bDead)
	{
		m_RigidBody->SetActive(false);
	}
	else
	{
		m_RigidBody->SetActive(true);

		// 바닥 밟을 때
		if (m_Ground)
		{
			if (!m_PushSnow)
			{
				// 일반 이동 상태
				if (KEY_TAP(KEY::LEFT))
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
				else if (KEY_RELEASED(KEY::LEFT))
				{
					m_State = eState::IDLE;
					m_Direction = eDirection::Left;
					m_Animator->Play(L"IDLE_LEFT", true);
				}

				if (KEY_TAP(KEY::RIGHT))
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
				else if (KEY_RELEASED(KEY::RIGHT))
				{
					m_State = eState::IDLE;
					m_Direction = eDirection::Right;
					m_Animator->Play(L"IDLE_RIGHT", true);
				}
			}
			else
			{
				Vec2 vPos = GetPos();
				Vec2 sPos = m_OverlappedSnowObj->GetPos();
				float vDirX = sPos.x - vPos.x;

				if (KEY_TAP(KEY::LEFT))
				{
					m_State = eState::MOVE;
					m_Direction = eDirection::Left;
					if (vDirX < 0)
						m_Animator->Play(L"PUSH_LEFT", true);
					else
						m_Animator->Play(L"WALK_LEFT", true);
				}
				else if (KEY_PRESSED(KEY::LEFT))
				{
					m_State = CPlayer::eState::MOVE;
					m_Direction = eDirection::Left;
					vPos.x -= m_Speed * DT;
					if (vDirX < 0)
					{
						sPos.x -= m_Speed * DT;
						m_OverlappedSnowObj->SetPos(sPos);
					}

				}
				else if (KEY_RELEASED(KEY::LEFT))
				{
					m_State = eState::IDLE;
					m_Direction = eDirection::Left;
					m_Animator->Play(L"IDLE_LEFT", true);
				}

				if (KEY_TAP(KEY::RIGHT))
				{
					m_State = CPlayer::eState::MOVE;
					m_Direction = eDirection::Right;
					if (vDirX > 0)
						m_Animator->Play(L"PUSH_RIGHT", true);
					else
						m_Animator->Play(L"WALK_RIGHT", true);

				}
				else if (KEY_PRESSED(KEY::RIGHT))
				{
					m_State = CPlayer::eState::MOVE;
					m_Direction = eDirection::Right;
					vPos.x += m_Speed * DT;
					if (vDirX > 0)
					{
						sPos.x += m_Speed * DT;
						m_OverlappedSnowObj->SetPos(sPos);
						m_OverlappedSnowObj->GetAnimator()->Play(L"SNOWROLL", false);
					}
				}
				else if (KEY_RELEASED(KEY::RIGHT))
				{
					m_State = eState::IDLE;
					m_Direction = eDirection::Right;
					m_Animator->Play(L"IDLE_RIGHT", true);
				}
			}
		}
		// 공중 상태일 때
		else if (!m_Ground)
		{
			// 공중 상태
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
	}


	// ==============================
	//			   Jump
	// ==============================

	if (KEY_TAP(KEY::SPACE) && !m_bDead)
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

	

	// ==============================
	//			  Missle
	// ==============================

	if (KEY_TAP(KEY::CTRL) && m_State != eState::ATTACK && !m_bDead)
	{
		if (!m_PushSnow)
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

				pSnow->SetPos(vSnowPos);
				pSnow->SetScale(Vec2(30.f, 40.f));

				SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pSnow);
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

				pSnow->SetPos(vSnowPos);
				pSnow->SetScale(Vec2(30.f, 40.f));

				SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pSnow);
				pSnow->SetDirection(eDirection::Right);
				pSnow->GetRigidBody()->Shoot(Vec2(1.f, -0.5f));
				break;
			}
			default:
				break;
			}
		}
		else
		{
			// 눈덩이 날리기
			Vec2 snowPos = m_OverlappedSnowObj->GetPos();
			Vec2 vDir = snowPos - vPos;

			switch (m_Direction)
			{
			case eDirection::Left:
			{
				m_OverlappedSnowObj->Shoot(Vec2(-1.f, 0.f));
				break;
			}
			case eDirection::Right:
			{
				m_OverlappedSnowObj->Shoot(Vec2(1.f, 0.f));
				break;
			}
			default:
				break;
			}
		}
		

	}


	// =================================
	//		애니메이션 끝났을 때 처리
	// =================================

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		// 공격 애니메이션
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

		// 사망 애니메이션
		if (m_Animator->GetCurAnim()->GetName() == L"DEAD")
		{
			//Destroy();
			vPos = Vec2(200.f, 870.f);
			m_bDead = false;
			m_Animator->Play(L"IDLE_RIGHT", true);
		}
	}

	SetPos(vPos);
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

void CPlayer::RoundClear()
{
	Vec2 vPos = GetPos();
	m_Animator->Play(L"CLEAR", true);
	m_bDead = true;
	m_bClear = true;
	m_Collider->SetActive(false);
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Monster")
	{
		CMonster* Mon = dynamic_cast<CMonster*>(_OtherObj);
		if (Mon->IsSnow())
		{

		}
		else
		{
			m_bDead = true;

			m_Animator->Play(L"DEAD", false);
		}
		
	}

	if (_OtherObj->GetName() == L"SnowObj")
	{
		m_OverlappedSnowObj = dynamic_cast<CSnowObj*>(_OtherObj);
		if (m_OverlappedSnowObj->IsActive())
		{
			if (m_OverlappedSnowObj->IsRoll())
			{
				// 플레이어가 굴러가는 눈덩이에 탄다

			}
			else
				m_PushSnow = true;
			
		}
		else
		{

		}
			
	}
	
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	//if (_OtherObj->GetName() == L"SnowObj")
	//{
	//	m_OverlappedSnowObj = dynamic_cast<CSnowObj*>(_OtherObj);
	//	if (m_OverlappedSnowObj->IsActive())
	//	{
	//		if (m_OverlappedSnowObj->IsRoll())
	//		{
	//			// 플레이어가 굴러가는 눈덩이에 탄다

	//		}
	//		else
	//			m_PushSnow = true;

	//	}
	//	else
	//	{

	//	}

	//}
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"SnowObj")
	{
		m_PushSnow = false;
	}
}

