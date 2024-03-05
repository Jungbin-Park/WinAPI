#include "pch.h"
#include "CDbgRender.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CDbgRender::CDbgRender()
	: m_bRender(true)
	, m_LogLife(3.5f)
	, m_LogSpace(18)
	, m_LogStartPos(Vec2(0.f, 10.f))
{

}

CDbgRender::~CDbgRender()
{

}

void CDbgRender::tick()
{
	if (KEY_TAP(KEY::_0))
	{
		m_bRender ? m_bRender = false : m_bRender = true;
	}
}

void CDbgRender::render()
{
	list<tDbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
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

	// �α� ���� ���
	list<tDbgLog>::iterator logiter = m_LogList.begin();

	SetBkMode(DC, TRANSPARENT);

	int i = 0;
	for (; logiter != m_LogList.end();)
	{
		if (m_bRender)
		{
			// ������ �α��ϼ��� �Ʒ��ʿ� ����� �Ǿ�� ��
					// �α��� y�� offset ��ġ�� ����
			int yoffset = ((int)m_LogList.size() - (i + 1)) * m_LogSpace;
			
			// �α� Ÿ�� �� �۾� ���� ����
			switch (logiter->Type)
			{
			case LOG_TYPE::DBG_LOG:
				SetTextColor(DC, RGB(255, 255, 255));
				break;
			case LOG_TYPE::DBG_WARNING:
				SetTextColor(DC, RGB(240, 240, 20));
				break;
			case LOG_TYPE::DBG_ERROR:
				SetTextColor(DC, RGB(240, 20, 20));
				break;
			}
			// �α� ���
			TextOut(DC, (int)m_LogStartPos.x
				, (int)m_LogStartPos.y + yoffset
				, logiter->strLog.c_str()
				, (int)logiter->strLog.length());
		}
		

		// �α� ���� ���
		logiter->Age += DT;

		if (m_LogLife <= logiter->Age)
		{
			logiter = m_LogList.erase(logiter);
		}
		else
		{
			++logiter;
		}

		++i;
	}

	SetBkMode(DC, OPAQUE);
	SetTextColor(DC, RGB(0, 0, 0));
	
}
