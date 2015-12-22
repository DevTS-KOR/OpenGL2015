#include <gl/glut.h>
#include <math.h>

#define PI 3.141592

typedef struct 
{
	float fX;
	float fY;
}RectInfo;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
RectInfo Info[100][400];
int iCount = 0;
int iTimer_Count = 1;
int iVertex = 0;
float fDistance = 10.f;
float fRadius = 0.f;
float iDelta = 0.f;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-9");

	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);													//점의 사이즈를 조절한다.
	glColor3f(0.0f, 0.0f, 1.0f);
	iDelta = 2.0 * PI / 100.f; 

	glBegin(0);
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < iVertex; j++)
		{
			//회오리를 만들기 위해 x와 y값을 추가해준다.
			glVertex2f(Info[0][j].fX, Info[0][j].fY);
			
		}
	}
	glEnd();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 292; i++)
		{
			if (i >= 145)
				Info[0][i].fX = x + 146.f;
			else
				Info[0][i].fX = x;

			Info[0][i].fY = 600.f - y;

		}
		iCount++;
		glutTimerFunc(100, TimerFunction, 1);
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{

	if (iTimer_Count > 145)
	{
		Info[0][iTimer_Count - 1].fX -= fRadius * cos(iDelta * fDistance);
		Info[0][iTimer_Count - 1].fY -= fRadius * sin(iDelta * fDistance);
		fRadius -= 0.5f;
		//iDelta += 5.f;
		fDistance -= 2.0f;
	}
	else
	{
		Info[0][iTimer_Count - 1].fX += fRadius * cos(iDelta * fDistance);
		Info[0][iTimer_Count - 1].fY += fRadius * sin(iDelta * fDistance);
		fRadius += 0.5f;
		//iDelta += 5.f;
		fDistance += 2.0f;
	}

	iTimer_Count++;

	if (iVertex != 292)
		iVertex++;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}