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
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼��� ������ ����
	// ������ ������ ����
	size_t FrmCount = m_vecFrm.size();
	fwrite(&FrmCount, sizeof(size_t), 1, pFile);

	// ������ ������ ������ ����
	for (size_t i = 0; i < m_vecFrm.size(); i++)
	{
		fwrite(&m_vecFrm[i], sizeof(tAnimFrm), 1, pFile);
	}

	// ��Ʋ�� �ؽ��� ������ ����
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

	// �ִϸ��̼��� ������ �б�
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	// ������ ���� �б�
	for (size_t i = 0; i < FrmCount; i++)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}

	// ��Ʋ�� �ؽ�ó ���� �б�
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




