// CG_TermProject_Together_Tang_x3.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "MainGame.h"
CMainGame	MainGame;
int		g_iWindow_Width = 0;
int		g_iWindow_Height = 0;
//extern	int g_iWindow_Width;
//extern	int g_iWindow_Height;

GLvoid	Initialize();
GLvoid MenuInit();
GLvoid	LightInit();
GLvoid	drawScene(GLvoid);
GLvoid	Reshape(int w, int h);
GLvoid	Keyboard(unsigned char key, int x, int y);
GLvoid	KeyboardUp(unsigned char key, int x, int y);
GLvoid	SpecialKeyboardUp(int key, int x, int y);
GLvoid	SpecialKeyboard(int key, int x, int y);
GLvoid	TimerFunc(int value);
GLvoid	Mouse(int button, int state, int x, int y);
GLvoid	MotionFunc(int x, int y);
GLvoid		MenuFunc(int button);
int _tmain(int argc, _TCHAR* argv[])
{
	srand(unsigned int(time(NULL)));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 800); // �������� ũ�� ���� 
	glutCreateWindow("���Բ� ������"); // ������ ���� (������ �̸�) 
	Initialize();
	glutDisplayFunc(drawScene);// ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(MotionFunc);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
	MainGame.~CMainGame();
}

GLvoid Initialize()
{
	MainGame.Initialize();
	MenuInit();
}

GLvoid LightInit()
{

}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MainGame.Render();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	g_iWindow_Width = w;
	g_iWindow_Height = h;

	glLoadIdentity();
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	MainGame.Keyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	MainGame.SpecialKeyboard(key, x, y);
	glutPostRedisplay();
}
GLvoid SpecialKeyboardUp(int key, int x, int y)
{

	MainGame.SpecialKeyboardUp(key, x, y);
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	MainGame.Update(value);
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);

}

GLvoid Mouse(int button, int state, int x, int y)
{
	MainGame.Mouse(button, state, x, y);
	glutPostRedisplay();
}

GLvoid MotionFunc(int x, int y)
{
	MainGame.MouseMotionFunc(x, y);
	glutPostRedisplay();
}

GLvoid MenuFunc(int button)
{
	switch (button)
	{
	case 11:

		exit(0);
		break;
	}
}

GLvoid MenuInit()
{

	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("����", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	MainGame.KeyboardUp(key, x, y);
	glutPostRedisplay();
}
