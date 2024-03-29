#pragma once

// ������Ʈ���� ���� ��ǥ / ������ ��ǥ�� �ٸ�

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

class CTexture;

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2		m_LookAt;	// ī�޶� �Ĵٺ��� �߽� ��ǥ
	Vec2		m_Diff;		// ī�޶� ��ġ�� ���� �ػ� �߽���ǥ���� ���̰�
	float		m_CamSpeed;

	CAM_EFFECT	m_Effect;
	float		m_Duration;
	float		m_Time;
	float		m_Alpha;

	CTexture*	m_FadeTex;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }

	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

public:
	void init();
	void tick();
	void render();

private:
	void Move();
	void CameraEffect();
};

