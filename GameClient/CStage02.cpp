#include "pch.h"
#include "CStage02.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAssetMgr.h"

CStage02::CStage02()
	:m_Img(nullptr)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"\\texture\\Map\\lvl2.png", L"\\texture\\Map\\lvl2.png");
}

CStage02::~CStage02()
{

}

void CStage02::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	TransparentBlt(DC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
		, (int)(vPos.y - m_Img->GetHeight() / 2.f)
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC(), 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), RGB(255, 0, 255));

}
