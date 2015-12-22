#include <gl/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.141592

//따로 하는거면 스위치를 써보자

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void TimerFunction2(int value);

bool Triangle = false;					//삼각형을 만들기위한 판정.
bool SinFunc = false;
bool CosFunc = false;
bool SpringFunc = false;
bool SinStart = false;
bool CosStart = false;
bool Sin_to_Cos = false;
bool Cos_to_Sin = false;
float fCenter_TriangleX = 0.0f;			//원점기준 삼각형의 회전.
float fRect_TriangleX = 0.0f;			//사각형의 원점기준 삼각형의 회전.
float fTriangleX = 0.0f;					//삼각형의 중점기준 회전.
float fTrans_X = 0.0f;
float fTrans_Y = 0.0f;

float fZoom = 1.0f;
float fRect_Zoom = 1.0f;
float fChange_Sin = 2.0f;
float fChange_Cos = 2.0f;

int iAnimation_X;
int iAnimation_Y = 0;
int iAnimation_Count = 1;

////Sin, Cos을 만들 점 정보/////
float VertexPoint[200][2];
float VertexPoint2[200][2];
float VertexPoint3[200][2];
float fRed = 1.0f;
float fBlue = 0.0f;
float fSin_X;
float fSin_Y;
float fCos_X;
float fCos_Y;
float fSpring_X;
float fSpring_Y;
float fTheta = 0.0f;
////////////////////////////////
float fReverse_SinX = -10.f;

