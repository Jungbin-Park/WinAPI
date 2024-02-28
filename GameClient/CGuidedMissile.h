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
	void FindTarget();

public:
	CGuidedMissile();
	~CGuidedMissile();
};

