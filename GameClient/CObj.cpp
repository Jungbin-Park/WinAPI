#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CComponent.h"

CObj::CObj()
	: m_Type(LAYER_TYPE::NONE)
{

}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecCom);
}

void CObj::begin()
{

}

void CObj::tick()
{
	
}

void CObj::finaltick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->finaltick();
	}
}

void CObj::render()
{
	HDC dc = CEngine::GetInst()->GetSubDC();

	// ������ ���� ������(ȭ�� Ŭ����)
	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);
}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	return _Component;
}


