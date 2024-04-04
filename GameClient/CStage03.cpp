#include "pch.h"
#include "CStage03.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAssetMgr.h"

CStage03::CStage03()
	:m_Img(nullptr)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"\\texture\\Map\\lvl3.png", L"\\texture\\Map\\lvl3.png");
}

CStage03::~CStage03()
{

}

void CStage03::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	TransparentBlt(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
		, (int)(vPos.y - m_Img->GetHeight() / 2.f)
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC(), 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), RGB(255, 0, 255));

}