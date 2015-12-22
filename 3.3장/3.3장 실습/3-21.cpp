#include <gl/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.141592
typedef struct Rotation
{
	float fY;
	float fStop_Y;
	float fRotate_X;
	float fTranslate_X;
	float fTranslate_Z;
}Rotation;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void init();
void Keyboard(unsigned char key, int x, int y);
Rotation figure[10];
int iCount = 0;
float fAngle[10];
float fDistance[10];
bool Depth = false;

void main()
{
	//초기화 함수들
	for (int i = 0; i < 10; i++)
	{
		fAngle[i] = 10.f;
		fDistance[i] = 10.f;
	}
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-21");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);

	if (Depth == true)
		glEnable(GL_DEPTH_TEST);
	else if (Depth == false)
		glDisable(GL_DEPTH_TEST);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);


	glPushMatrix();
	glColor3f(0.f, 0.f, 1.f);
	glScalef(1.f, 50.f, 1.f);
	glutSolidCube(10);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.f, 0.f, 0.f);
	glTranslated(0.f, figure[0].fY, 0.f);
	glTranslated(sin(fAngle[0] * PI) * fDistance[0], 0.f, cos(fAngle[0] * PI) * fDistance[0]);
	glRotatef(figure[0].fRotate_X, 1.f, 0.f, 0.f);
	glutWireTorus(25, 50, 20, 20);
	glPopMatrix();

	if (iCount >= 1)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[1].fY, 0.f);
		glTranslated(sin(fAngle[1] * PI) * fDistance[1], 0.f, cos(fAngle[1] * PI) * fDistance[1]);
		glRotatef(figure[1].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
		glPopMatrix();
	}

	if (iCount >= 2)
	{
		glPushMatrix();
		glColor3f(0.f, 1.f, 0.f);
		glScalef(5.f, 1.f, 5.f);
		glTranslated(0.f, figure[2].fY, 0.f);
		glTranslated(sin(fAngle[2] * PI) * fDistance[2], 0.f, cos(fAngle[2] * PI) * fDistance[2]);
		//glRotatef(figure[2].fRotate_X, 1.f, 0.f, 0.f);
		glutSolidCube(50);
		glPopMatrix();
	}

	if (iCount >= 3)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[3].fY, 0.f);
		glTranslated(sin(fAngle[3] * PI) * fDistance[3], 0.f, cos(fAngle[3] * PI) * fDistance[3]);
		glRotatef(figure[3].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
		glPopMatrix();
	}


	if (iCount >= 4)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[4].fY, 0.f);
		glTranslated(sin(fAngle[4] * PI) * fDistance[4], 0.f, cos(fAngle[4] * PI) * fDistance[4]);
		glRotatef(figure[4].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
		glPopMatrix();
	}

	if (iCount >= 5)
	{
		glPushMatrix();
		glColor3f(0.f, 1.f, 0.f);
		glScalef(5.f, 1.f, 5.f);
		glTranslated(0.f, figure[5].fY, 0.f);
		glTranslated(sin(fAngle[5] * PI) * fDistance[5], 0.f, cos(fAngle[5] * PI) * fDistance[5]);
		glRotatef(figure[5].fRotate_X, 1.f, 0.f, 0.f);
		glutSolidCube(50);
		glPopMatrix();
	}

	if (iCount >= 6)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[6].fY, 0.f);
		glTranslated(sin(fAngle[6] * PI) * fDistance[6], 0.f, cos(fAngle[6] * PI) * fDistance[6]);
		glRotatef(figure[6].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
		glPopMatrix();
	}


	if (iCount >= 7)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[7].fY, 0.f);
		glTranslated(sin(fAngle[7] * PI) * fDistance[7], 0.f, cos(fAngle[7] * PI) * fDistance[7]);
		glRotatef(figure[7].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
		glPopMatrix();
	}

	if (iCount >= 8)
	{
		glPushMatrix();
		glColor3f(0.f, 1.f, 0.f);
		glScalef(5.f, 1.f, 5.f);
		glTranslated(0.f, figure[8].fY, 0.f);
		glTranslated(sin(fAngle[8] * PI) * fDistance[8], 0.f, cos(fAngle[8] * PI) * fDistance[8]);
		glRotatef(figure[8].fRotate_X, 1.f, 0.f, 0.f);
		glutSolidCube(50);
		glPopMatrix();
	}

	if (iCount >= 9)
	{
		glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glTranslated(0.f, figure[9].fY, 0.f);
		glTranslated(sin(fAngle[9] * PI) * fDistance[9], 0.f, cos(fAngle[9] * PI) * fDistance[9]);
		glRotatef(figure[9].fRotate_X, 1.f, 0.f, 0.f);
		glutWireTorus(25, 50, 20, 20);
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
	figure[0] = { 250.f, -250.f, 90.f, sin(fAngle[0] * PI) * fDistance[0], cos(fAngle[0] * PI) * fDistance[0] };
	figure[1] = { 250.f, -200.f, 90.f, sin(fAngle[1] * PI) * fDistance[1], cos(fAngle[2] * PI) * fDistance[1] };
	figure[2] = { 250.f, -150.f, 90.f, sin(fAngle[2] * PI) * fDistance[2], cos(fAngle[2] * PI) * fDistance[2] };
	figure[3] = { 250.f, -100.f, 90.f, sin(fAngle[3] * PI) * fDistance[3], cos(fAngle[3] * PI) * fDistance[3] };
	figure[4] = { 250.f, -50.f, 90.f, sin(fAngle[4] * PI) * fDistance[4], cos(fAngle[4] * PI) * fDistance[4] };
	figure[5] = { 250.f, 0.f, 90.f, sin(fAngle[5] * PI) * fDistance[5], cos(fAngle[5] * PI) * fDistance[5] };
	figure[6] = { 250.f, 50.f, 90.f, sin(fAngle[6] * PI) * fDistance[6], cos(fAngle[6] * PI) * fDistance[6] };
	figure[7] = { 250.f, 100.f, 90.f, sin(fAngle[7] * PI) * fDistance[7], cos(fAngle[7] * PI) * fDistance[7] };
	figure[8] = { 250.f, 150.f, 90.f, sin(fAngle[8] * PI) * fDistance[8], cos(fAngle[8] * PI) * fDistance[8] };
	figure[9] = { 250.f, 200.f, 90.f, sin(fAngle[9] * PI) * fDistance[9], cos(fAngle[9] * PI) * fDistance[9] };

}

