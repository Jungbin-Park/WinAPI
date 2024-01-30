#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{

	}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{

	}

	~Vec2()
	{

	}
};

struct tDbgRenderInfo
{
	DBG_SHAPE	Shape;
	Vec2		Position;
	Vec2		Scale;
	COLORREF	Color;

	float		Duration;
	float		Age;
};