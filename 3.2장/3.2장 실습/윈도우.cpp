#include <gl/glut.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main()
{
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("������");
	glutDisplayFunc(drawScene);		//��� �Լ� ����
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);				//�̵�, ȸ��, ������ �����̴�.(������ ��� ��带 ����)
	//glLoadIdentity();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);		//�߾��� ��������
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);		//�������� ��������
}
