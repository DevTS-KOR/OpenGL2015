// �� �ҽ��� ������
/******************************************************
	g-Matrix3D Engine
	Copyright (c)2000 Kim Seong Wan (kaswan, �𻧱ͽ�)
	
	E-mail: kaswan@hitel.net
	http://www.hitel.net/~kaswan

*******************************************************/

// ����� �ּ� �Է� - �ѹ���

#ifndef SOFTWARE_H
#define SOFTWARE_H


extern BOOL bIsActive;					// DIB ������ ����� �� �ִ���
extern BOOL bIsDIB;

extern HDC hScreenDC, hMemoryDC;		// ��ũ��DC, �޸�DC

BOOL SetupSoftware(HWND hWnd);			// ����Ʈ������� �ʱ�ȭ
BOOL CloseSoftware(HWND hWnd);			// ����Ʈ������� ����

void UpdateFrame(void);					// ȭ�� ����


#endif