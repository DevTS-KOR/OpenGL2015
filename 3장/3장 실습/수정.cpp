#include <GL/glut.h> // includes gl.h glu.h
#include <stdlib.h>	//�ߺ����� ������ ���� ���1
#include <time.h>	//�ߺ����� ������ ���� ���2

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

struct point{
	int x;
	int y;
};

point p[10];
int btt = 0;
int click = 0;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));		//�ð����� ������ �ٸ��� �ؼ� �ߺ��� ����
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse); // ���콺 �ݹ��Լ�
	glutTimerFunc(1000, Timerfunction, 1);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'White' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (int i = 0; i < 10; i++)
	{
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'red' ���� ����
		glRectf(p[i].x, p[i].y, p[i].x + 40, p[i].y - 40); // �簢�� �׸���
	}
	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Timerfunction(int value)
{
	p[btt].x = rand() % 760 + 40;
	p[btt].y = rand() % 560 + 40;
	btt++;

	glutPostRedisplay();
	glutTimerFunc(1000, Timerfunction, 1);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		click = 1;
	}
}

void init()
{
	for (int i = 0; i < 10; i++)
	{
		p[i].x = 1000;
	}
}