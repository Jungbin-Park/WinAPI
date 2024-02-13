#pragma once
#include "pch.h"

#include "CDbgRender.h"


void DrawDebugRect(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time);


void DrawDebugCircle(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time);


template<typename T>
void Safe_Del_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

template<typename T, UINT iSize>
void Safe_Del_Arr(T* (&Arr)[iSize])
{
	for (UINT i = 0; i < iSize; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}