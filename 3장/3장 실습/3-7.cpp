#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct  
{
	float fX;
	float fY;
	float fX2;
	float fY2;

}Vertex_Point;

typedef struct
{
	float Vertex_Point[1][2];

}Circle_Point;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int iX, int iY);
void TimerFunction(int value);
Vertex_Point Rect[100];
Circle_Point Circle;

int iCount = 0;
int iCircle_Count = 0;
int iMouse_Count = 0;
float radius = 15.f;

void main()
{
	srand((unsigned)time(NULL));
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-7");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.7f, 0.3f, 0.3f);
	for (int i = 0; i < iCount; i++)
	{
		glRectf(Rect[i].fX, Rect[i].fY, Rect[i].fX2, Rect[i].fY2);
	}

	glColor3f(0.1f, 0.1f, 0.8f);
	for (int i = 0; i < iCircle_Count; i++)
	{
		glPushMatrix();
		glTranslatef(Circle.Vertex_Point[i][0], Circle.Vertex_Point[i][1], 0.0f);
		glBegin(GL_POLYGON);
		for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f)
		{
			glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);
		}
		glEnd();
		glPopMatrix();
	}

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int iX, int iY)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

		Rect[iCount].fX = iX - rand() % 20 + 10;
		Rect[iCount].fY = 600.f - iY + rand() % 20 + 10;
		Rect[iCount].fX2 = iX + rand() % 20 + 10;
		Rect[iCount].fY2 = 600.f - iY - rand() % 20 + 10;


		if (iCount != 100)
			iCount++;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (iCircle_Count == 1)
			iCircle_Count = 0;

		if (iCircle_Count < 1)
		{
			Circle.Vertex_Point[iCircle_Count][0] = iX;
			Circle.Vertex_Point[iCircle_Count][1] = 600.f - iY;
			iCircle_Count++;
		}

		if (iMouse_Count == 0)
			glutTimerFunc(50, TimerFunction, 1);

		iMouse_Count++;
		
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	for (int i = 0; i < iCount; i++)
	{
		if (Rect[i].fX - 10.f > Circle.Vertex_Point[0][0])
		{
			Rect[i].fX -= 5.f;
			Rect[i].fX2 -= 5.f;
		}
		else
		{
			Rect[i].fX += 5.f;
			Rect[i].fX2 += 5.f;
		}

		if (Rect[i].fY - 10.f > Circle.Vertex_Point[0][1])
		{
			Rect[i].fY -= 5.f;
			Rect[i].fY2 -= 5.f;
		}
		else
		{
			Rect[i].fY += 5.f;
			Rect[i].fY2 += 5.f;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}