#pragma once

class CCollider;

union COLLIDER_ID
{
	struct
	{
		DWORD LeftID;
		DWORD RightID;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	WORD					m_Matrix[(UINT)LAYER_TYPE::END];

	// 각각의 충돌체가 서로 이전에도 충돌중이었는지에 대한 정보를 저장하고 있어야 한다.
	map<ULONGLONG, bool>	m_mapCollisionInfo;

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

