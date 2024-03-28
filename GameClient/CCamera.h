#pragma once

// 오브젝트들의 실제 좌표 / 랜더링 좌표가 다름

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2	m_LookAt;	// 카메라가 쳐다보는 중심 좌표
	Vec2	m_Diff;		// 카메라 위치와 원점 해상도 중심좌표와의 차이값

	float	m_CamSpeed;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }

public:
	void init();
	void tick();

};

