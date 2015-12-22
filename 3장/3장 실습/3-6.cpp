#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
	float iX;
	float iY;
	int Rotate;
}Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void RenderRect(int value);
void MoveRect(int value);
void Mouse(int button, int state, int x, int y);
int iCount = 0;
int Render_Count = 0;
float iSpeed = 40.f;
float fX[10];
float fY[10];
float Mouse_fX;
float Mouse_fY;
int Start = 0;
Rect RectInfomation[10];

void main()
{
	srand((unsigned)time(NULL));
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-6");
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);

	glutTimerFunc(500, RenderRect, 2);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Render_Count - 1; ++i)
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_POLYGON);
		glVertex2f(RectInfomation[i].iX - 20.f, 600.f - RectInfomation[i].iY + 20.f);		//왜 600에서 빼야하나??
		glVertex2f(RectInfomation[i].iX + 20.f, 600.f - RectInfomation[i].iY + 20.f);		//윈도우와 GL이 좌표계가 다르기 때문
		glVertex2f(RectInfomation[i].iX + 20.f, 600.f - RectInfomation[i].iY - 20.f);
		glVertex2f(RectInfomation[i].iX - 20.f, 600.f - RectInfomation[i].iY - 20.f);
		glEnd();

	}
	
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}


void RenderRect(int value)
{

	RectInfomation[Render_Count].iX = rand() % ((760) + 1) + 20;
	RectInfomation[Render_Count].iY = rand() % ((560) + 1) + 20;

	if (Render_Count <= 10)
	{
		for (int i = 0; i < Render_Count; ++i)
		{
			fX[i] = RectInfomation[i].iX;
			fY[i] = RectInfomation[i].iY;
		}

		//if (Render_Count <= 10)
			++Render_Count;
	}
	glutPostRedisplay();
	glutTimerFunc(500, RenderRect, 2);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Mouse_fX = x;
		Mouse_fY = y;

		for (int i = 0; i < Render_Count; ++i)
		{
			RectInfomation[i].Rotate = 0;
		}
		for (int i = 0; i < Render_Count; ++i)
		{
			if (x > fX[i] - 20.f && x < fX[i] + 20.f)
				if(y >  fY[i] - 20.f && y < fY[i] + 20.f)
				glutTimerFunc(100, MoveRect, 1);
		}
		
	}
}

void MoveRect(int value)
{
	for (int i = 0; i < Render_Count; ++i)
	{
		if (Mouse_fX > fX[i] - 20.f && Mouse_fX < fX[i] + 20.f)
			if (Mouse_fY >  fY[i] - 20.f && Mouse_fY < fY[i] + 20.f)
			{
				glutTimerFunc(100, MoveRect, 1);
				Start++;
			}
	}

	if (Start != 0)
	for (int i = 0; i < Render_Count; ++i)
	{
		if (RectInfomation[i].iX + 20.f >= 800.f && RectInfomation[i].Rotate == 0)
		{
			RectInfomation[i].iX = 780.f;
			RectInfomation[i].Rotate = 1;
		}
		if (RectInfomation[i].iY + 20.f >= 600.f && RectInfomation[i].Rotate == 1)
		{
			RectInfomation[i].iY = 580.f;
			RectInfomation[i].Rotate = 2;
		}
		if (RectInfomation[i].iX - 20.f <= 0.f && RectInfomation[i].Rotate == 2)
		{
			RectInfomation[i].iX = 20.f;
			RectInfomation[i].Rotate = 3;
		}
		if (RectInfomation[i].iY - 20.f <= fY[i] && RectInfomation[i].Rotate == 3)
		{
			RectInfomation[i].iY = fY[i] - 20.f;
			RectInfomation[i].Rotate = 4;
		}
		if (RectInfomation[i].iX + 20.f >= fX[i] && RectInfomation[i].Rotate == 4)
		{
			RectInfomation[i].iX = fX[i] - 20.f;
			RectInfomation[i].Rotate = 5;
		}

		if (RectInfomation[i].Rotate == 0)
		{
			RectInfomation[i].iX += iSpeed;
		}
		if (RectInfomation[i].Rotate == 1)
		{
			RectInfomation[i].iY += iSpeed;
		}
		if (RectInfomation[i].Rotate == 2)
		{
			RectInfomation[i].iX -= iSpeed;
		}
		if (RectInfomation[i].Rotate == 3)
		{
			RectInfomation[i].iY -= iSpeed;
		}
		if (RectInfomation[i].Rotate == 4)
		{
			RectInfomation[i].iX += iSpeed;
		}
		if (RectInfomation[i].Rotate == 5)
		{
			RectInfomation[i].iX = fX[i];
			RectInfomation[i].iY = fY[i];
		}

		Start = 0;
	}

	glutPostRedisplay();
	
	
}
