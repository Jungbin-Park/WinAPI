#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CCollider.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		Save_Del_Vec(m_arrObj[i]);
	}
	
}

void CLevel::begin()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->begin();
		}
	}
}

void CLevel::tick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->tick();
		}
	}
}

void CLevel::finaltick()
{
	// 이전 프레임 충돌체 등록 정보 Clear
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		m_arrCollider[i].clear();
	}

	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->finaltick();
		}
	}
}

void CLevel::render()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->render();
		}
	}
}

void CLevel::AddObject(LAYER_TYPE _Layer, CObj* _Obj)
{
	m_arrObj[(UINT)_Layer].push_back(_Obj);
	_Obj->m_Type = _Layer;
}

void CLevel::RegisterCollider(CCollider* _Collider)
{
	LAYER_TYPE Layer = _Collider->GetOwner()->GetLayerType();
	m_arrCollider[(UINT)Layer].push_back(_Collider);
}


