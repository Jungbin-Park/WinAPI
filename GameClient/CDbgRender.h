#pragma once

class CDbgRender
{
	SINGLE(CDbgRender)
private:
	list< tDbgRenderInfo>	m_RenderList;

public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}


public:
	void render();
};

