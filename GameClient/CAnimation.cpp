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
	if (nullptr == m_Atlas)
		return;

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
	// 프레임 개수를 저장
	size_t FrmCount = m_vecFrm.size();
	fwrite(&FrmCount, sizeof(size_t), 1, pFile);

	// 각각의 프레임 정보를 저장
	for (size_t i = 0; i < m_vecFrm.size(); i++)
	{
		fwrite(&m_vecFrm[i], sizeof(tAnimFrm), 1, pFile);
	}

	// 아틀라스 텍스쳐 정보를 저장
	bool bAtlasTex = false;
	if (nullptr != m_Atlas)
		bAtlasTex = true;

	fwrite(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		wstring strKey = m_Atlas->GetKey();
		size_t len = strKey.length();
		fwrite(&len, sizeof(size_t), 1, pFile);
		fwrite(strKey.c_str(), sizeof(wchar_t), len, pFile);

		wstring strRelativePath = m_Atlas->GetRelativePath();
		len = strRelativePath.length();
		fwrite(&len, sizeof(size_t), 1, pFile);
		fwrite(strRelativePath.c_str(), sizeof(wchar_t), len, pFile);
	}
	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		return E_FAIL;
	}

	// 애니메이션의 정보를 읽기
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	// 프레임 정보 읽기
	for (size_t i = 0; i < FrmCount; i++)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}

	// 아틀라스 텍스처 정보 읽기
	bool bAtlasTex = false;
	fread(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		wstring strKey;
		wstring strRelativePath;

		wchar_t buff[256] = {};

		size_t len = 0;
		fread(&len, sizeof(size_t), 1, pFile);
		fread(buff, sizeof(wchar_t), len, pFile);
		strKey = buff;

		wmemset(buff, 0, 256);

		fread(&len, sizeof(size_t), 1, pFile);
		fread(buff, sizeof(wchar_t), len, pFile);
		strRelativePath = buff;

		m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	fclose(pFile);

	return S_OK;
}




