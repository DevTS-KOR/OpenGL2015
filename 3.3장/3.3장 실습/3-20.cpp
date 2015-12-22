#include <gl/glut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct Vertex
{
	float fX;
	float fY;
	float fZ;
}Vertex;

typedef struct Circle
{
	float fX;
	float fY;
	float fZ;
	float fMove_X;
	float fMove_Y;
	float fMove_Z;
}Circle;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void init();
void Circle_init();
void Color_init();
void Keyboard(unsigned char key, int x, int y);
void TimerFunc(int value);
void Mouse(int button, int state, int x, int y);
float randomFloat();

Vertex One_Vertex[4];
Vertex Two_Vertex[4];
Vertex Three_Vertex[4];
Vertex Four_Vertex[4];
Vertex Five_Vertex[4];
Vertex Six_Vertex[4];
Circle str_Circle[5];

float Zoom = 500.f;
float YRotate = 0.f;
float ZRotate = 0.f;

int iCircle_Count = 0;

float fRed[5] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
float fGreen[5] = { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
float fBlue[5] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f };
float fMouse_X1, fMouse_X2;

void main()
{
	//초기화 함수들
	init();
	Circle_init();
	//Color_init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-20");
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunc, 1);
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, Zoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glRotatef(30.f, 1.f, 0.f, 0.f);
	glRotatef(YRotate, 0.f, 1.f, 0.f);
	glRotatef(ZRotate, 0.f, 0.f, 1.f);

	if (fMouse_X1 > fMouse_X2)
		ZRotate += 10.f;

	else if (fMouse_X1 < fMouse_X2)
		ZRotate -= 10.f;

	glutSolidCube(200);

	glBegin(GL_QUADS);
	glColor3f(fRed[0], fGreen[0], fBlue[0]);
	glVertex3f(One_Vertex[0].fX, One_Vertex[0].fY, One_Vertex[0].fZ);
	glVertex3f(One_Vertex[1].fX, One_Vertex[1].fY, One_Vertex[1].fZ);
	glVertex3f(One_Vertex[2].fX, One_Vertex[2].fY, One_Vertex[2].fZ);
	glVertex3f(One_Vertex[3].fX, One_Vertex[3].fY, One_Vertex[3].fZ);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(fRed[1], fGreen[1], fBlue[1]);
	glVertex3f(Two_Vertex[0].fX, Two_Vertex[0].fY, Two_Vertex[0].fZ);
	glVertex3f(Two_Vertex[0].fX, Two_Vertex[1].fY, Two_Vertex[1].fZ);
	glVertex3f(Two_Vertex[0].fX, Two_Vertex[2].fY, Two_Vertex[2].fZ);
	glVertex3f(Two_Vertex[0].fX, Two_Vertex[3].fY, Two_Vertex[3].fZ);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(fRed[2], fGreen[2], fBlue[2]);
	glVertex3f(Three_Vertex[0].fX, Three_Vertex[0].fY, Three_Vertex[0].fZ);
	glVertex3f(Three_Vertex[1].fX, Three_Vertex[1].fY, Three_Vertex[1].fZ);
	glVertex3f(Three_Vertex[2].fX, Three_Vertex[2].fY, Three_Vertex[2].fZ);
	glVertex3f(Three_Vertex[3].fX, Three_Vertex[3].fY, Three_Vertex[3].fZ);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(fRed[3], fGreen[3], fBlue[3]);
	glVertex3f(Four_Vertex[0].fX, Four_Vertex[0].fY, Four_Vertex[0].fZ);
	glVertex3f(Four_Vertex[1].fX, Four_Vertex[1].fY, Four_Vertex[1].fZ);
	glVertex3f(Four_Vertex[2].fX, Four_Vertex[2].fY, Four_Vertex[2].fZ);
	glVertex3f(Four_Vertex[3].fX, Four_Vertex[3].fY, Four_Vertex[3].fZ);
	glEnd();

	/*glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(Five_Vertex[0].fX, Five_Vertex[0].fY, Five_Vertex[0].fZ);
	glVertex3f(Five_Vertex[1].fX, Five_Vertex[1].fY, Five_Vertex[1].fZ);
	glVertex3f(Five_Vertex[2].fX, Five_Vertex[2].fY, Five_Vertex[2].fZ);
	glVertex3f(Five_Vertex[3].fX, Five_Vertex[3].fY, Five_Vertex[3].fZ);
	glEnd();*/

	glBegin(GL_QUADS);
	glColor3f(fRed[4], fGreen[4], fBlue[4]);
	glVertex3f(Six_Vertex[0].fX, Six_Vertex[0].fY, Six_Vertex[0].fZ);
	glVertex3f(Six_Vertex[1].fX, Six_Vertex[1].fY, Six_Vertex[1].fZ);
	glVertex3f(Six_Vertex[2].fX, Six_Vertex[2].fY, Six_Vertex[2].fZ);
	glVertex3f(Six_Vertex[3].fX, Six_Vertex[3].fY, Six_Vertex[3].fZ);
	glEnd();

	if (iCircle_Count >= 1)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(str_Circle[0].fX, str_Circle[0].fY, str_Circle[0].fZ);
		glutSolidSphere(5.f, 20.f, 20.f);
		glPopMatrix();
	}

	if (iCircle_Count >= 2)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(str_Circle[1].fX, str_Circle[1].fY, str_Circle[1].fZ);
		glutSolidSphere(5.f, 20.f, 20.f);
		glPopMatrix();
	}

	if (iCircle_Count >= 3)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(str_Circle[2].fX, str_Circle[2].fY, str_Circle[2].fZ);
		glutSolidSphere(5.f, 20.f, 20.f);
		glPopMatrix();
	}

	if (iCircle_Count >= 4)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(str_Circle[3].fX, str_Circle[3].fY, str_Circle[3].fZ);
		glutSolidSphere(5.f, 20.f, 20.f);
		glPopMatrix();
	}

	if (iCircle_Count >= 5)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(str_Circle[4].fX, str_Circle[4].fY, str_Circle[4].fZ);
		glutSolidSphere(5.f, 20.f, 20.f);
		glPopMatrix();
	}

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void init()
{
	One_Vertex[0] = { -50.f, -50.f, 50.f };
	One_Vertex[1] = { 50.f, -50.f, 50.f };
	One_Vertex[2] = { 50.f, -50.f, -50.f };
	One_Vertex[3] = { -50.f, -50.f, -50.f };

	Two_Vertex[0] = { 50.f, -50.f, 50.f };
	Two_Vertex[1] = { 50.f, -50.f, -50.f };
	Two_Vertex[2] = { 50.f, 50.f, -50.f };
	Two_Vertex[3] = { 50.f, 50.f, 50.f };

	Three_Vertex[0] = { 50.f, -50.f, -50.f };
	Three_Vertex[1] = { -50.f, -50.f, -50.f };
	Three_Vertex[2] = { -50.f, 50.f, -50.f };
	Three_Vertex[3] = { 50.f, 50.f, -50.f };

	Four_Vertex[0] = { -50.f, -50.f, -50.f };
	Four_Vertex[1] = { -50.f, -50.f, 50.f };
	Four_Vertex[2] = { -50.f, 50.f, 50.f };
	Four_Vertex[3] = { -50.f, 50.f, -50.f };

	Five_Vertex[0] = { -50.f, -50.f, 50.f };
	Five_Vertex[1] = { 50.f, -50.f, 50.f };
	Five_Vertex[2] = { 50.f, 50.f, 50.f };
	Five_Vertex[3] = { -50.f, 50.f, 50.f };

	Six_Vertex[0] = { -50.f, 50.f, 50.f };
	Six_Vertex[1] = { 50.f, 50.f, 50.f };
	Six_Vertex[2] = { 50.f, 50.f, -50.f };
	Six_Vertex[3] = { -50.f, 50.f, -50.f };

}

