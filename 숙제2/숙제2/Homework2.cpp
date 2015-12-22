#include <gl/glut.h>
#include "Village.h"
#include "Roller.h"
#include "Skybox.h"
#include "Weather.h"
#include "Fireplay.h"
#include "OutSkybox.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

typedef struct XYZ
{
	float fX;
	float fY;
	float fZ;
}XYZ;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void TimerFunction2(int value);
int randomRange(int n1, int n2);
XYZ Bezier(XYZ *p, int n, double mu);

Village village;
Roller roller;
Skybox skybox;
OutSkybox outskybox;
Weather weather;
class Bomb bomb[10];

XYZ Control_Point2[20];
XYZ p[100];
float Control_Point[20][3];

float fCamera_X = 0.0f;
float fXplus = 0.0f;
float fYplus = 0.0f;
float fBefore_Camera_Z = 600.f;
float fCamera_Y = 600.0f;
float fCamera_Z = 600.0f;
float fZplus = 0.0f;
float fMouse_X[20];
float fMouse_Y[20];
float fMouse_Z[20];
int iMouse_Count = 0;
int iMove_Count = 0;
int iWaether_Count = 0;

int iView = 0;
bool Z_Click[20];
bool Light1 = true;
bool Light2 = true;
bool MultiView = false;
float ambient_Light1 = 0.3f;
float diffuse_Light1= 0.2f;
float specre_f1 = 0.2f;

float ambient_Light2 = 0.8f;
float diffuse_Light2 = 0.8f;
float specre_f2 = 0.5f;

