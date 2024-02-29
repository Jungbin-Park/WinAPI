#pragma once

#include "CMissile.h"

class CGuidedMissile :
	public CMissile
{
private:
	CObj*	m_Target;

	float	m_Range;

public:
	virtual void tick() override;

private:
	virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
	void FindTarget();

public:
	CGuidedMissile();
	~CGuidedMissile();
};

