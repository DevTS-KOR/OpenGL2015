#ifndef GRAPHIC_H
#define GRAPHIC_H

// ȭ�鿡 �� ���
void PutPixel(int x, int y, int r, int g, int b);

// ���߱�(�ε��Ҽ����̿�)
void LineDDAFloatingPoint( int x1, int y1, int x2, int y2, int r, int g, int b );
// ���߱�(�����Ҽ����̿�)
void LineDDAFixedPoint( int x1, int y1, int x2, int y2, int r, int g, int b );


//-------------------���� �߰���---------------------------
BOOL ClipLine( POINT *p1, POINT *p2);
//--------------------------------------------------------
#endif