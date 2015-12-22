#pragma once
//#include "stdafx.h"

// Pie��
#define PI	3.141592

// �������� �ʺ�, ����
#define WINDOW_WIDTH	800
#define	WINDOW_HEIGHT	800

// �ؽ��ĸ� �޾ƿö� Scene�����ؼ�
// �迭�� �ε����� ����ֱ�����
// ex) GetTexture(DRAW_LOGO)
#define DRAW_LOGO	0
#define DRAW_LOBBY	1

// �����Ҵ�� ������ �����ϱ� ���� ���ø�
template<typename T>
static void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

// X, Y, Z��ǥ�� �����ϴ� ����ü
// ���� float���� ��������� ������ ����
struct Vec3
{
	float fX;
	float fY;
	float fZ;
};

// X, Y��ǥ�� �����ϴ� ����ü
// ���� float���� ��������� ������ ����
struct Vec2
{
	float fX;
	float fY;
};

// �� �� �� 3���� ������� ����ü ���İ��� ����
struct Color
{
	int iRed;
	int iGreen;
	int iBlue;
};

// �� �� �� 3���� ������� ����ü ���İ� ����
struct ColorAlpha
{
	int iRed;
	int iGreen;
	int iBlue;
	int	iAlpha;
};

// Scene��ȯ�� ���� enum����
enum SceneList
{
	SCENE_LOGO,
	SCENE_LOBBY,
	SCENE_INGAME,
	SCENE_NONE
};

