#include <gl/glut.h>
#include <iostream>
using namespace std;
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void MenuFunc(int button);
void Keyboard(unsigned char key, int x, int y);
int SubMenu1, SubMenu2, MainMenu;
int iChange = 0;
float fAngle1 = 0.0f;
float fDistance1 = 200.0f;
float fDistance1_1 = 100.0f;
float fX1[360];
float fY1[360];
float fCircle_X1[360];
float fCircle_Y1[360];
float fX1_1[360];
float fY1_1[360];
float fTornado_Angle1 = 0.0f;
///////////////////////////////////
float fAngle2 = 0.0f;
float fDistance2 = 200.0f;
float fDistance2_2 = 100.0f;
float fX2[360];
float fY2[360];
float fCircle_X2[360];
float fCircle_Y2[360];
float fX2_1[360];
float fY2_1[360];
float fTornado_Angle2 = 0.0f;
//////////////////////////////////
float fAngle3 = 0.0f;
float fDistance3 = 200.0f;
float fDistance3_3 = 100.0f;
float fX3[360];
float fY3[360];
float fCircle_X3[360];
float fCircle_Y3[360];
float fX3_1[360];
float fY3_1[360];
float fTornado_Angle3 = 0.0f;
float fPuls2 = 110.0f;
float fPuls3 = -110.0f;

float eyeX = 0.0f;
float centerY = 0.0f;
float upZ = 0.0f;
float fZview = 0.0f;

void main()
{
	for (int i = 0; i < 360; i++)
	{
		fX1[i] = 0.0f;
		fY1[i] = 0.0f;
		fX2[i] = 0.0f;
		fY2[i] = 0.0f;
	}
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D 윈도우");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid", 0);
	glutAddMenuEntry("Wire", 1);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Menu", SubMenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);

	glTranslatef(eyeX, centerY, upZ);
	glTranslatef(0.0f, 0.0f, fZview);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	if (iChange == 0)
		glutSolidSphere(50.0f, 25.0f, 25.0f);
	else
		glutWireSphere(50.0f, 25.0f, 25.0f);
	///////////////////////////////////
	glPushMatrix();
	glPointSize(2);
	glRotatef(290.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX1[i] = cos(fAngle1 * PI) * fDistance1;
		fY1[i] = sin(fAngle1 * PI) * fDistance1;
		fCircle_X1[i] = fX1[i];
		fCircle_Y1[i] = fY1[i];
		glVertex3f(fX1[i], fY1[i], 0.0f);
		fAngle1 += 0.008f;

	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(fTornado_Angle1, 0.0f, 1.0f, 1.0f);
	glTranslatef(-cos(fAngle1 * PI / 180) * fDistance1, sin(fAngle1 * PI / 180) * fDistance1, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX1_1[i] = cos(fAngle1 * PI) * fDistance1_1;
		fY1_1[i] = sin(fAngle1 * PI) * fDistance1_1;
		glVertex3f(fX1_1[i], fY1_1[i], 0.0f);
		fAngle1 += 0.008f;
	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(fTornado_Angle1, 0.0f, 1.0f, 1.0f);
	glTranslatef(-cos(fAngle1 + 5 * PI / 180) * fDistance1_1, sin(fAngle1 + 5 * PI / 180) * fDistance1_1, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glPointSize(2);
	glRotatef(fPuls2, 0.0f, 1.0f, 0.7f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX2[i] = cos(fAngle2 * PI) * fDistance2;
		fY2[i] = sin(fAngle2 * PI) * fDistance2;
		fCircle_X2[i] = fX2[i];
		fCircle_Y2[i] = fY2[i];
		glVertex3f(fX2[i], fY2[i], 0.0f);
		fAngle2 += 0.009f;

	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(fTornado_Angle2, 0.0f, 1.0f, 1.0f);
	glTranslatef(cos(fAngle2 * PI / 180) * fDistance2, sin(fAngle2 * PI / 180) * fDistance2, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(130.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX2_1[i] = cos(fAngle2 * PI) * fDistance2_2;
		fY2_1[i] = sin(fAngle2 * PI) * fDistance2_2;
		glVertex3f(fX2_1[i], fY2_1[i], 0.0f);
		fAngle2 += 0.006f;
	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(fTornado_Angle2, 0.0f, 1.0f, 1.0f);
	glTranslatef(cos(fAngle2 + 5 * PI / 180) * fDistance2_2, sin(fAngle2 + 5 * PI / 180) * fDistance2_2, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glPointSize(2);
	glRotatef(fPuls3, 0.0f, 1.0f, 0.7f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX3[i] = cos(fAngle3 * PI) * fDistance3;
		fY3[i] = sin(fAngle3 * PI) * fDistance3;
		fCircle_X3[i] = fX3[i];
		fCircle_Y3[i] = fY3[i];
		glVertex3f(fX3[i], fY3[i], 0.0f);
		fAngle3 += 0.01f;

	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(fTornado_Angle1, 0.0f, 1.0f, 1.0f);
	glTranslatef(-cos(fAngle3 * PI / 180) * fDistance3, sin(fAngle3 * PI / 180) * fDistance3, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(130.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		fX3_1[i] = cos(fAngle3 * PI) * fDistance3_3;
		fY3_1[i] = sin(fAngle3 * PI) * fDistance3_3;
		glVertex3f(fX3_1[i], fY3_1[i], 0.0f);
		fAngle3 += 0.009f;
	}
	glEnd();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(fTornado_Angle3, 0.0f, 1.0f, 1.0f);
	glTranslatef(cos(fAngle3 + 5 * PI / 180) * fDistance3_3, sin(fAngle3 + 5 * PI / 180) * fDistance3_3, 0.0f);
	if (iChange == 0)
		glutSolidSphere(25.0f, 25.0f, 25.0f);
	else
		glutWireSphere(25.0f, 25.0f, 25.0f);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////////
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	gluLookAt(0.0, 0.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void MenuFunc(int button)
{
	switch (button)
	{
	case 0:
		iChange = 0;
		break;
	case 1:
		iChange = 1;
		break;

		break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	fTornado_Angle1 = 1;
	fTornado_Angle2 = 1;
	fTornado_Angle3 = 1;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
		fPuls2 += 10.f;
	else if (key == '2')
		fPuls2 -= 10.f;

	if (key == '3')
		fPuls3 += 10.f;
	else if (key == '4')
		fPuls3 -= 10.f;

	if (key == '+')
		fZview = 10.0f;
	else if (key == '-')
		fZview = -10.0f;
	else if (key == '0')
		fZview = 0.0f;

	if (key == 'x')
		eyeX = 10.0f;
	else if (key == 'X')
		eyeX = -10.0f;
	else if (key == 'y')
		centerY += 1.0f;
	else if (key == 'Y')
		centerY += -1.0f;
	else if (key == 'z')
		upZ = 1.0f;
	else if (key == 'Z')
		upZ = -1.0f;

	if (key == 'i')
	{
		eyeX = 0.0f;
		centerY = 0.0f;
		upZ = 0.0f;
		fZview = 0.0f;
	}

	glutPostRedisplay();
}