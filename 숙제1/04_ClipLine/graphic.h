#ifndef GRAPHIC_H
#define GRAPHIC_H

// 화면에 점 찍기
void PutPixel(int x, int y, int r, int g, int b);

// 선긋기(부동소수점이용)
void LineDDAFloatingPoint( int x1, int y1, int x2, int y2, int r, int g, int b );
// 선긋기(고정소수점이용)
void LineDDAFixedPoint( int x1, int y1, int x2, int y2, int r, int g, int b );


//-------------------새로 추가됨---------------------------
BOOL ClipLine( POINT *p1, POINT *p2);
//--------------------------------------------------------
#endif