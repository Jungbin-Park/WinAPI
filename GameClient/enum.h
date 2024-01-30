#pragma once


enum class PEN_TYPE
{
	PEN_RED,
	PEN_GREEN,
	PEN_BLUE,	

	END,
};

enum class BRUSH_TYPE
{
	BRUSH_RED,
	BRUSH_GREEN,
	BRUSH_BLUE,
	BRUSH_GRAY,

	BRUSH_HOLLOW,
	BRUSH_BLACK,

	END,
};

enum class LEVEL_TYPE
{
	LOGO_START,
	EDITOR,

	STAGE_01,
	STAGE_02,
	STAGE_03,

	BOSS_01,

	END,
};

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	RUN,
	DASH,
	ATTACK,
	HIT,
	DEAD,

	END,
};

enum class DBG_SHAPE
{
	CIRCLE,
	RECT,
};