#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

UINT g_RealKey[(UINT)KEY::KEY_END] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',

	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,

	VK_RETURN,
	VK_SPACE,
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_ESCAPE,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::KEY_END; ++i)
	{
		tKeyInfo info = {};
		info.eKey = (KEY)i;
		info.eKeyState = KEY_STATE::NONE;
		info.bPressed = false;

		m_vecKeyInfo.push_back(info);
	}

	
}

void CKeyMgr::tick()
{
	// MainWnd 포커싱
	if (CEngine::GetInst()->GetMainWnd() == GetFocus())
	{
		for (UINT i = 0; i < (UINT)m_vecKeyInfo.size(); ++i)
		{
			// 지금 키가 눌려있는지 체크
			if (0x8001 & GetAsyncKeyState(g_RealKey[(UINT)m_vecKeyInfo[i].eKey]))
			{
				// 이전에도 눌려있었는지 체크
				if (m_vecKeyInfo[i].bPressed)
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::PRESSED;
				}
				// 이전에도 눌려있지 않았고, 지금은 눌려있다.
				else
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::TAP;
				}

				m_vecKeyInfo[i].bPressed = true;
			}
			// 키가 안눌려있다
			else
			{
				// 이전에는 눌려 있었다.
				if (m_vecKeyInfo[i], )

				// 이전에도 눌려있지 않았고, 지금도 안 눌려있다
				else {}

			}
		}
	}
	// 윈도우 포커싱 해제됨
	else
	{
		
	}
	

	
}
