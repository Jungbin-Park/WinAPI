#include "pch.h"
#include "CEngine.h"

#include "CLevelMgr.h"
#include "CDbgRender.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)	
	, m_Resolution{}
	, m_hDC(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
{

}

CEngine::~CEngine()
{
	// DC 삭제
	ReleaseDC(m_hMainWnd, m_hDC);

	// Pen 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	// Brush 삭제
	for (int i = 0; i < 4; ++i) 
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// 입력된 해상도를 가져가기 위한 실제 윈도우의 크기를 계산
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };		
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// 윈도우 크기 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC 및 펜, 브러쉬 생성
	CreateDefaultGDIObject();
	
	// Manager 초기화
	CKeyMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();

	return S_OK;
}

void CEngine::progress()
{
	// Managet tick
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	// Level Progress
	CLevelMgr::GetInst()->progress();
	
	// 화면 클리어 작업
	//Rectangle(m_hDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);

	CLevelMgr::GetInst()->render();

	CDbgRender::GetInst()->render();

	// 충돌처리

	// 이벤트

	// 디버깅 로그
}

void CEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) 생성
	// DC 란? 렌더링과 관련
	// 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	m_hDC = ::GetDC(m_hMainWnd);
	// DC 보유 정보
	// GetDC 로 생성되는 DC 의 정보
	// 목적지 비트맵 - 입력 윈도우의 비트맵
	// 펜 - BlackPen(Default)
	// 브러쉬 - White Brush(Default)


	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

}
