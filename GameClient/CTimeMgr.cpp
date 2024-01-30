#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_DeltaTime(0.f)
	, m_Time(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// GetTickCount() : 1000/s (�ʹ� ����)
	// �ʴ� 1000�� ī�����ϱ� ������ ��Ȯ���� ��������.

	// 1�ʿ� �� �� �ִ� ī��Ʈ ������ ��´�.
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);

	
}

void CTimeMgr::tick()
{
	// ���� ī��Ʈ ���
	QueryPerformanceCounter(&m_llCurCount);

	// ���� ī��Ʈ�� ���� ī��Ʈ�� ���̰��� ���ؼ� 1������ ���� �ð� ���� ���
	m_DeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) /(float) m_llFrequency.QuadPart;

	// ���� �ð��� ���ؼ� ���α׷��� ����� ���ķ� ������ �ð� ���� ���
	

	// ���� ī��Ʈ ���� ���� ī��Ʈ�� ������ ��
	m_llPrevCount = m_llCurCount;




	// 1�ʿ� �ѹ��� TextOut
	static float AccTime = 0.f;
	AccTime += m_DeltaTime;

	if (1.f < AccTime)
	{
		wchar_t szBuff[255] = {};
		swprintf_s(szBuff, L"DeltaTime : %f, FPS ; %f ", m_DeltaTime, 1.f / m_DeltaTime);
		//TextOut(CEngine::GetInst()->GetMainDC(), 10, 10, szBuff, wcslen(szBuff));
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);
		AccTime = 0.f;
	}

	
}
