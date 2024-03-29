#include "pch.h"
#include "CEntity.h"

// ±¸Çö
UINT CEntity::g_NextID = 0;


CEntity::CEntity()
	: m_ID(g_NextID++)
{
}

CEntity::CEntity(const CEntity& _Other)
	: m_ID(g_NextID++)
	, m_strName(_Other.m_strName)
{
}

CEntity::~CEntity()
{	
}
