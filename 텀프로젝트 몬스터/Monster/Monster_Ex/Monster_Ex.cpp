// Monster_Ex.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Monster.h"

GLvoid	drawScene(GLvoid);
GLvoid	Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
Monster m_Monster;

float fRotate_X = 0.f;
float fRotate_Y = 0.f;

int _tmain(int argc, _TCHAR* argv[])
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 800); // �������� ũ�� ���� 
	glutCreateWindow("���Բ� ������"); // ������ ���� (������ �̸�) 
	//m_Monster.SetupRC();
	glutDisplayFunc(drawScene);// ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	//�ؽ�ó �Ķ���� ���� --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);

	glRotatef(fRotate_X, 1, 0, 0);
	glRotatef(fRotate_Y, 0, 1, 0);

	glPushMatrix();
	m_Monster.draw();
	glPopMatrix();
	//glFlush();
	glutSwapBuffers();		//��� ���
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'y')
		fRotate_Y += 10.f;
	else if (key == 'Y')
		fRotate_Y -= 10.f;
	else if (key == 'x')
		fRotate_X -= 10.f;
	else if (key == 'X')
		fRotate_X += 10.f;

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (m_Monster.fZ_left_arm >= 70.f)
	{
		m_Monster.fArm_move *= -1;
		m_Monster.fLeg_move *= -1;
	}

	else if (m_Monster.fZ_left_arm <= -70.f)
	{
		m_Monster.fArm_move *= -1;
		m_Monster.fLeg_move *= -1;
	}

	m_Monster.fZ_left_arm += m_Monster.fArm_move;
	m_Monster.fZ_right_arm -= m_Monster.fArm_move;
	m_Monster.fZ_left_leg -= m_Monster.fLeg_move;
	m_Monster.fZ_right_leg += m_Monster.fLeg_move;

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}


