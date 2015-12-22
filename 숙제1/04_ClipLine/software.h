// 이 소스의 제작자
/******************************************************
	g-Matrix3D Engine
	Copyright (c)2000 Kim Seong Wan (kaswan, 찐빵귀신)
	
	E-mail: kaswan@hitel.net
	http://www.hitel.net/~kaswan

*******************************************************/

// 잡다한 주석 입력 - 한범석

#ifndef SOFTWARE_H
#define SOFTWARE_H


extern BOOL bIsActive;					// DIB 섹션이 만들어 져 있는지
extern BOOL bIsDIB;

extern HDC hScreenDC, hMemoryDC;		// 스크린DC, 메모리DC

BOOL SetupSoftware(HWND hWnd);			// 소프트웨어렌더러 초기화
BOOL CloseSoftware(HWND hWnd);			// 소프트웨어렌더러 종료

void UpdateFrame(void);					// 화면 갱신


#endif