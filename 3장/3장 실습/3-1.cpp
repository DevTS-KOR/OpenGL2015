#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("�ǽ�1");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	//float fRandom[4];

	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 3; ++i)
	//	fRandom[i] = rand() % 2;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//������ ����������
	glClear(GL_COLOR_BUFFER_BIT);			//������ ������ ��ü�� ĥ�ϱ�
	
	//���� �����ϰ� �簢�� �׸���

	//glColor3f(fRandom[0], fRandom[1], fRandom[2]);
	glColor3f(1.0f, 1.0f, 1.0f);			//�߾� �簢��
	glRectf(-0.3f, -0.3f, 0.3f, 0.3f);

	glColor3f(0.0f, 1.0f, 1.0f);			//�»� �簢
	glRectf(-1.0f, 1.0f, -0.4f, 0.4f);

	glColor3f(0.0f, 1.0f, 0.0f);			//��� �簢��
	glRectf(0.4f, 1.0f, 1.0f, 0.4f);

	glColor3f(1.0f, 0.0f, 0.0f);			//���� �簢��
	glRectf(-1.0f, -0.4f, -0.4f, -1.0f);

	glColor3f(1.0f, 1.0f, 0.0f);			//���� �簢��
	glRectf(0.4f, -0.4f, 1.0f, -1.0f);

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}