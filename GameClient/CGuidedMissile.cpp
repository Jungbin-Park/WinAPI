#include "pch.h"
#include "CGuidedMissile.h"

CGuidedMissile::CGuidedMissile()
	: m_Target(nullptr)
{

}

CGuidedMissile::~CGuidedMissile()
{

}

void CGuidedMissile::tick()
{
	// ���� ����� ��ȿ�� �� Ȯ��
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// ���� ����� ���ϴ� ������ ����

	CMissile::tick();
}

void CGuidedMissile::FindTarget()
{
	
}
