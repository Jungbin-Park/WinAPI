#include "pch.h"
#include "CPathMgr.h"

#include "resource.h"
#include "CEngine.h"

CPathMgr::CPathMgr()
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	// 실행 경로를 얻어낸다
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);

	// bin 폴더의 상위폴더로 접근한다
	GetParentPath(szBuffer);

	// \\content\\ 를 붙여둔다
	m_Content = szBuffer;
	m_Content += L"\\content\\";

	// OutputFile 폴더의 상위 폴더로 접근한다
	GetParentPath(szBuffer);
	m_Solution = szBuffer;

	// String Table 에서 프로젝트 이름을 얻어온다.
	wchar_t szProjName[50] = {};
	LoadStringW(CEngine::GetInst()->GetProcessInstance(), IDS_APP_TITLE, szProjName, 50);

	// Solution 경로에서 프로젝트 이름을 붙인다.
	m_Proj = m_Solution + L"\\" + szProjName;
}

void CPathMgr::render()
{
	TextOut(DC, 10, 10, m_Solution.c_str(), (int)m_Solution.length());
	TextOut(DC, 10, 30, m_Proj.c_str(), (int)m_Proj.length());
	TextOut(DC, 10, 50, m_Content.c_str(), (int)m_Content.length());
}

void CPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);

	for (size_t i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}
