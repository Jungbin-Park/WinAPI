#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	WORD	m_Matrix[(UINT)LAYER_TYPE::END];

public:
	void CollisionCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(WORD) * (UINT)LAYER_TYPE::END); }
	void CollisionUnCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);

private:
	bool IsCollision(CCollider* _Left, CCollider* _Right);

public:
	void init();
	void tick();
};

