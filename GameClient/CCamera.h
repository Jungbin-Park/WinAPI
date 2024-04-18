#pragma once

// 오브젝트들의 실제 좌표 / 랜더링 좌표가 다름

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
	Vec2					m_LookAt;	// 카메라가 쳐다보는 중심 좌표
	Vec2					m_Diff;		// 카메라 위치와 원점 해상도 중심좌표와의 차이값
	float					m_CamSpeed;
	list<CAM_EFFECT_INFO>	m_EffectList;

	// 카메라 이동 관련
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

