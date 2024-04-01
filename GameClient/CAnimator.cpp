#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
	, m_Repeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Other)
	: CComponent(_Other)
	, m_CurAnim(nullptr)
	, m_Repeat(_Other.m_Repeat)
{
	// ���� Animator�� ������ Animation���� �����ؼ� �����´�.
	for (const auto& pair : _Other.m_mapAnim)
	{
		CAnimation* pCloneAnim = pair.second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pair.first, pCloneAnim));
	}

	// ���� ������� �ִϸ��̼� ����
	if (nullptr != _Other.m_CurAnim)
	{
		m_CurAnim = FindAnimation(_Other.m_CurAnim->GetName());
	}
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator::finaltick()
{
	if (nullptr != m_CurAnim)
	{
		if (m_CurAnim->IsFinish() && m_Repeat)
		{
			m_CurAnim->Reset();
		}
		m_CurAnim->finaltick();
	}
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

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
	// �ִϸ��̼��� ���� ������ ��ηκ��� �ε��� ����
	CAnimation* pNewAnim = new CAnimation;
	if (FAILED(pNewAnim->Load(_strRelativeFilePath)))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ε� ����");
		return;
	}

	if (nullptr != FindAnimation(pNewAnim->GetName()))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"�ߺ��� �ִϸ��̼� �̸�");
		return;
	}

	pNewAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = FindAnimation(_AnimName);

	if (nullptr == m_CurAnim)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"Play �� �ִϸ��̼��� ã�� �� ����");
		return;
	}

	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}


