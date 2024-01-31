#pragma once

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	WORD	m_Matrix[(UINT)LAYER_TYPE::END];

public:
	void CollisionCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);

public:
	void init();
	void tick();
};

