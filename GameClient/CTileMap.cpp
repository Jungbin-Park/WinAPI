#include "pch.h"
#include "CTileMap.h"

#include "CEngine.h"
#include "CDbgRender.h"

#include "CTexture.h"

CTileMap::CTileMap()
	: m_Row(1)
	, m_Col(1)
	, m_TileSize(Vec2(TILE_SIZE, TILE_SIZE))
	, m_AtlasTex(nullptr)
{
}

CTileMap::~CTileMap()
{
}

void CTileMap::finaltick()
{
}

void CTileMap::render()
{
	render_tile();

	if (CDbgRender::GetInst()->IsDbgRender())
	{
		render_grid();
	}
}

void CTileMap::render_grid()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Row; i++)
	{
		for (UINT j = 0; j < m_Col; j++)
		{
			Rectangle(DC, (int)(vRenderPos.x + m_TileSize.x * j), (int)(vRenderPos.y + m_TileSize.y * i)
				, (int)(vRenderPos.x + m_TileSize.x * j + m_TileSize.x), (int)(vRenderPos.y + m_TileSize.y * i + m_TileSize.y));
		}
	}
}

void CTileMap::render_tile()
{
	if (nullptr == m_AtlasTex)
		return;

	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Row; ++i)
	{
		for (UINT j = 0; j < m_Col; ++j)
		{
			BitBlt(DC, (int)(vRenderPos.x + m_TileSize.x * j), (int)(vRenderPos.y + m_TileSize.y * i)
				, m_TileSize.x, m_TileSize.y, m_AtlasTex->GetDC(), 0, 0, SRCCOPY);
		}
	}
}

void CTileMap::SetRow(UINT _Row)
{
	m_Row = _Row;
	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void CTileMap::SetCol(UINT _Col)
{
	m_Col = _Col;
	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

