#pragma once
#include "stdafx.h"
#include "Common.h"

class CGameObject
{
protected:
	Vec3		m_tPosition;
	ColorAlpha	m_tColor;

public:
	CGameObject();
	~CGameObject();
};

