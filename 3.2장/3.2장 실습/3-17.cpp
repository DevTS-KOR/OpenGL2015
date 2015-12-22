#include <gl/glut.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void ground();
void First_Rect();
void Second_Rect();
void Third_Rect();
float fRotate_X = 0.f;
float fRotate_Y = 0.f;
float fX = 0.f;
float fX_Move = 5.f;
float fZ = 0.f;
float fRotate_XY = 0.f;
float fRotate_XY2 = 0.f;
float fRotateX_Start = 0.f;
float fRotateY_Start = 0.f;

float fRotate_XZ = 0.f;
float fRotate_XZ2 = 0.f;
float fRotateX_Start2 = 0.f;
float fRotateZ_Start2 = 0.f;


void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-17");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1000.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	ground();
	glPushMatrix();
	First_Rect();
	
	glPushMatrix();
	Second_Rect();

	glPushMatrix();
	Third_Rect();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{

	if (key == 'y')
	{
		fRotate_Y -= 10.f;
	}
	else if (key == 'Y')
	{
		fRotate_Y += 10.f;
	}

	if (key == '1')
	{
		fRotate_XY += 10.f;
		fRotateX_Start = 1.f;
		//fRotateY_Start = 0.f;
	}

	else if (key == '2')
	{
		fRotate_XY -= 10.f;
		fRotateX_Start = 1.f;
		//fRotateY_Start = 0.f;
	}

	else if (key == '3')
	{
		fRotate_XY2 += 10.f;
		//fRotateX_Start = 0.f;
		fRotateY_Start = 1.f;
	}

	else if (key == '4')
	{
		fRotate_XY2 -= 10.f;
		//fRotateX_Start = 0.f;
		fRotateY_Start = 1.f;
	}

	else if (key == '9')
	{
		fRotate_X += 10.f;
	}

	else if (key == '0')
	{
		fRotate_X -= 10.f;
	}

	if (key == 'x')
	{
		fRotate_XZ -= 10.f;
		fRotateX_Start2 = 1.f;
		//fRotateZ_Start2 = 0.f;
	}

	else if (key == 'X')
	{
		fRotate_XZ += 10.f;
		fRotateX_Start2 = 1.f;
		//fRotateZ_Start2 = 0.f;
	}

	else if (key == 'z')
	{
		fRotate_XZ2 -= 10.f;
		//fRotateX_Start2 = 0.f;
		fRotateZ_Start2 = 1.f;
	}

	else if (key == 'Z')
	{
		fRotate_XZ2 += 10.f;
		//fRotateX_Start2 = 0.f;
		fRotateZ_Start2 = 1.f;
	}

	glutPostRedisplay();
}

void ground()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-200.f, -100.f, 750.f);
	glVertex3f(-200.f, -100.f, -1000.f);
	glVertex3f(200.f, -100.f, -1000.f);
	glVertex3f(200.f, -100.f, 750.f);
	glEnd();
}

void First_Rect()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5f, 2.0f, 2.f);
	glRotatef(fRotate_X, 0.f, 1.f, 0.f);
	glTranslatef(fX, -20.0f, 0.f);
	glRotatef(fRotate_Y, 0.0f, 1.0f, 0.0f);
	glutWireCube(50);
}

void Second_Rect()
{
	glColor3f(0.f, 1.f, 0.f);
	glScalef(1.f, 1.0f, 1.0f);
	glRotatef(fRotate_XY, fRotateX_Start, 0.f, 0.f);
	glRotatef(fRotate_XY2, 0.f, fRotateY_Start, 0.f);
	glTranslatef(0.f, 45.f, 0.0f);
	glutWireCube(40);

}

void Third_Rect()
{
	glColor3f(0.f, 0.f, 1.f);
	glScalef(0.7f, 0.7f, 0.7f);
	glRotatef(fRotate_XZ, fRotateX_Start2, 0.f, 0.f);
	glRotatef(fRotate_XZ2, 0.f, 0.f, fRotateZ_Start2);
	glTranslatef(0.f, 50.f, 0.0f);
	glutWireCube(40);
}

void TimerFunction(int value)
{
	fX += fX_Move;

	if (fX == 350.f || fX == -350.f)
		fX_Move *= (-1);

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}