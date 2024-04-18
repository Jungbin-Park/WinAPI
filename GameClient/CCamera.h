#pragma once

// ������Ʈ���� ���� ��ǥ / ������ ��ǥ�� �ٸ�

typedef void(CLevel::*CAMDELEGATE)(void);

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CAM_EFFECT_INFO
{
	CAM_EFFECT	Effect;
	float		Duration;
	float		Time;
	float		Alpha;
};

class CTexture;
class CLevel;

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2					m_LookAt;	// ī�޶� �Ĵٺ��� �߽� ��ǥ
	Vec2					m_Diff;		// ī�޶� ��ġ�� ���� �ػ� �߽���ǥ���� ���̰�
	float					m_CamSpeed;
	list<CAM_EFFECT_INFO>	m_EffectList;

	// ī�޶� �̵� ����
	Vec2					m_MoveDir;	
	int						m_DesY;

	CTexture*	m_FadeTex;
	CTexture*	m_RedTex;

	bool					m_bCameraMove;
	bool					m_bCamFixed;

	CLevel*					m_CamFixedInst;
	CAMDELEGATE				m_CamFixedDelegate;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }
	Vec2 GetLookAt() { return m_LookAt; }
	bool IsMoveDone() { return m_bCamFixed; }

	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);
	void SetCameraDes(Vec2 _Pos);

	void SetCamFixedDelegate(CLevel* _Inst, CAMDELEGATE _MemFunc)
	{
		m_CamFixedInst = _Inst;
		m_CamFixedDelegate = _MemFunc;
	}

	void DrawBlackTex();

public:
	void init();
	void tick();
	void render();

private:
	void Move();
	void CameraEffect();
};

