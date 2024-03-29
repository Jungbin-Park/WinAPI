#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

#include "CEngine.h"

CTexture::CTexture()
	: m_hDC{}
	, m_hBit{}
	, m_Info{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

int CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
		, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (nullptr == m_hBit)
	{
		MessageBox(nullptr, L"비트맵 로딩 실패", L"Asset 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// 로드된 비트맵의 정보를 확인한다.
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	// DC를 생성시켜서 로드된 비트맵이랑 연결한다.
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));

	return S_OK;
}

int CTexture::Create(UINT _Width, UINT _Height)
{
	// DC 생성
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// Bitmap 생성
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, _Height);

	// SubDC가 SubBitmap을 지정하게 함
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	// 로드된 비트맵의 정보를 확인한다.
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return S_OK;
}
