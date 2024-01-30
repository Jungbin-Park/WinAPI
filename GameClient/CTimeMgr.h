#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	// LARGE_INTEGER : 8����Ʈ ���� ���
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	UINT			m_FPS;
	
	float			m_DeltaTime;	// ���α׷��� ���� ���ķ� ���� �ð�
	float			m_Time;			// ������ ���� �ð�

public:
	void init();
	void tick();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }
};

