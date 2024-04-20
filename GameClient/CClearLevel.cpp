#include "pch.h"
#include "CClearLevel.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CSound.h"

CClearLevel::CClearLevel()
	: m_Img(nullptr)
	, m_Logo(nullptr)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\GameOverLogo.png", L"texture\\UI\\GameOverLogo.png");
	m_Logo = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\Congratulation.png", L"texture\\UI\\Congratulation.png");
}

CClearLevel::~CClearLevel()
{
}

void CClearLevel::begin()
{
	CLevel::begin();
}

void CClearLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::LOGO_START);
	}
}

void CClearLevel::render()
{
	CLevel::render();

	Vec2 vPos = CCamera::GetInst()->GetLookAt();

	// ================================
	//			 검은색 배경
	// ================================
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLACK);
	Rectangle(DC, -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);

	// ================================
	//				배경
	// ================================
	static float eAlpha = 0;
	static float dir = 1;

	eAlpha += DT * 500.f * dir;

	if (255.f <= eAlpha)
	{
		dir *= -1.f;
	}
	else if (eAlpha <= 0.f)
	{
		dir *= -1.f;
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)eAlpha;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
		, (int)(vPos.y - m_Img->GetHeight() / 2.f)
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC(), 0, 0, m_Img->GetWidth(), m_Img->GetHeight(), bf);

	// ================================
	//			 엔딩 로고
	// ================================
	
	BLENDFUNCTION bfl = {};

	bfl.BlendOp = AC_SRC_OVER;
	bfl.BlendFlags = 0;
	bfl.SourceConstantAlpha = 255;
	bfl.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vPos.x - m_Logo->GetWidth() / 2.f)
		, (int)(vPos.y - m_Logo->GetHeight() / 2.f)
		, m_Logo->GetWidth(), m_Logo->GetHeight()
		, m_Logo->GetDC(), 0, 0, m_Logo->GetWidth(), m_Logo->GetHeight(), bfl);
}

void CClearLevel::Enter()
{
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Clear", L"sound\\Music\\NextStage.wav");
	pSound->SetVolume(100.f);
	pSound->PlayToBGM(false);
}

void CClearLevel::Exit()
{
}


