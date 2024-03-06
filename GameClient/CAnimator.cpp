#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::finaltick()
{
	if (nullptr != m_CurAnim)
		m_CurAnim->finaltick();
}

void CAnimator::render()
{
	if (nullptr != m_CurAnim)
		m_CurAnim->render();
}

void CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	// 동일한 이름의 Animation이 이미 Animator에 있는 경우
	CAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	// Animation 객체를 하나 생성
	pAnim = new CAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);

	// Animation이 Animator에 등록되는 이름(키)을 알게 한다.
	pAnim->SetName(_AnimName);

	// Animation에 본인이 소속되는 Animator를 알게 한다.
	pAnim->m_Animator = this;

	// Animator가 Animation을 Map에 넣는다.
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}


