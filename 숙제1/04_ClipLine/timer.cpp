#include "stdafx.h"


LARGE_INTEGER g_iStart, g_iEnd, g_iFrequency;
float g_fTimer;
float g_fFPS;


void InitTimer()
{
	g_fTimer = 0.0f;
	g_fFPS = 0.0f;
	// 시스템 주파수를 알아온다
	QueryPerformanceFrequency(&g_iFrequency);
}

void FrameCheck()
{
	QueryPerformanceCounter(&g_iEnd);
	g_fTimer = (g_iEnd.LowPart - g_iStart.LowPart) / (float)g_iFrequency.LowPart;
	g_fFPS = 1 / g_fTimer;
	g_iStart = g_iEnd;
}

