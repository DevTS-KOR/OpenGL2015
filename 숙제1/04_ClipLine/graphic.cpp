

#include "stdafx.h"
#include <math.h>

extern BYTE *g_pBits;
extern int g_swidth, g_sheight;
extern int g_scanline;

void PutPixel( int x, int y, int r, int g, int b )
{
  int off = y * g_scanline + x * 3;
  
  g_pBits[ off + 0 ] = b;
  g_pBits[ off + 1 ] = g;
  g_pBits[ off + 2 ] = r;
}



// float을 사용한 선 긋기
void LineDDAFloatingPoint( int x1, int y1, int x2, int y2, int r, int g, int b )
{
	float x, y;			// 임시 변수
	int dx, dy;			// x, y의 차이값
	int x_inc, y_inc;		// x, y의 증감값

	dx = x2 - x1;
	dy = y2 - y1;
	
	// dx가 0보다 크거나 같으면 x증감값은 3
	if(dx>=0)
	{
		x_inc = 3;
	}
	else
	{
		x_inc = -3;
		dx = -dx;
	}

	// dx가 0보다 크거나 같으면 y증감값은 g_scanline
	if(dy>=0)
	{
		y_inc = g_scanline;
	}
	else
	{
		y_inc = -g_scanline;
		dy = -dy;
	}

	// 임시변수 x,y 초기화
	x = (float)x1;
	y = (float)y1;

	// offset값 초기화
	int off = x1 * 3 + (g_scanline * y1);

	// 기울기가 1보다 작은경우는 y값에 기울기를 더하여 점을 찾는다
	if(dx>dy)
	{
		// 기울기 계산
		float m = (float)fabs((float)(y2 - y1) / (x2 - x1 ));
		// dx만큼 루프
		for(int i=0; i<dx; ++i)
		{
			// 점을 찍는다.
			g_pBits[off] = b;
			g_pBits[off+1] = g;
			g_pBits[off+2] = r;

			// x값 증감
			off += x_inc;

			// 기울기를 더한 y값과 1씩 증가한 y1값을 비교하여
			// offset값에 y방향으로 증가할건지 결정
			if(y > (float)y1)
			{
				off += y_inc;
				++y1;
			}
			y += m;
		}
	}
	// 기울기가 1보다 크거나 같을경우는 x값에 기울기를 더하여 점을 찾는다
	else
	{
		float m = (float)fabs((float)(x2 - x1) / (y2 - y1 ));
		for(int i=0; i<dy; ++i)
		{
			g_pBits[off] = b;
			g_pBits[off+1] = g;
			g_pBits[off+2] = r;
			off += y_inc;
			if(x > (float)(x1))
			{
				off += x_inc;
				++x1;
			}
			x += m;
		}
	}
}

// int를 사용한 선긋기
void LineDDAFixedPoint( int x1, int y1, int x2, int y2, int r, int g, int b )
{
	int x, y;
	int dx, dy;
	int x_inc, y_inc;

	dx = x2 - x1;
	dy = y2 - y1;
	
	if(dx>=0)
	{
		x_inc = 3;
	}
	else
	{
		x_inc = -3;
		dx = -dx;
	}

	if(dy>=0)
	{
		y_inc = g_scanline;
	}
	else
	{
		y_inc = -g_scanline;
		dy = -dy;
	}

	
	x = x1<<16;
	y = y1<<16;
	int off = x1 * 3 + (g_scanline * y1);

	if(dx>dy)
	{
		int m = abs(((y2 - y1)<<16) / (x2 - x1));
		for(int i=0; i<dx; ++i)
		{
			g_pBits[off] = b;
			g_pBits[off+1] = g;
			g_pBits[off+2] = r;
			off += x_inc;
			if(y > (y1<<16))
			{
				off += y_inc;
				++y1;
			}
			y += m;
		}
	}
	else
	{
		int m = abs(((x2 - x1)<<16) / (y2 - y1));
		for(int i=0; i<dy; ++i)
		{
			g_pBits[off] = b;
			g_pBits[off+1] = g;
			g_pBits[off+2] = r;
			off += y_inc;
			if(x > (x1<<16))
			{
				off += x_inc;
				++x1;
			}
			x += m;
		}
	}
}




