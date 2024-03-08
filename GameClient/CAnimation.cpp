#include "pch.h"
#include "CAnimation.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"

CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::finaltick()
{
	if (m_bFinish)
		return;

	// 현재 프레임 정보
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		// 프레임이 마지막에 도달했다.
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			--m_CurFrmIdx;
			m_bFinish = true;
		}
	}
}

void CAnimation::render()
{
	// 현재 프레임 정보
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation을 재생하고 있는 오브젝트
	CObj* pOwnerObj = m_Animator->GetOwner();

	// 오브젝트의 위치
	Vec2 vPos = pOwnerObj->GetPos();

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	TransparentBlt(DC
		, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
		, (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y)
		, (int)(frm.SliceSize.x), (int)(frm.SliceSize.y)
		, m_Atlas->GetDC()
		, (int)(frm.StartPos.x), (int)(frm.StartPos.y)
		, (int)(frm.SliceSize.x), (int)(frm.SliceSize.y)
		, RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// 프레임 정보 생성
	for (int i = 0; i < _FrameCount; ++i)
	{
		tAnimFrm frm = {};
		frm.Duration = 1.f / (float)_FPS;
		frm.StartPos = _StartPos + Vec2(_SliceSize.x * i, 0.f);
		frm.SliceSize = _SliceSize;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFolderPath;
	strFilePath += GetName();
	strFilePath += L".anim";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 저장 실패");
		return;
	}

	// 애니메이션의 정보를 저장

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{

}