void main()
{
	for (int i = 0; i < 200; i++)
	{
		VertexPoint[i][0] = 0.0f;
		VertexPoint[i][1] = 0.0f;
	}

	fSin_X = -10.0f;				//좌표정보.
	fSin_Y = 0.0f;
	fCos_X = -10.f;
	fCos_Y = 0.0f;
	fSpring_X = -10.0f;
	fSpring_Y = 0.0f;

	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-10");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);				//이동, 회전, 신축을 위함이다.(현재의 행렬 모드를 설정)
	glLoadIdentity();						//시각 좌표계를 원점으로 초기화 한다.

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.f, 10.0f);
	glVertex2f(0.f, -10.0f);
	glVertex2f(-10.f, 0.f);
	glVertex2f(10.0f, 0.f);
	glEnd();


	glPushMatrix();
	glTranslatef(fTrans_X, fTrans_Y, 0.0f);
	glScalef(fZoom, fZoom, 0.0f);			//확대 축소를 위한 스케일함수


	glRotatef(fCenter_TriangleX, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 1.0f);

	if (SinFunc == true)
		for (int i = 0; i < 200; i++)
		{
			VertexPoint[i][0] = fSin_X;
			VertexPoint[i][1] = fSin_Y;
			fSin_X += 0.1f;
			if (Sin_to_Cos == false)
				fSin_Y = fChange_Sin * sin(fSin_X);
			else
				fSin_Y = fChange_Sin * cos(fSin_X);
			glVertex3f(VertexPoint[i][0], VertexPoint[i][1], 0.0f);
		}
	else if (SinFunc == false)
	{
		fSin_X = -10.0f;				//좌표정보.
		fSin_Y = 0.0f;
		fCos_X = -10.f;
		fCos_Y = 0.0f;
		fSpring_X = -10.f;
		fSpring_Y = 0.0f;
	}

	if (CosFunc == true)
		for (int i = 0; i < 200; i++)
		{
			VertexPoint2[i][0] = fCos_X;
			VertexPoint2[i][1] = fCos_Y;
			fCos_X += 0.1f;
			if (Cos_to_Sin == false)
				fCos_Y = fChange_Cos * cos(fCos_X);
			else
				fCos_Y = fChange_Cos * sin(fCos_X);
			glVertex3f(VertexPoint2[i][0], VertexPoint2[i][1], 0.0f);
		}

	else if (CosFunc == false)
	{
		fSin_X = -10.0f;				//좌표정보.
		fSin_Y = 0.0f;
		fCos_X = -10.f;
		fCos_Y = 0.0f;
		fSpring_X = -10.f;
		fSpring_Y = 0.0f;
	}

	if (SpringFunc == true)
	{
		for (int i = 0; i < 200; i++)
		{
			if (i % 10 == 9)
			{
				fRed -= 0.05f;
				fBlue += 0.05f;
			}
			glColor3f(fRed, 0.0f, fBlue);
			VertexPoint3[i][0] = fSpring_X;
			VertexPoint3[i][1] = fSpring_Y;
			
			if (fSpring_X <= 10.0f)
			{
				fSpring_X += sin(fTheta * 2.0f);
				fSpring_Y += cos(fTheta * 2.0f);
				fSpring_X += 0.05f;
				fTheta += 0.1f;
			}
			glVertex3f(VertexPoint3[i][0], VertexPoint3[i][1], 1.0f);

		}

		fSpring_X = -10.f;
		fSpring_Y = 0.0f;
		fTheta = 0.0f;
		fRed = 1.0f;
		fBlue = 0.0f;
	}
	else if (SpringFunc == false)
	{
		fSin_X = -10.0f;				//좌표정보.
		fSin_Y = 0.0f;
		fCos_X = -10.f;
		fCos_Y = 0.0f;
		fSpring_X = -10.f;
		fSpring_Y = 0.0f;
	}
	glEnd();

	glPushMatrix();

	if (Triangle == true)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);
		glScalef(fRect_Zoom, fRect_Zoom, 0.0f);
		glRotatef(fRect_TriangleX, 0.0f, 0.0f, 1.0f);
		glutSolidCube(0.5);
	}

	glPopMatrix();
	glPopMatrix();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '4')
	{
		if (Triangle == true)
			Triangle = false;
		else
		{
			SinFunc = false;
			CosFunc = false;
			SpringFunc = false;
			Triangle = true;
		}
	}

	else if (key == '3')
	{
		if (SpringFunc == true)
			SpringFunc = false;
		else
		{
			SinFunc = false;
			CosFunc = false;
			Triangle = false;
			SpringFunc = true;
		}
	}

	else if (key == 'R')				//원점을 중심으로 회전
		fCenter_TriangleX += 10.f;

	else if (key == 'r')				//사각형의 원점을 중심으로 회전
		fRect_TriangleX += 10.f;

	else if (key == 'S')
	{
		if (fZoom >= 3.0f)
			fZoom = 3.0f;
		else
			fZoom += 0.05f;
	}

	else if (key == 's')
	{
		if (fZoom <= 0.05f)
			fZoom = 0.05f;
		else
			fZoom -= 0.05f;
	}

	else if (key == '1')
	{
		if (SinFunc == false)
		{
			CosFunc = false;
			SpringFunc = false;
			SpringFunc = false;
			SinFunc = true;
		}
		else
			SinFunc = false;
	}

	else if (key == '2')
	{
		if (CosFunc == false)
		{
			SinFunc = false;
			SpringFunc = false;
			SpringFunc = false;
			CosFunc = true;
		}
		else
			CosFunc = false;
	}

	else if (key == 'X')
		fTrans_X += 0.1f;


	else if (key == 'x')
		fTrans_X -= 0.1f;

	else if (key == 'Y')
		fTrans_Y += 0.1f;

	else if (key == 'y')
		fTrans_Y -= 0.1f;

	else if (key == 'C')
		fRect_Zoom += 0.05f;

	else if (key == 'c')
		fRect_Zoom -= 0.05f;

	else if (key == 'i' || key == 'I')
	{
		fSin_X = -10.0f;				//좌표정보.
		fSin_Y = 0.0f;
		fCos_X = -10.f;
		fCos_Y = 0.0f;
		fSpring_X = -10.f;
		fSpring_Y = 0.0f;
		fCenter_TriangleX = 0.0f;			//원점기준 삼각형의 회전.
		fRect_TriangleX = 0.0f;			//사각형의 원점기준 삼각형의 회전.
		fTriangleX = 0.0f;					//삼각형의 중점기준 회전.
		fTrans_X = 0.0f;
		fTrans_Y = 0.0f;
		fZoom = 1.0f;
		fRect_Zoom = 1.0f;
		iAnimation_X;
		iAnimation_Y = 0;
		iAnimation_Count = 1;
	}

	else if (key == 'b')
		glutTimerFunc(500, TimerFunction, 1);

	else if (key == 'B')
		glutTimerFunc(500, TimerFunction2, 2);

	else if (key == 'q' || key == 'Q')
		exit(1);

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	/////////////Sin -> Cos//////////////////
	if (SinStart == false)
		fChange_Sin -= 0.1f;

	if (fChange_Sin <= 0.0f)
	{
		fChange_Sin = 0;
		SinStart = true;
		Sin_to_Cos = true;
	}

	if (SinStart == true)
	{
		fChange_Sin += 0.1f;
	}

	if (fChange_Sin >= 2.0f)
		fChange_Sin = 2.0f;
	///////////////////////////////////////

	glutPostRedisplay();
	glutTimerFunc(500, TimerFunction, 1);
}

void TimerFunction2(int value)
{
	///////////////Cos -> Sin///////////////
	if (CosStart == false)
		fChange_Cos -= 0.1f;

	if (fChange_Cos <= 0.0f)
	{
		fChange_Cos = 0;
		CosStart = true;
		Cos_to_Sin = true;
	}

	if (CosStart == true)
	{
		fChange_Cos += 0.1f;
	}

	if (fChange_Cos >= 2.0f)
		fChange_Cos = 2.0f;
	///////////////////////////////////////
	glutPostRedisplay();
	glutTimerFunc(500, TimerFunction2, 2);
}
