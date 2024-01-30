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
	// DC ����
	ReleaseDC(m_hMainWnd, m_hDC);

	// Pen ����
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	// Brush ����
	for (int i = 0; i < 4; ++i) 
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// �Էµ� �ػ󵵸� �������� ���� ���� �������� ũ�⸦ ���
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };		
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// ������ ũ�� ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC �� ��, �귯�� ����
	CreateDefaultGDIObject();
	
	// Manager �ʱ�ȭ
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
	
	// ȭ�� Ŭ���� �۾�
	//Rectangle(m_hDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);

	CLevelMgr::GetInst()->render();

	CDbgRender::GetInst()->render();

	// �浹ó��

	// �̺�Ʈ

	// ����� �α�
}

void CEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) ����
	// DC ��? �������� ����
	// ��Ʈ�ʿ� �������ϱ� ���� �ʿ��� �ʼ� ���� ����ü
	m_hDC = ::GetDC(m_hMainWnd);
	// DC ���� ����
	// GetDC �� �����Ǵ� DC �� ����
	// ������ ��Ʈ�� - �Է� �������� ��Ʈ��
	// �� - BlackPen(Default)
	// �귯�� - White Brush(Default)


	// ���� ����� �� ����
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// ���� ����� �귯�� ����
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

}
