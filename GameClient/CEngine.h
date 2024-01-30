#pragma once

// 게임 최고 관리자
class CEngine
{
	SINGLE(CEngine)
private:
	HWND		m_hMainWnd;		// 메인 윈도우 핸들
	POINT		m_Resolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// 메인 윈도우 DC

	HDC			m_hSubDC;		// 보조 DC
	HBITMAP		m_hSubBitmap;	// 보조 Bitmap

	HPEN		m_arrPen[(UINT)PEN_TYPE::END];
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];


public:
	int init(HWND _hWnd, POINT _Resolution);
	void progress();

private:
	void CreateDefaultGDIObject();

public:
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC	GetSubDC() { return m_hSubDC; }

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	HBRUSH GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }

};