//-------------------새로 추가됨---------------------------
// 직선클리핑
BOOL ClipLine( POINT *p1, POINT *p2)
{
	POINT pTemp1, pTemp2;
	pTemp1.x = p1->x;
	pTemp1.y = p1->y;
	pTemp2.x = p2->x;
	pTemp2.y = p2->y;
	// 영역체크------------------------------------
	// r1:점1에 대한 영역 r2:점2에 대한 영역
	int r1=0, r2=0;
	if(p1->y < 0)
		r1 |= 8;
	if(p1->y > g_sheight - 1)
		r1 |= 4;

	if(p1->x < 0)
		r1 |= 1;
	if(p1->x > g_swidth - 1)
		r1 |= 2;

	if(p2->y < 0)
		r2 |= 8;
	if(p2->y > g_sheight - 1)
		r2 |= 4;

	if(p2->x < 0)
		r2 |= 1;
	if(p2->x > g_swidth - 1)
		r2 |= 2;
	//--------------------------------------------

	// r1 | r2 가 0 이면 영역 안 -> 기존 선긋기 사용
	if(!(r1 || r2)) return TRUE;

	// r1 & r2 가 0이 아니면 그리지 않음
	if(r1 & r2) 
		return FALSE;

	switch(r1)
	{
	case 0:
		break;
	case 1:
		pTemp1.x = 0;
		pTemp1.y = p1->y + (LONG)((float)(-p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		break;
	case 2:
		pTemp1.x = g_swidth - 1;
		pTemp1.y = p1->y + (LONG)((float)(pTemp1.x - p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		break;
	case 4:
		pTemp1.y = g_sheight - 1;
		pTemp1.x = p1->x + (LONG)((float)(pTemp1.y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		break;
	case 5:
		pTemp1.y = g_sheight - 1;
		pTemp1.x = p1->x + (LONG)((float)(pTemp1.y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		if(pTemp1.x < 0)
		{
			pTemp1.x = 0;
			pTemp1.y = p1->y + (LONG)((float)(-p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		}
		break;
	case 6:
		pTemp1.y = g_sheight - 1;
		pTemp1.x = p1->x + (LONG)((float)(pTemp1.y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		if(pTemp1.x > g_swidth - 1)
		{
			pTemp1.x = g_swidth - 1;
			pTemp1.y = p1->y + (LONG)((float)(pTemp1.x - p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		}
		break;
	case 8:
		pTemp1.y = 0;
		pTemp1.x = p1->x + (LONG)((float)(-p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		break;
	case 9:
		pTemp1.y = 0;
		pTemp1.x = p1->x + (LONG)((float)(-p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		if(pTemp1.x < 0)
		{
			pTemp1.x = 0;
			pTemp1.y = p1->y + (LONG)((float)(-p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		}
		break;
	case 10:
		pTemp1.y = 0;
		pTemp1.x = p1->x + (LONG)((float)(-p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + 0.5f);
		if(pTemp1.x > g_swidth - 1)
		{
			pTemp1.x = g_swidth - 1;
			pTemp1.y = p1->y + (LONG)((float)(pTemp1.x - p1->x) * (p2->y - p1->y) / (p2->x - p1->x) + 0.5f);
		}
		break;
	}
	
	switch(r2)
	{
	case 0:
		break;
	case 1:
		pTemp2.x = 0;
		pTemp2.y = p2->y + (LONG)((float)(-p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		break;
	case 2:
		pTemp2.x = g_swidth - 1;
		pTemp2.y = p2->y + (LONG)((float)(pTemp2.x - p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		break;
	case 4:
		pTemp2.y = g_sheight - 1;
		pTemp2.x = p2->x + (LONG)((float)(pTemp2.y - p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		break;
	case 5:
		pTemp2.y = g_sheight - 1;
		pTemp2.x = p2->x + (LONG)((float)(pTemp2.y - p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		if(pTemp2.x < 0)
		{
			pTemp2.x = 0;
			pTemp2.y = p2->y + (LONG)((float)(-p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		}
		break;
	case 6:
		pTemp2.y = g_sheight - 1;
		pTemp2.x = p2->x + (LONG)((float)(pTemp2.y - p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		if(pTemp2.x > g_swidth - 1)
		{
			pTemp2.x = g_swidth - 1;
			pTemp2.y = p2->y + (LONG)((float)(pTemp2.x - p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		}
		break;
	case 8:
		pTemp2.y = 0;
		pTemp2.x = p2->x + (LONG)((float)(-p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		break;
	case 9:
		pTemp2.y = 0;
		pTemp2.x = p2->x + (LONG)((float)(-p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		if(pTemp2.x < 0)
		{
			pTemp2.x = 0;
			pTemp2.y = p2->y + (LONG)((float)(-p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		}
		break;
	case 10:
		pTemp2.y = 0;
		pTemp2.x = p2->x + (LONG)((float)(-p2->y) * (p1->x - p2->x) / (p1->y - p2->y) + 0.5f );
		if(pTemp2.x > g_swidth - 1) 
		{
			pTemp2.x = g_swidth - 1;
			pTemp2.y = p2->y + (LONG)((float)(pTemp2.x - p2->x) * (p1->y - p2->y) / (p1->x - p2->x) + 0.5f );
		}
		break;
	}

	if( pTemp1.x<0 || pTemp1.x >=g_swidth || pTemp1.y <0 || pTemp1.y >= g_sheight ||
		pTemp2.x<0 || pTemp2.x>=g_swidth || pTemp2.y<0 || pTemp2.y >= g_sheight )return FALSE;

	p1->x = pTemp1.x;
	p1->y = pTemp1.y;
	p2->x = pTemp2.x;
	p2->y = pTemp2.y;
	return TRUE;
}
//-------------------------------------------------------------
