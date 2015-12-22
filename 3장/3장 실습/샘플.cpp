#include <gl/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main()
{
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("����");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);		//�������� ũ�Ⱑ ���Ҷ� ���� ��������
	glutMainLoop();
}

//������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);		//�׸��� �� ����
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);		//�簢�� �׸���
	glFlush();								//ȭ�鿡 ���
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}