#include "pch.h"
#include "CEndLevel.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CSound.h"

CEndLevel::CEndLevel()
	: m_Img(nullptr)
	, m_Logo(nullptr)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\GameOver.png", L"texture\\UI\\GameOver.png");
	m_Logo = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\GameOverLogo.png", L"texture\\UI\\GameOverLogo.png");
}

CEndLevel::~CEndLevel()
{
	
}

void CEndLevel::begin()
{
	CLevel::begin();
}

void CEndLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::LOGO_START);
	}
	if (KEY_TAP(KEY::ESC))
	{
		DestroyWindow(CEngine::GetInst()->GetMainWnd());
	}
}

void CEndLevel::render()
{
	CLevel::render();

	Vec2 vPos = CCamera::GetInst()->GetLookAt();

	// ================================
	//			 ������ ���
	// ================================
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLACK);
	Rectangle(DC, -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);


	// ================================
	//				���
	// ================================
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
		, (int)(vPos.y - m_Img->GetHeight() / 2.f)
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC(), 0, 0, m_Img->GetWidth(), m_Img->GetHeight(), bf);


	// ================================
	//			 ���� �ΰ�
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

	BLENDFUNCTION bfl = {};

	bfl.BlendOp = AC_SRC_OVER;
	bfl.BlendFlags = 0;
	bfl.SourceConstantAlpha = (int)eAlpha;
	bfl.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(DC, (int)(vPos.x - m_Logo->GetWidth() / 2.f)
		, (int)(vPos.y - m_Logo->GetHeight() / 2.f)
		, m_Logo->GetWidth(), m_Logo->GetHeight()
		, m_Logo->GetDC(), 0, 0, m_Logo->GetWidth(), m_Logo->GetHeight(), bfl);
}

void CEndLevel::Enter()
{
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"End", L"sound\\Music\\GameOver.wav");
	pSound->SetVolume(100.f);
	pSound->PlayToBGM(false);
}

void CEndLevel::Exit()
{
}


