#include "pch.h"
#include "CDbgRender.h"

CDbgRender::CDbgRender()
{

}

CDbgRender::~CDbgRender()
{

}

void CDbgRender::render()
{
	list<tDbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		(*iter).Age += DT;

	}
}
