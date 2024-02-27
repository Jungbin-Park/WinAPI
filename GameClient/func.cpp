#include "pch.h"

#include "CDbgRender.h"

void DrawDebugRect(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::RECT;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRender::GetInst()->AddDbgRenderInfo(info);
}

void DrawDebugCircle(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::CIRCLE;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRender::GetInst()->AddDbgRenderInfo(info);
}

#include "CTaskMgr.h"
void SpawnObject(CLevel* _Level, LAYER_TYPE _type, CObj* _pSpawned)
{
	tTask task = {};
	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.lParam = (DWORD_PTR)_Level;
	task.rParam = (DWORD_PTR)_pSpawned;
	task.wParam = (DWORD_PTR)_type;

	CTaskMgr::GetInst()->AddTask(task);
}


