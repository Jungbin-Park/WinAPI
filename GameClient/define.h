#pragma once


#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							type(const type& _other) = delete;\
						public:\
							~type();

#define USE_PEN(DC, TYPE) CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(PEN_TYPE::TYPE))
#define USE_BRUSH(DC, TYPE) CSelectObj SelectBrush(DC, CEngine::GetInst()->GetBrush(BRUSH_TYPE::TYPE))

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define DC CEngine::GetInst()->GetSubDC()

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key)		KEY_CHECK(KEY::Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(KEY::Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(KEY::Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(KEY::Key, KEY_STATE::NONE)