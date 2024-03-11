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
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 저장 실패");
		return;
	}

	// 애니메이션의 정보를 저장
	// 애니메이션 이름 저장
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");

	wstring strAnimName = GetName();
	fwprintf_s(pFile, L"%s\n\n", strAnimName.c_str());

	// 아틀라스 텍스처 정보 저장
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	if (nullptr == m_Atlas)
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", L"None");
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", L"None");
	}
	else
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", m_Atlas->GetKey().c_str());
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", m_Atlas->GetRelativePath().c_str());
	}
	fwprintf_s(pFile, L"\n");

	// 프레임 정보
	// 프레임 개수를 저장
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());

	// 각각의 프레임 정보를 저장
	size_t FrmCount = m_vecFrm.size();
	for (size_t i = 0; i < FrmCount; i++)
	{
		fwprintf_s(pFile, L"[FRAME_INDEX]\t%d\n", (int)i);
		fwprintf_s(pFile, L"[START_POS]\t%f  %f\n", m_vecFrm[i].StartPos.x, m_vecFrm[i].StartPos.y);
		fwprintf_s(pFile, L"[SLICE_SIZE]\t%f  %f\n", m_vecFrm[i].SliceSize.x, m_vecFrm[i].SliceSize.y);
		fwprintf_s(pFile, L"[OFFSET]\t\t%f  %f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);
		fwprintf_s(pFile, L"[DURATION]  \t%f\n", m_vecFrm[i].Duration);
		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile)
	{
		return E_FAIL;
	}

	// 애니메이션의 정보를 읽기
	// 애니메이션 이름 읽기
	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;
		
		// 애니메이션 이름 읽기
		if (strRead == L"[ANIMATION_NAME]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			SetName(szReadBuff);
		}
		// 아틀라스 텍스쳐 읽기
		else if (strRead == L"[ATLAS_TEXTURE]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strKey = szReadBuff;

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strPath = szReadBuff;

			if (strKey != L"None" && strPath != L"None")
			{
				m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strPath);
			}

		}
		// 프레임 정보 읽기
		else if (strRead == L"[FRAME_COUNT]")
		{
			int frmCount = 0;
			fwscanf_s(pFile, L"%d", &frmCount);

			for (int i = 0; i < frmCount; i++)
			{
				tAnimFrm frm = {};

				// [START_POS]가 나올 때까지 읽어들인다.
				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } 
				while (wcscmp(szReadBuff, L"[START_POS]"));

				fwscanf_s(pFile, L"%f%f", &frm.StartPos.x, &frm.StartPos.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.SliceSize.x, &frm.SliceSize.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.Offset.x, &frm.Offset.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f", &frm.Duration);

				m_vecFrm.push_back(frm);
			}
		}
	}

	fclose(pFile);

	return S_OK;
}




