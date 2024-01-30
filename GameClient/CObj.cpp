#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CObj::CObj()
{

}

CObj::~CObj()
{

}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	return nullptr;
}

void CObj::begin()
{

}

void CObj::tick()
{
	// 방향키가 눌리면 이동

	// 현실 시간 동기화 
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	float fSpeed = 1000.f;


	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		m_Pos.x -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		m_Pos.x += fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		m_Pos.y -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		m_Pos.y += fSpeed * DT;
	}
}

void CObj::finaltick()
{

}

void CObj::render()
{
	HDC dc = CEngine::GetInst()->GetMainDC();

	// 렌더링 과정 문제점(화면 클리어)
	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);

	
}