void Circle_init()
{
	srand((unsigned)time(NULL));

	str_Circle[0] = { rand() % 45, rand() % 45, rand() % 45, 5.f, 2.5f, 5.f };
	str_Circle[1] = { rand() % 45, rand() % 45, rand() % 45, 5.f, 2.5f, 5.f };
	str_Circle[2] = { rand() % 45, rand() % 45, rand() % 45, 5.f, 2.5f, 5.f };
	str_Circle[3] = { rand() % 45, rand() % 45, rand() % 45, 5.f, 2.5f, 5.f };
	str_Circle[4] = { rand() % 45, rand() % 45, rand() % 45, 5.f, 2.5f, 5.f };
}


/*void Color_init()
{
	for (int i = 0; i < 5; i++)
	{
		fRed[i] = rand() % 2;
		fGreen[i] = rand() % 2;
		fBlue[i] = rand() % 2;
	}
}*/

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'Z')
		Zoom -= 10.f;

	else if (key == 'z')
		Zoom += 10.f;

	else if (key == 'Y')
		YRotate += 10.f;

	else if (key == 'y')
		YRotate -= 10.f;

	else if (key == 'b' || key == 'B')
	{
		if (iCircle_Count != 5)
			iCircle_Count++;
	}

	else if (key == '0')
	{
		fMouse_X1 = 0.f;
		fMouse_X2 = 0.f;
	}


	glutPostRedisplay();
}

void TimerFunc(int value)
{
	for (int i = 0; i < iCircle_Count; i++)
	{
		str_Circle[i].fX += str_Circle[i].fMove_X;
		str_Circle[i].fY += str_Circle[i].fMove_Y;
		str_Circle[i].fZ += str_Circle[i].fMove_Z;

		if (str_Circle[i].fX >= 45)
		{
			fRed[1] = randomFloat();
			fGreen[1] = randomFloat();
			fBlue[1] = randomFloat();
			str_Circle[i].fMove_X *= -1;
		}

		if (str_Circle[i].fX <= -45)
		{
			fRed[3] = randomFloat();
			fGreen[3] = randomFloat();
			fBlue[3] = randomFloat();
			str_Circle[i].fMove_X *= -1;
		}

		if (str_Circle[i].fY >= 45)
		{
			fRed[4] = randomFloat();
			fGreen[4] = randomFloat();
			fBlue[4] = randomFloat();
			str_Circle[i].fMove_Y *= -1;
		}

		if (str_Circle[i].fY <= -45)
		{
			fRed[0] = randomFloat();
			fGreen[0] = randomFloat();
			fBlue[0] = randomFloat();
			str_Circle[i].fMove_Y *= -1;
		}

		if (str_Circle[i].fZ >= 45)
		{
			str_Circle[i].fMove_Z *= -1;
		}

		if (str_Circle[i].fZ <= -45)
		{
			fRed[2] = randomFloat();
			fGreen[2] = randomFloat();
			fBlue[2] = randomFloat();
			str_Circle[i].fMove_Z *= -1;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

float randomFloat()
{
	return (float)rand() / RAND_MAX;
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		fMouse_X1 = x;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		fMouse_X2 = x;

	glutPostRedisplay();
}
