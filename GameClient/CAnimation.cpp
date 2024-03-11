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

	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		// �������� �������� �����ߴ�.
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

	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation�� ����ϰ� �ִ� ������Ʈ
	CObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ�� ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
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

	// ������ ���� ����
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
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼��� ������ ����
	// �ִϸ��̼� �̸� ����
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");

	wstring strAnimName = GetName();
	fwprintf_s(pFile, L"%s\n\n", strAnimName.c_str());

	// ��Ʋ�� �ؽ�ó ���� ����
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

	// ������ ����
	// ������ ������ ����
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());

	// ������ ������ ������ ����
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
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		return E_FAIL;
	}

	// �ִϸ��̼��� ������ �б�
	// �ִϸ��̼� �̸� �б�
	wstring strAnimName;
	LoadWString(strAnimName, pFile);
	SetName(strAnimName);

	// ������ ���� �б�
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; i++)
	{
		tAnimFrm frm{};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}

	// ��Ʋ�� �ؽ�ó ���� �б�
	bool bAtlasTex = false;
	fread(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		wstring strKey;
		LoadWString(strKey, pFile);

		wstring strRelativePath;
		LoadWString(strRelativePath, pFile);

		m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	fclose(pFile);

	return S_OK;
}




