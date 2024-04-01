#include "pch.h"
#include "CTile.h"

CTile::CTile()
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::begin()
{
}

void CTile::tick()
{
}

void CTile::render()
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	Rectangle(DC, (int)vRenderPos.x, (int)vRenderPos.y
		, (int)vRenderPos.x + (int)vScale.x, (int)vRenderPos.y + (int)vScale.y);
}


