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
		Safe_Del_Vec(m_arrObj[i]);
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
		vector<CObj*>::iterator iter = m_arrObj[i].begin();

		for (; iter < m_arrObj[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
			}
			else
			{
				(*iter)->render();
				iter++;
			}
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

CObj* CLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		CObj* pFindObj = FindObjectByName((LAYER_TYPE)i, _Name);

		if (pFindObj)
		{
			return pFindObj;
		}
	}

	return nullptr;
}

CObj* CLevel::FindObjectByName(LAYER_TYPE _Type, const wstring& _Name)
{
	for (size_t i = 0; i < m_arrObj[(UINT)_Type].size(); ++i)
	{
		if (_Name == m_arrObj[(UINT)_Type][i]->GetName())
		{
			return m_arrObj[(UINT)_Type][i];
		}
	}

	return nullptr;
}


