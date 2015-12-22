#include "stdafx.h"


// Windows Globals
HWND hWnd;					// ������ �ڵ�
HINSTANCE hThisInst;		// ������ �ν��Ͻ�

// Function Prototypes
// ������Ŭ���� ���
BOOL RegisterWindowClass(HINSTANCE hInstance);

// ������ ����
BOOL MakeWindow(char *title, HINSTANCE hInstance, int nCmdShow);

// ������ ����, DIB���� ����
BOOL CreateDIBWindow(HINSTANCE hInstance, int nCmdShow);

// ������ ����
BOOL CloseDIBWindow(HWND hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, // handle to current instance 
					HINSTANCE hPrevInstance, // handle to previous instance 
					LPSTR lpCmdLine, // pointer to command line 
					int nCmdShow) // show state of window 
{
	// ������ �޽���
    MSG msg;
	
	// �����츦 �����ϰ� DIB������ �����Ѵ�
	CreateDIBWindow(hInstance, nCmdShow);
	
	// �ν��Ͻ� ����
	hThisInst = hInstance;

	// message loop for game application
    while( 1 )
    {
		// PeekMessage();  ��.
		// �Ϲ������� ��API���α׷����� GetMessage�� �̿��Ͽ� ���� ������ �����µ� 
		// GetMessage�� �޽����� ��� �ö����� ������ ��ٸ��� �Լ��̹Ƿ�
		// ���ӿ����� ����� ���� ����..(�޽����� ������ �ʴ��� ȭ�鰻���� �Ǿ�� �ϹǷ�..)
		// PeekMessage()���� �޽����� ������ TRUE�� ��ȯ�Ͽ� �޽����� ó���ϰ�
		// �޽����� ������ �ʾ����� FALSE�� ��ȯ �Ͽ� ȭ�� ������ ���� �� �ִ�.
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
		// DIB������ ����� ������ ȭ�鰻��
        else if ( g_bIsActive )
        {
			UpdateFrame();
        }
        else
        {
			// �޽��� ��ٸ�
            WaitMessage();
        }
    }

	///////////////////////////////////////////////
	///
	// DIB������ ����
	CloseDIBWindow(hWnd);

	// ������ �ı�
    DestroyWindow(hWnd);

	return msg.wParam;

}

// ������ ���
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

// ������ ����
BOOL MakeWindow(char *title, HINSTANCE hInstance, int nCmdShow)
{
	// ������ ũ��� 640X480
    RECT rect = {0, 0, 639, 479};

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	// ���� = 640, ���� = 480
	int width = rect.right - rect.left + 1;
	int height = rect.bottom - rect.top + 1;
	
	// ������ ����
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

	// ���� ���и� FALSE����
    if (!hWnd) return FALSE;

	// ������ �����ְ� ������Ʈ
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	return TRUE;
}

BOOL CreateDIBWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ������ ���
	if (!RegisterWindowClass(hInstance))
		return FALSE;

	// ������ ����
    if (!MakeWindow("Lecture", hInstance, nCmdShow))
        return FALSE;
	
	// DIB���� ����, �ʱ�ȭ..
	SetupSoftware(hWnd);
	
	return TRUE;
}

BOOL CloseDIBWindow(HWND hWnd)
{
	// DIB���� ����
	CloseSoftware(hWnd);
	return TRUE;
}

// ������ ���ν���
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



