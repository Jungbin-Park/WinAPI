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
	// 원본 Animator가 보유한 Animation들을 복제해서 가져온다.
	for (const auto& pair : _Other.m_mapAnim)
	{
		CAnimation* pCloneAnim = pair.second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pair.first, pCloneAnim));
	}

	// 현재 재생중인 애니메이션 설정
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

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
	// 애니메이션을 만들어서 지정된 경로로부터 로딩을 진행
	CAnimation* pNewAnim = new CAnimation;
	if (FAILED(pNewAnim->Load(_strRelativeFilePath)))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 로딩 실패");
		return;
	}

	if (nullptr != FindAnimation(pNewAnim->GetName()))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"중복된 애니메이션 이름");
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
		LOG(LOG_TYPE::DBG_ERROR, L"Play 할 애니메이션을 찾을 수 없음");
		return;
	}

	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}


