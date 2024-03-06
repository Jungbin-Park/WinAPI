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
	// ������ �̸��� Animation�� �̹� Animator�� �ִ� ���
	CAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	// Animation ��ü�� �ϳ� ����
	pAnim = new CAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);

	// Animation�� Animator�� ��ϵǴ� �̸�(Ű)�� �˰� �Ѵ�.
	pAnim->SetName(_AnimName);

	// Animation�� ������ �ҼӵǴ� Animator�� �˰� �Ѵ�.
	pAnim->m_Animator = this;

	// Animator�� Animation�� Map�� �ִ´�.
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}


