#pragma once

// ������Ʈ���� ���� ��ǥ / ������ ��ǥ�� �ٸ�

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2	m_LookAt;	// ī�޶� �Ĵٺ��� �߽� ��ǥ
	Vec2	m_Diff;		// ī�޶� ��ġ�� ���� �ػ� �߽���ǥ���� ���̰�

	float	m_CamSpeed;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }

public:
	void init();
	void tick();

};

