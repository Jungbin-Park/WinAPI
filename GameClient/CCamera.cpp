#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_CamSpeed(500.f)
	, m_Effect(CAM_EFFECT::NONE)
	, m_Duration(0.f)
	, m_Time(0.f)
	, m_FadeTex(nullptr)
	, m_Alpha(0.f)
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
}

void CCamera::render()
{
	if (m_Alpha <= 0.f)
		return;

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)m_Alpha;	// ����(0~255)
	bf.AlphaFormat = 0;	

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
	if (CAM_EFFECT::NONE == m_Effect)
		return;

	m_Time += DT;
	if (m_Duration < m_Time)
	{
		m_Effect = CAM_EFFECT::NONE;
	}

	if (CAM_EFFECT::FADE_IN == m_Effect)
	{
		// ���İ��� 0�� �����������
		m_Alpha = (1.f - (m_Time / m_Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == m_Effect)
	{
		// ���İ��� 255�� �����������
		m_Alpha = (m_Time / m_Duration) * 255.f;
	}
}

void CCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	m_Effect = _Effect;
	m_Duration = _Duration;
	m_Time = 0.f;
}
