#include <gl/glut.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);


float fX = 0.0f;
float fY = 0.0f;
bool Clrick = false;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-29");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);				//이동, 회전, 신축을 위함이다.(현재의 행렬 모드를 설정)
	//glLoadIdentity();

	
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
	cout << fX << ", " << fY << endl;
	glVertex3f(fX, fY, 0.0f);
	glEnd();
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);		//중앙을 원점으로
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);		//좌측밑을 원점으로
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		fX = x;
		fY = -y + 600;
	}

	glutPostRedisplay();

}