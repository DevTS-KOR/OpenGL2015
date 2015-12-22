

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



// float�� ����� �� �߱�
void LineDDAFloatingPoint( int x1, int y1, int x2, int y2, int r, int g, int b )
{
	float x, y;			// �ӽ� ����
	int dx, dy;			// x, y�� ���̰�
	int x_inc, y_inc;		// x, y�� ������

	dx = x2 - x1;
	dy = y2 - y1;
	
	// dx�� 0���� ũ�ų� ������ x�������� 3
	if(dx>=0)
	{
		x_inc = 3;
	}
	else
	{
		x_inc = -3;
		dx = -dx;
	}

	// dx�� 0���� ũ�ų� ������ y�������� g_scanline
	if(dy>=0)
	{
		y_inc = g_scanline;
	}
	else
	{
		y_inc = -g_scanline;
		dy = -dy;
	}

	// �ӽú��� x,y �ʱ�ȭ
	x = (float)x1;
	y = (float)y1;

	// offset�� �ʱ�ȭ
	int off = x1 * 3 + (g_scanline * y1);

	// ���Ⱑ 1���� �������� y���� ���⸦ ���Ͽ� ���� ã�´�
	if(dx>dy)
	{
		// ���� ���
		float m = (float)fabs((float)(y2 - y1) / (x2 - x1 ));
		// dx��ŭ ����
		for(int i=0; i<dx; ++i)
		{
			// ���� ��´�.
			g_pBits[off] = b;
			g_pBits[off+1] = g;
			g_pBits[off+2] = r;

			// x�� ����
			off += x_inc;

			// ���⸦ ���� y���� 1�� ������ y1���� ���Ͽ�
			// offset���� y�������� �����Ұ��� ����
			if(y > (float)y1)
			{
				off += y_inc;
				++y1;
			}
			y += m;
		}
	}
	// ���Ⱑ 1���� ũ�ų� �������� x���� ���⸦ ���Ͽ� ���� ã�´�
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

// int�� ����� ���߱�
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




//-------------------���� �߰���---------------------------
// ����Ŭ����
BOOL ClipLine( POINT *p1, POINT *p2)
{
	POINT pTemp1, pTemp2;
	pTemp1.x = p1->x;
	pTemp1.y = p1->y;
	pTemp2.x = p2->x;
	pTemp2.y = p2->y;
	// ����üũ------------------------------------
	// r1:��1�� ���� ���� r2:��2�� ���� ����
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

	// r1 | r2 �� 0 �̸� ���� �� -> ���� ���߱� ���
	if(!(r1 || r2)) return TRUE;

	// r1 & r2 �� 0�� �ƴϸ� �׸��� ����
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
