#include <gl/glut.h>
#include <math.h>

typedef struct 
{
	float fX;
	float fY;
}strCircle;

#define width 800
#define height 600
#define PI  3.1415926
#define Radius 20


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int iX, int iY);
void TimerFunction(int value);
strCircle Circle[100][100];
int iCount = 0;
float iDelta = 0;
int Vertex = 100;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-8");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);													//점의 사이즈를 조절한다.
	glColor3f(1.0f, 0.0f, 0.0f);
	iDelta = 2.0 * PI / Vertex;

	glBegin(0);
	for (int i = 0; i < iCount; i++)
	{
		for (int j = 0; j < Vertex; j++)
		{
			glVertex2f(Circle[i][j].fX + Radius * cos(iDelta * j),
				Circle[i][j].fY + Radius * sin(iDelta * j));   // x, y 는 중심점
		}
	}
	glEnd();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();           // 변환된 회전이나 좌표의 행렬을 처음 원래대로 설정.
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int iX, int iY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < Vertex; i++)
		{
			Circle[iCount][i].fX = iX;
			Circle[iCount][i].fY = height - iY;
		}
		iCount++;
	}

	glutPostRedisplay();

}

void TimerFunction(int value)
{
	for (int i = 0; i < iCount; i++)
	{
		for (int j = 0; j < Vertex; j++)
		{
			Circle[i][j].fX += Radius * cos(iDelta * j);
			Circle[i][j].fY += Radius * sin(iDelta * j);
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}