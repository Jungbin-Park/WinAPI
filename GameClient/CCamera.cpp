#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_CamSpeed(600.f)
	, m_FadeTex(nullptr)
	, m_bCameraMove(false)
	, m_bCamFixed(false)
	, m_MoveDir(0.f, 0.f)
	, m_DesY(498)
{

}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_LookAt = Vec2(vResol.x / 2.f, vResol.y / 2.f);

	// ������ �ػ󵵶� ������ ũ���� ������ �ؽ��ĸ� ���� 
	m_FadeTex = CAssetMgr::GetInst()->CreateTexture(L"FadeTexture", (UINT)vResol.x, (UINT)vResol.y);

	// ������ �ػ󵵶� ������ ũ���� ������ �ؽ��ĸ� ����
	//m_RedTex = CAssetMgr::GetInst()->CreateTexture(L"RedTexture", (UINT)vResol.x, (UINT)vResol.y);

	
	// 1. Red Texture�� Red Brush�� Rectangle�� �׸���
	//USE_BRUSH(m_RedTex->GetDC(), BRUSH_TYPE::BRUSH_RED);
	//Rectangle(m_RedTex->GetDC(), -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);

	// 2. SetPixel �Լ��� �̿��� �׸���
	/*for (UINT Row = 0; Row < vResol.y; ++Row)
	{
		for (UINT Col = 0; Col < vResol.x; ++Col)
		{
			SetPixel(m_RedTex->GetDC(), Col, Row, RGB(255, 0, 0));
		}
	}*/
}

void CCamera::tick()
{
	// ī�޶� �̵�
	Move();

	// �ػ� �߽ɰ� ī�޶� �ٶ󺸰� �ִ� ���� ���� ���̰�
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - Vec2(vResol.x / 2.f, vResol.y / 2.f);

	// ī�޶� ȿ��
	CameraEffect();

	if (m_bCameraMove)
	{
		m_MoveDir.y = (int)(m_DesY - m_LookAt.y);
		
		if (!m_MoveDir.IsZero())
		{
			m_MoveDir.Normalize();
			m_LookAt.y += (int)(m_MoveDir.y * DT * m_CamSpeed);

		}
		else
		{
			m_bCameraMove = false;
			m_bCamFixed = true;
	
		}
	}

	if (m_bCamFixed)
	{
		if (m_CamFixedInst && m_CamFixedDelegate)
		{
			(m_CamFixedInst->*m_CamFixedDelegate)();
			m_bCamFixed = false;
		}
	}
	
}

void CCamera::render()
{
	if (m_EffectList.empty())
		return;

	CAM_EFFECT_INFO& info = m_EffectList.front();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;	// ����(0~255)
	bf.AlphaFormat = 0;	

	/*AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), m_FadeTex->GetDC()
		, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);*/

	AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), m_FadeTex->GetDC()
		, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);

}

void CCamera::Move()
{
	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * m_CamSpeed;

	
}

void CCamera::CameraEffect()
{
	while(true)
	{
		if (m_EffectList.empty())
			return;

		CAM_EFFECT_INFO& info = m_EffectList.front();
		info.Time += DT;

		if (info.Duration < info.Time)
		{
			m_EffectList.pop_front();
		}
		else
		{
			break;
		}
	}

	CAM_EFFECT_INFO& info = m_EffectList.front();

	if (CAM_EFFECT::FADE_IN == info.Effect)
	{
		// ���İ��� 0�� �����������
		info.Alpha = (1.f - (info.Time / info.Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == info.Effect)
	{
		// ���İ��� 255�� �����������
		info.Alpha = (info.Time / info.Duration) * 255.f;
	}
}

void CCamera::DrawBlackTex()
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();

	// 1. Red Texture�� Red Brush�� Rectangle�� �׸���
	USE_BRUSH(m_FadeTex->GetDC(), BRUSH_TYPE::BRUSH_BLACK);
	Rectangle(m_FadeTex->GetDC(), -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);
}

void CCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	CAM_EFFECT_INFO info = {};

	info.Effect = _Effect;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Alpha = 0.f;

	m_EffectList.push_back(info);
}

void CCamera::SetCameraDes(Vec2 _Pos)
{
	m_bCameraMove = true;
	m_bCamFixed = false;
	m_DesY = _Pos.y;
}
