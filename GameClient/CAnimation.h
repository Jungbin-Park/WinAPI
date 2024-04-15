#pragma once
#include "CEntity.h"

// �� ����� ������
struct tAnimFrm
{
    Vec2    StartPos;
    Vec2    SliceSize;
    Vec2    Offset;
    float   Duration;   // ������ ���� �ð�
};

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_Animator;     // Animation�� �����ϰ� �ִ� Animator
    CTexture*           m_Atlas;        // Animation �̹����� �����ϰ� �ִ� Atlas Texture
    vector<tAnimFrm>    m_vecFrm;       // �� ������ ����

    float               m_Time;         // �����ð� üũ

    int                 m_CurFrmIdx;    // ���� ������
    bool                m_bFinish;      // �ִϸ��̼� ����� ������� �˸�

public:
    void SetAtlasTexture(CTexture* Atlas) { m_Atlas = Atlas; }
    bool IsFinish() { return m_bFinish; }

    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

    tAnimFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }
    int GetCurFrame() { return m_CurFrmIdx; }

public:
    void finaltick();
    void render();
    void Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);

    void Save(const wstring& _strRelativeFolderPath);
    int Load(const wstring& _strRelativeFilePath);

public:
    CLONE(CAnimation);

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

