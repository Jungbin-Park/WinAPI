#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CTexture.h"


CStartLevel::CStartLevel()
	: m_Img(nullptr)
	, m_Logo(nullptr)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\StartLevel.png", L"texture\\UI\\StartLevel.png");
	m_Logo = CAssetMgr::GetInst()->LoadTexture(L"texture\\UI\\StartLogo.png", L"texture\\UI\\StartLogo.png");
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::begin()
{
	CLevel::begin();
}

void CStartLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CStartLevel::render()
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
	//			 스타트 문장
	// ================================
	static float alpha = 0;
	static float dir = 1;

	alpha += DT * 500.f * dir;

	if (255.f <= alpha)
	{
		dir *= -1.f;
	}
	else if (alpha <= 0.f)
	{
		dir *= -1.f;
	}

	BLENDFUNCTION bfl = {};

	bfl.BlendOp = AC_SRC_OVER;
	bfl.BlendFlags = 0;
	bfl.SourceConstantAlpha = (int)alpha;
	bfl.AlphaFormat = AC_SRC_ALPHA;

	
	AlphaBlend(DC, (int)(vPos.x - m_Logo->GetWidth() / 2.f)
		, 700/*(int)(vPos.y - m_Logo->GetHeight() / 2.f)*/
		, m_Logo->GetWidth(), m_Logo->GetHeight()
		, m_Logo->GetDC(), 0, 0, m_Logo->GetWidth(), m_Logo->GetHeight(), bfl);


	
}

void CStartLevel::Enter()
{

}

void CStartLevel::Exit()
{
}


