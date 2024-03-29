#pragma once

// 정적 변수
// 1. 함수 내
// 2. 파일
// 3. 클래스



class CEntity
{
private:
	// 정적 맴버 선언
	static UINT g_NextID;	// 특정 클래스 내에 맴버로 정적변수를 선언

private:	
	const UINT	m_ID;		// 객체별 고유 ID
	wstring		m_strName;	

public:
	UINT GetID() { return m_ID; }

	void SetName(const wstring& _Name) { m_strName = _Name; }
	const wstring& GetName() { return m_strName; }

public:
	// CEntity 클래스는 추상클래스이다.
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Other);
	virtual ~CEntity();
};