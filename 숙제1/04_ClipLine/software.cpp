#include "stdafx.h"

// ��ũ��DC, �޸�DC
// ��ũ��DC�� �޸� DC�� ���� �ξ� ����ϴ� ������
// �׳� ȭ��(��ũ��DC)�� �ٷ� ������ �Ҽ��� ������
// ȭ�鿡 �������ϴ°��� �ӵ��� �����⶧����
// ��ũ���� �Ȱ��� ũ���� �޸𸮰����� �������ϰ�
// �޸𸮿� �������� ����Ǹ� �Ѳ����� ȭ������ ��Ӻ��縦 �ϸ� ������..
HDC hScreenDC, hMemoryDC;

// �޸�DC�� ������ ��Ʈ�� �ڵ�
HBITMAP hBM;
// ������ ��Ʈ�� �ڵ�
HBITMAP hDefaultBitmap;

// �޸𸮺�Ʈ���� ù��° �ּ�(���,�����κ��� �� ��Ʈ�ʵ����� �κ�)�� ����Ű������ ������
BYTE *g_pBits;

// ��Ʈ���� ����, ����
int g_swidth, g_sheight;
// ��Ʈ���� ���� ����(����Ʈ)
int g_scanline;

// DIB������ ����� ���ִ���.. �ʱⰪFALSE
BOOL g_bIsActive = FALSE;

// DIB����, �ʱ�ȭ
BOOL SetupSoftware(HWND hWnd);
// DIB����
BOOL CloseSoftware(HWND hWnd);

// ȭ�� ����
void UpdateFrame();

// DIB����
HBITMAP MakeDIBSection(HDC hDC, int width, int height, BYTE **pBits);

BOOL SetupSoftware(HWND hWnd)
{
	// ȭ��DC�� ����
	hScreenDC = GetDC(hWnd);
	// ȭ��DC�� �������� ����
	hMemoryDC = CreateCompatibleDC(hScreenDC);
	// DIB������ ��Ʈ���ڵ� ����
	hBM = MakeDIBSection(hScreenDC, 640, 480, &g_pBits);

	// ����� hBM�� ����� �ϰ� ���� HBITMAP�� �����س���
	hDefaultBitmap = (HBITMAP)SelectObject(hMemoryDC, hBM);

	// Ÿ�̸� �ʱ�ȭ
	InitTimer();

	// DIB���� ����� ����
	g_bIsActive = TRUE;

	return TRUE;
}

BOOL CloseSoftware(HWND hWnd)
{
	// ���� HBITMAP�� ����
	SelectObject(hMemoryDC, hDefaultBitmap);
	// MemDC����
	DeleteDC(hMemoryDC);
	// HBITMAP����
	DeleteObject(hDefaultBitmap);
	DeleteObject(hBM);
	// ��ũ��DC�� ���� ��
	ReleaseDC(hWnd, hScreenDC);
		
	return TRUE;
}

// ȭ�� ����
void UpdateFrame()
{
	
	//--------------------------------------------------------
	
	memset( g_pBits, 0, sizeof( g_swidth * g_sheight * 3 ) );
	
	//-------------------���� �߰���---------------------------
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
	//������ üũ
	FrameCheck();
	sprintf(szText, "FPS : %f", g_fFPS);
	// ���� ������ ���
	TextOut(hMemoryDC, 0, 0, szText, strlen(szText));

	// �޸�DC�� ��Ʈ���� ȭ�鿡 ��Ӻ���
	BitBlt(hScreenDC, 0, 0, 640, 480, hMemoryDC, 0, 0, SRCCOPY);
}

// DIB���� ����
HBITMAP MakeDIBSection(HDC hDC, int width, int height, BYTE **pBits)
{
	// 24��Ʈ ��Ʈ���� ����
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

	// DIB������ ����
	hDIBitmap = CreateDIBSection (hDC, (BITMAPINFO *)&BMInfo, DIB_RGB_COLORS, (VOID **)pBits, NULL, 0);

	// g_scanline �� 4�� ����� ��.. <- �ӵ��� ����
	g_scanline = (width * 3 + 3)/4 * 4;
	g_swidth = width;
	g_sheight = height;
	
	return (hDIBitmap);
}


