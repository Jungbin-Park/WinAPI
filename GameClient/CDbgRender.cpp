#include "pch.h"
#include "CDbgRender.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CDbgRender::CDbgRender()
	: m_bRender(true)
{

}

CDbgRender::~CDbgRender()
{

}

void CDbgRender::tick()
{
	if (KEY_TAP(_0))
	{
		m_bRender ? m_bRender = false : m_bRender = true;
	}
}

void CDbgRender::render()
{
	list<tDbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		USE_BRUSH(DC, BRUSH_HOLLOW);
		CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(iter->Color));

		// DBG �� Rect �� �簢���� �׸���.
		if (m_bRender && DBG_SHAPE::RECT == iter->Shape)
		{
			Rectangle(DC
				, (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}

		// DBG_SHAPE �� Circle �̸� ���� �׸���.
		else if (m_bRender && DBG_SHAPE::CIRCLE == iter->Shape)
		{
			Ellipse(DC
				, (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}


		// �ش� ����׷��� ������ ������ ���ϸ� ����Ʈ���� �����Ѵ�.
		(*iter).Age += DT;
		if (iter->Duration < iter->Age)
		{
			iter = m_RenderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