void main()
{
	//초기화 함수들
	for (int i = 0; i < 20; i++)
		Z_Click[i] = false;

	for (int i = 0; i < iMouse_Count; i++)
		Control_Point2[i].fZ = 0.f;


	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		bomb[i].Init_boom(rand() % 500 - 250, 0.f, randomRange(-450, -150));
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("숙제2");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	village.SetupRC();
	skybox.SetupRC();
	outskybox.SetupRC();
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(50, TimerFunction2, 2);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLoadIdentity();

	if (MultiView == false)
		glViewport(0, 0, 800, 600);
	
	if (MultiView == true)
		glViewport(0, 0, 400, 600);

	glPushMatrix();
	if (iView == 0)
		gluLookAt(0.0f, 0.0f, fBefore_Camera_Z, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	else if (iView == 1)
		gluLookAt(0.0f, fCamera_Y, 0.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	else if (iView >= 2)
	{
		gluLookAt(0.0f, 400.0f, fCamera_Z, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	}


	//시점변환
	glRotatef(fXplus, 1, 0, 0);
	glRotatef(fYplus, 0, 1, 0);
	glRotatef(fZplus, 0, 0, 1);

	GLfloat diffuseLight1[] = { diffuse_Light1, diffuse_Light1, diffuse_Light1, 1.0f };
	GLfloat ambientLight1[] = { ambient_Light1, ambient_Light1, ambient_Light1, 1.0f };
	GLfloat specref1[] = { specre_f1, specre_f1, specre_f1, 1.0f };

	GLfloat diffuseLight2[] = { diffuse_Light2, diffuse_Light2, diffuse_Light2, 1.0f };
	GLfloat ambientLight2[] = { ambient_Light2, ambient_Light2, ambient_Light2, 1.0f };
	GLfloat specref2[] = { specre_f2, specre_f2, specre_f2, 1.0f };

	glEnable(GL_LIGHTING);

	if (Light1 == true)
	{
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	if (Light2 == true)
	{
		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glTranslatef(0.0f, 0.f, 300.0f);
	GLfloat lightPos[] = { 300, -300, -100, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat lightPos2[] = { -300, 0, -500, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glTranslatef(0.0f, 0.f, -300.0f);
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);


	glPushMatrix();
	glTranslatef(0.0f, 0.f, 300.0f);
	for (int i = 0; i < 10; i++)
		bomb[i].draw();
	glTranslatef(0.0f, 0.f, -300.0f);
	glPopMatrix();


	glPointSize(10);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < iMouse_Count; i++)
	{
		if (iView == 0)
			glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);
		else if (iView == 1)
			glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);
		else if (iView >= 2)
			glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);

	}
	glEnd();


	for (int i = 0; i < 100; i++)
	{
		p[i] = Bezier(Control_Point2, iMouse_Count - 1, i / (float)100);
		glColor3f(1.0f, 0.0f, 1.0f);
		glLineWidth(3);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; i++)
			glVertex3f(p[i].fX, p[i].fY, p[i].fZ);
		glEnd();
	}

	//롤러코스터 생성 및 이동
	if (iView >= 2)
	{
		glPushMatrix();
		glTranslatef(p[iMove_Count].fX, p[iMove_Count].fY, p[iMove_Count].fZ);
		roller.draw();
		glTranslatef(-p[iMove_Count].fX, -p[iMove_Count].fY, -p[iMove_Count].fZ);
		glPopMatrix();
	}

	//랜덤한 위치의 빌딩 10개 생성
	glPushMatrix();
	village.Draw();
	glPopMatrix();

	//스카이박스 생성
	if (iView >= 2)
	{
		glPushMatrix();
		outskybox.Draw();
		skybox.Draw();
		glPopMatrix();

		if (iWaether_Count == 1)
		{
			//눈 내리는 날씨
			glPushMatrix();
			weather.Snow_Draw();
			glPopMatrix();
		}

		else if (iWaether_Count == 2)
		{
			//비오는 날씨
			glPushMatrix();
			weather.Rain_Draw();
			glPopMatrix();
		}
	}
	glPopMatrix();

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	if (MultiView == false)
		glViewport(0, 0, 800, 600);

	if (MultiView == true)
		glViewport(400, 0, 800, 600);

	glPushMatrix();

	if (iView >= 2 && MultiView == true)
	{
		gluLookAt(0.0f, 0.0f, fCamera_Z, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);



		//시점변환
		glTranslatef(-100.f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.f, 0.0f);
		glRotatef(fXplus, 1, 0, 0);
		glRotatef(fYplus, 0, 1, 0);
		glRotatef(fZplus, 0, 0, 1);


		glPushMatrix();
		glTranslatef(0.0f, 0.f, 300.0f);
		for (int i = 0; i < 10; i++)
			bomb[i].draw();
		glTranslatef(0.0f, 0.f, -300.0f);
		glPopMatrix();


		glPointSize(10);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < iMouse_Count; i++)
		{
			if (iView == 0)
				glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);
			else if (iView == 1)
				glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);
			else if (iView >= 2)
				glVertex3f(Control_Point2[i].fX, Control_Point2[i].fY, Control_Point2[i].fZ);

		}
		glEnd();


		for (int i = 0; i < 100; i++)
		{
			p[i] = Bezier(Control_Point2, iMouse_Count - 1, i / (float)100);
			glColor3f(1.0f, 0.0f, 1.0f);
			glLineWidth(3);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 100; i++)
				glVertex3f(p[i].fX, p[i].fY, p[i].fZ);
			glEnd();
		}

		//롤러코스터 생성 및 이동
		if (iView >= 2)
		{
			glPushMatrix();
			glTranslatef(p[iMove_Count].fX, p[iMove_Count].fY, p[iMove_Count].fZ);
			roller.draw();
			glTranslatef(-p[iMove_Count].fX, -p[iMove_Count].fY, -p[iMove_Count].fZ);
			glPopMatrix();
		}

		//랜덤한 위치의 빌딩 10개 생성
		glPushMatrix();
		village.Draw();
		glPopMatrix();

		//스카이박스 생성
		if (iView >= 2)
		{
			glPushMatrix();
			outskybox.Draw();
			skybox.Draw();
			glPopMatrix();

			if (iWaether_Count == 1)
			{
				//눈 내리는 날씨
				glPushMatrix();
				weather.Snow_Draw();
				glPopMatrix();
			}

			else if (iWaether_Count == 2)
			{
				//비오는 날씨
				glPushMatrix();
				weather.Rain_Draw();
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
	
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400.0, 400.0, -300.0, 300.0, -2000.0, 2000.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'z')
		fZplus -= 10.f;

	else if (key == 'Z')
		fZplus += 10.f;

	else if (key == 'x')
		fXplus -= 10.f;

	else if (key == 'X')
		fXplus += 10.f;

	else if (key == 'y')
		fYplus -= 10.f;

	else if (key == 'Y')
		fYplus += 10.f;

	else if (key == 'p')
		fCamera_Z += 10.f;

	else if (key == 'P')
		fCamera_Z -= 10.f;

	else if (key == '1')
		iView++;

	else if (key == '2')
	{
		if (iWaether_Count >= 2)
			iWaether_Count = 0;
		else 
			iWaether_Count++;
	}

	else if (key == '3')
	{
		if (Light1 == true)
			Light1 = false;
		else
			Light1 = true;
	}

	else if (key == '4')
	{
		if (Light2 == true)
			Light2 = false;
		else
			Light2 = true;
	}

	else if (key == '5')
	{
		Light1 = true;
		Light2 = true;
	}

	else if (key == '6')
	{
		Light1 = false;
		Light2 = false;
	}

	else if (key ==  '0')
	{
		if (MultiView == false)
			MultiView = true;
		else
			MultiView = false;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

	if (iView == 0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			for (int i = 0; i < 10; i++)
			{
				if ((x - 400) > village.fX[i] - 25 && x - 400 < village.fX[i] + 25)
				{
					if (village.fScale_Y[i] == 1)
						if (-y + 300 < -275)
							return;
					
					if (village.fScale_Y[i] == 2)
						if (-y + 300 < -250)
							return;

					if (village.fScale_Y[i] == 3)
						if (-y + 300 < -225)
							return;

					if (village.fScale_Y[i] == 4)
						if (-y + 300 < -200)
							return;
				}
					
			}
			

			Control_Point2[iMouse_Count].fX = x - 400;
			Control_Point2[iMouse_Count].fY = -y + 300;
			Control_Point2[iMouse_Count].fZ = 0.f;

			if (iMouse_Count >= 20)
				iMouse_Count = 20;
			else
				iMouse_Count++;
		}
	}

	else if (iView == 1)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			cout << -x + 400 << ", " << -y + 300 << endl << endl;
			for (int i = 0; i < iMouse_Count; i++)
			{

				if ((-x + 400) >= (Control_Point2[i].fX - 5) && (-x + 400) <= (Control_Point2[i].fX + 5)
					&& (-y + 300) >= (Control_Point2[i].fZ - 5) && (-y + 300) <= (Control_Point2[i].fZ + 5))
				{
					cout << 1 << endl;
					Z_Click[i] = true;
				}
			}
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			for (int i = 0; i <= iMouse_Count; i++)
			{
				if (Z_Click[i] == true)
				{
					Control_Point2[i].fX = -x + 400.f;
					Control_Point2[i].fZ = -y + 300.f;
					Z_Click[i] = false;
				}
			}
		}
	}



	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (iView >= 2)
	{
		fYplus += 2.f;

	}

	if (iWaether_Count == 1)
	{

		for (int i = 0; i < 60; i++)
		{
			if (weather.snow.fY[i] <= -300.f)
				weather.snow.fY[i] = 300.f;
			else
				weather.snow.fY[i] -= 10.f;
		}

	}

	else if (iWaether_Count == 2)
	{
		for (int i = 0; i < 60; i++)
		{
			if (weather.rain.fY[i] <= -300.f)
				weather.rain.fY[i] = 300.f;
			else
				weather.rain.fY[i] -= 10.f;
		}
	}

	if (iView >= 2)
	{
		if (iMove_Count > 100)
			iMove_Count = 0;
		else
			iMove_Count++;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void TimerFunction2(int value)
{
	if (iView >= 2)
	{
		for (int i = 0; i < 10; i++)
			bomb[i].update(1);
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction2, 2);
}

XYZ Bezier(XYZ *p, int n, double mu)
{
	int iCount, kn, nn, nkn;
	double blend, muk, munk;
	XYZ position = { 0.0, 0.0, 0.0 };
	muk = 1;
	munk = pow(1 - mu, (double)n);

	for (iCount = 0; iCount <= n; iCount++)
	{
		nn = n;
		kn = iCount;
		nkn = n - iCount;
		blend = muk * munk;
		muk *= mu;
		munk /= (1 - mu);
		while (nn >= 1)
		{
			blend *= nn;
			nn--;
			if (kn > 1)
			{
				blend /= (double)kn;
				kn--;
			}
			if (nkn > 1)
			{
				blend /= (double)nkn;
				nkn--;
			}
		}

		position.fX += p[iCount].fX * blend;
		position.fY += p[iCount].fY * blend;
		position.fZ += p[iCount].fZ * blend;

	}
	return(position);

}

int randomRange(int n1, int n2)
{
	return (int)(rand() % (n2 - n1 + 1)) + n1;
}
