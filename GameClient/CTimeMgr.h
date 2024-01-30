#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	// LARGE_INTEGER : 8바이트 정수 대용
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	UINT			m_FPS;
	
	float			m_DeltaTime;	// 프로그램이 켜진 이후로 지난 시간
	float			m_Time;			// 프레임 간격 시간

public:
	void init();
	void tick();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }
};

