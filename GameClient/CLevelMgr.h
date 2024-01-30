#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];	
	CLevel*		m_pCurrentLevel;	// ���� level pointer
	// ������ ���� -> �θ�(�Ŵ���) �����ͷ� �ڽ�(����) �����͸� ����ų �� ����
	
public:
	void init();
	void progress();
	void render();
};