void TimerFunction(int value)
{

	if (figure[iCount].fY == figure[iCount].fStop_Y)
	{
		figure[iCount].fY = figure[iCount].fStop_Y;
		figure[iCount].fRotate_X = 0.f;
	}

	else
	{
		figure[iCount].fY -= 10.f;
		fAngle[iCount] += 0.2f;
		fDistance[iCount] += 0.1f;
		if (figure[iCount].fY == figure[iCount].fStop_Y)
			iCount++;

		if (iCount > 9)
		{
			iCount = 0;
			figure[0] = { 250.f, -250.f, 90.f, sin(fAngle[0] * PI) * fDistance[0], cos(fAngle[0] * PI) * fDistance[0] };
			figure[1] = { 250.f, -200.f, 90.f, sin(fAngle[1] * PI) * fDistance[1], cos(fAngle[2] * PI) * fDistance[1] };
			figure[2] = { 250.f, -150.f, 90.f, sin(fAngle[2] * PI) * fDistance[2], cos(fAngle[2] * PI) * fDistance[2] };
			figure[3] = { 250.f, -100.f, 90.f, sin(fAngle[3] * PI) * fDistance[3], cos(fAngle[3] * PI) * fDistance[3] };
			figure[4] = { 250.f, -50.f, 90.f, sin(fAngle[4] * PI) * fDistance[4], cos(fAngle[4] * PI) * fDistance[4] };
			figure[5] = { 250.f, 0.f, 90.f, sin(fAngle[5] * PI) * fDistance[5], cos(fAngle[5] * PI) * fDistance[5] };
			figure[6] = { 250.f, 50.f, 90.f, sin(fAngle[6] * PI) * fDistance[6], cos(fAngle[6] * PI) * fDistance[6] };
			figure[7] = { 250.f, 100.f, 90.f, sin(fAngle[7] * PI) * fDistance[7], cos(fAngle[7] * PI) * fDistance[7] };
			figure[8] = { 250.f, 150.f, 90.f, sin(fAngle[8] * PI) * fDistance[8], cos(fAngle[8] * PI) * fDistance[8] };
			figure[9] = { 250.f, 200.f, 90.f, sin(fAngle[9] * PI) * fDistance[9], cos(fAngle[9] * PI) * fDistance[9] };
		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		if (Depth == true)
			Depth = false;
		else if (Depth == false)
			Depth = true;
	}

	glutPostRedisplay();
}