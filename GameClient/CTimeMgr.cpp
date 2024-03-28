#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_FPS(0)
	, m_DeltaTime(0.f)
	, m_Time(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// GetTickCount() : 1000/s (너무 느림)
	// 초당 1000을 카운팅하기 때문에 정확도가 떨어진다.

	// 1초에 셀 수 있는 카운트 기준을 얻는다.
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	// 현재 카운트 계산
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 카운트와 현재 카운트의 차이값을 통해서 1프레임 간의 시간 값을 계산
	m_DeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) /(float) m_llFrequency.QuadPart;

	// DT 보정
	if (1.f / 60.f < m_DeltaTime)
		m_DeltaTime = 1.f / 60.f;

	// 누적 시간을 통해서 프로그램이 실행된 이후로 지나간 시간 값을 기록
	m_Time += m_DeltaTime;

	// 현재 카운트 값을 이전 카운트로 복사해 둠
	m_llPrevCount = m_llCurCount;

	// 초당 실행 횟수 (fps) 계산
	++m_FPS;

	// 1초에 한번씩 TextOut
	static float AccTime = 0.f;
	AccTime += m_DeltaTime;

	if (1.f < AccTime)
	{
		wchar_t szBuff[255] = {};
		swprintf_s(szBuff, L"DeltaTime : %f, FPS ; %f ", m_DeltaTime, 1.f / m_DeltaTime);
		//TextOut(CEngine::GetInst()->GetMainDC(), 10, 10, szBuff, wcslen(szBuff));
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);
		AccTime = 0.f;
		m_FPS = 0;
	}

	
}
