#include "stdafx.h"


// Windows Globals
HWND hWnd;					// 윈도우 핸들
HINSTANCE hThisInst;		// 윈도우 인스턴스

// Function Prototypes
// 윈도우클래스 등록
BOOL RegisterWindowClass(HINSTANCE hInstance);

// 윈도우 생성
BOOL MakeWindow(char *title, HINSTANCE hInstance, int nCmdShow);

// 윈도우 생성, DIB섹션 생성
BOOL CreateDIBWindow(HINSTANCE hInstance, int nCmdShow);

// 윈도우 종료
BOOL CloseDIBWindow(HWND hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, // handle to current instance 
					HINSTANCE hPrevInstance, // handle to previous instance 
					LPSTR lpCmdLine, // pointer to command line 
					int nCmdShow) // show state of window 
{
	// 윈도우 메시지
    MSG msg;
	
	// 윈도우를 생성하고 DIB섹션을 생성한다
	CreateDIBWindow(hInstance, nCmdShow);
	
	// 인스턴스 저장
	hThisInst = hInstance;

	// message loop for game application
    while( 1 )
    {
		// PeekMessage();  란.
		// 일반적으로 윈API프로그래밍은 GetMessage를 이용하여 무한 루프를 돌리는데 
		// GetMessage는 메시지가 들어 올때까지 무한정 기다리는 함수이므로
		// 게임에서는 사용할 수가 없다..(메시지가 들어오지 않더라도 화면갱신이 되어야 하므로..)
		// PeekMessage()에서 메시지가 들어오면 TRUE를 반환하여 메시지를 처리하고
		// 메시지가 들어오지 않았으면 FALSE를 반환 하여 화면 갱신을 해줄 수 있다.
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( !GetMessage( &msg, NULL, 0, 0 ) )
            {
				break;
            }
            else
			{
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
		// DIB섹션이 만들어 졌으면 화면갱신
        else if ( g_bIsActive )
        {
			UpdateFrame();
        }
        else
        {
			// 메시지 기다림
            WaitMessage();
        }
    }

	///////////////////////////////////////////////
	///
	// DIB윈도우 종료
	CloseDIBWindow(hWnd);

	// 윈도우 파괴
    DestroyWindow(hWnd);

	return msg.wParam;

}

// 윈도우 등록
BOOL RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASS wc;

    wc.style            = CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc      = WindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, NULL);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "GM2D Class";

    if (!RegisterClass(&wc)) return FALSE;

	return TRUE;
}

// 윈도우 생성
BOOL MakeWindow(char *title, HINSTANCE hInstance, int nCmdShow)
{
	// 윈도우 크기는 640X480
    RECT rect = {0, 0, 639, 479};

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	// 가로 = 640, 세로 = 480
	int width = rect.right - rect.left + 1;
	int height = rect.bottom - rect.top + 1;
	
	// 윈도우 생성
	hWnd = CreateWindowEx(NULL,
                          "GM2D Class",
                          title,
                          WS_OVERLAPPEDWINDOW,
                          (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
                          (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
                          640,
                          480,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

	// 생성 실패면 FALSE리턴
    if (!hWnd) return FALSE;

	// 윈도우 보여주고 업데이트
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	return TRUE;
}

BOOL CreateDIBWindow(HINSTANCE hInstance, int nCmdShow)
{
	// 윈도우 등록
	if (!RegisterWindowClass(hInstance))
		return FALSE;

	// 윈도우 생성
    if (!MakeWindow("Lecture", hInstance, nCmdShow))
        return FALSE;
	
	// DIB섹션 생성, 초기화..
	SetupSoftware(hWnd);
	
	return TRUE;
}

BOOL CloseDIBWindow(HWND hWnd)
{
	// DIB섹션 종료
	CloseSoftware(hWnd);
	return TRUE;
}

// 윈도우 프로시저
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int mouse_x, mouse_y;
	static int mouse_sx, mouse_sy;
	static BOOL LButton = FALSE;
    
	switch(message)
    {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	    case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		
		case WM_KEYDOWN:
			{
				switch(wParam)
				{
					case VK_UP:
						return 0;

					case VK_DOWN:
						return 0;

					case VK_RIGHT:
						return 0;

					case VK_LEFT:
						return 0;

					case VK_ESCAPE:
						PostMessage(hWnd, WM_CLOSE, 0, 0);
						return 0;
				}
			}
			break;

		case WM_LBUTTONUP:
			LButton = FALSE;
			ReleaseCapture();
			return 0;
		
		case WM_LBUTTONDOWN:
			LButton = TRUE;
			SetCapture(hWnd);
			
			mouse_sx = (short)LOWORD(lParam);
			mouse_sy = (short)HIWORD(lParam);

			return 0;
		
		case WM_MOUSEMOVE:
			if ( LButton == TRUE )
			{
				mouse_x = (short)LOWORD(lParam);
				mouse_y = (short)HIWORD(lParam);
				
			}
			return 0;
    }

	return DefWindowProc(hWnd, message, wParam, lParam);
}



