#include "stdafx.h"

// 스크린DC, 메모리DC
// 스크린DC와 메모리 DC를 따로 두어 사용하는 이유는
// 그냥 화면(스크린DC)에 바로 렌더링 할수도 있지만
// 화면에 렌더링하는것은 속도가 느리기때문에
// 스크린과 똑같은 크기의 메모리공간에 렌더링하고
// 메모리에 렌더링이 종료되면 한꺼번에 화면으로 고속복사를 하면 빠르다..
HDC hScreenDC, hMemoryDC;

// 메모리DC와 연결할 비트맵 핸들
HBITMAP hBM;
// 이전의 비트맵 핸들
HBITMAP hDefaultBitmap;

// 메모리비트맵의 첫번째 주소(헤더,정보부분을 뺀 비트맵데이터 부분)를 가리키기위한 포인터
BYTE *g_pBits;

// 비트맵의 가로, 세로
int g_swidth, g_sheight;
// 비트맵의 가로 길이(바이트)
int g_scanline;

// DIB섹션이 만들어 져있는지.. 초기값FALSE
BOOL g_bIsActive = FALSE;

// DIB생성, 초기화
BOOL SetupSoftware(HWND hWnd);
// DIB종료
BOOL CloseSoftware(HWND hWnd);

// 화면 갱신
void UpdateFrame();

// DIB생성
HBITMAP MakeDIBSection(HDC hDC, int width, int height, BYTE **pBits);

BOOL SetupSoftware(HWND hWnd)
{
	// 화면DC를 얻어옴
	hScreenDC = GetDC(hWnd);
	// 화면DC의 복사판을 얻어옴
	hMemoryDC = CreateCompatibleDC(hScreenDC);
	// DIB생성후 비트맵핸들 저장
	hBM = MakeDIBSection(hScreenDC, 640, 480, &g_pBits);

	// 현재는 hBM을 쓰기로 하고 이전 HBITMAP을 저장해놓음
	hDefaultBitmap = (HBITMAP)SelectObject(hMemoryDC, hBM);

	// 타이머 초기화
	InitTimer();

	// DIB섹션 만들어 졌음
	g_bIsActive = TRUE;

	return TRUE;
}

BOOL CloseSoftware(HWND hWnd)
{
	// 이전 HBITMAP을 선택
	SelectObject(hMemoryDC, hDefaultBitmap);
	// MemDC해제
	DeleteDC(hMemoryDC);
	// HBITMAP해제
	DeleteObject(hDefaultBitmap);
	DeleteObject(hBM);
	// 스크린DC를 놓아 줌
	ReleaseDC(hWnd, hScreenDC);
		
	return TRUE;
}

// 화면 갱신
void UpdateFrame()
{
	
	//--------------------------------------------------------
	
	memset( g_pBits, 0, sizeof( g_swidth * g_sheight * 3 ) );
	
	//-------------------새로 추가됨---------------------------
	POINT p1, p2;
	p1.x = -100;
	p1.y = -200;
	p2.x = 600;
	p2.y = 300;

	if( ClipLine( &p1, &p2 ) )
	{
		LineDDAFixedPoint( p1.x, p1.y, p2.x, p2.y, 255, 255, 255 );
	}
	
	p1.x = 300;
	p1.y = 500;
	p2.x = 700;
	p2.y = 200;

	if( ClipLine( &p1, &p2 ) )
	{
		LineDDAFixedPoint( p1.x, p1.y, p2.x, p2.y, 255, 255, 255 );
	}
	//---------------------------------------------------------


	
	char szText[128];
	//프레임 체크
	FrameCheck();
	sprintf(szText, "FPS : %f", g_fFPS);
	// 현재 프레임 출력
	TextOut(hMemoryDC, 0, 0, szText, strlen(szText));

	// 메모리DC의 비트맵을 화면에 고속복사
	BitBlt(hScreenDC, 0, 0, 640, 480, hMemoryDC, 0, 0, SRCCOPY);
}

// DIB섹션 생성
HBITMAP MakeDIBSection(HDC hDC, int width, int height, BYTE **pBits)
{
	// 24비트 비트맵을 생성
	HBITMAP hDIBitmap;
	BITMAPINFO BMInfo;

	BMInfo.bmiHeader.biSize				= sizeof (BITMAPINFOHEADER);
	BMInfo.bmiHeader.biWidth			= width;
	BMInfo.bmiHeader.biHeight			= -height;
	BMInfo.bmiHeader.biPlanes			= 1;
	BMInfo.bmiHeader.biBitCount			= 24;
	BMInfo.bmiHeader.biCompression		= BI_RGB;
	BMInfo.bmiHeader.biSizeImage		= 0;
	BMInfo.bmiHeader.biXPelsPerMeter	= 0;
	BMInfo.bmiHeader.biYPelsPerMeter	= 0;
	BMInfo.bmiHeader.biClrUsed			= 0;
	BMInfo.bmiHeader.biClrImportant		= 0;

	// DIB섹션을 생성
	hDIBitmap = CreateDIBSection (hDC, (BITMAPINFO *)&BMInfo, DIB_RGB_COLORS, (VOID **)pBits, NULL, 0);

	// g_scanline 은 4의 배수로 함.. <- 속도가 빠름
	g_scanline = (width * 3 + 3)/4 * 4;
	g_swidth = width;
	g_sheight = height;
	
	return (hDIBitmap);
}


