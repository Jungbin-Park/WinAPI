#pragma once


class CDbgRender
{
	SINGLE(CDbgRender)
private:
	list<tDbgRenderInfo>	m_RenderList;
	list<tDbgLog>			m_LogList;
	bool					m_bRender;

	float					m_LogLife;		// 로그 수명값
	int						m_LogSpace;		// 로그 위아래 간격
	Vec2					m_LogStartPos;	// 첫 로그 출력 위치

public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info){ m_RenderList.push_back(_info); }
	void AddDbgLog(const tDbgLog& _info) { m_LogList.push_back(_info); }

	bool IsDbgRender() { return m_bRender; }

public:
	void tick();
	void render();
};


