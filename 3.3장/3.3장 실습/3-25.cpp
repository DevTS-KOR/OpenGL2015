#include <gl/glut.h>
#include <iostream>
using namespace std;

typedef struct Rotate
{
	float fX;
	float fY;
	float fZ;
}Rotate;

typedef struct Rotate_Puls
{
	float fX;
	float fY;
	float fZ;
}Rotate_Plus;

typedef struct Trans
{
	float fX;
	float fY;
	float fZ;
}Trans;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunc(int value);
void Init();
void Rect();
void Shpere();
void Shpere_Trus();
void Keyboard(unsigned char key, int x, int y);

Rotate Cube_Rotate;
Rotate Shpere_Rotate;
Rotate Shpere_Trus_Rotate;
Rotate Trus_Rotate;

Rotate_Plus Cube_RotatePlus;
Rotate_Plus Shpere_RotatePlus;
Rotate_Plus Shpere_Trus_RotatePlus;
Rotate_Plus Trus_RotatePlus;

Trans Cube_Trans;
Trans Shpere_Trans;
Trans Shpere_Trus_Trans;
Trans Trus_Trans;

float fRotate_Y = 0.0f;
float fRotate_Plus_Y = 10.f;
float fAmbient_Light = 0.3f;
float fDiffuse_Light = 0.2f;
float fSpecre_f = 0.2f;
bool bLight = false;

void main()
{
	//초기화 함수들
	Init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-25");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunc, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	GLfloat diffuseLight[] = { fDiffuse_Light, fDiffuse_Light, fDiffuse_Light, 1.0f };
	GLfloat ambientLight[] = { fAmbient_Light, fAmbient_Light, fAmbient_Light, 1.0f };
	GLfloat specref[] = { fSpecre_f, fSpecre_f, fSpecre_f, 1.0f };

	glRotatef(fRotate_Y, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glEnable(GL_LIGHTING);

	if (bLight == false)
		glEnable(GL_LIGHT0);
	else if (bLight == true)
		glDisable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { 200, 75, 0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
	//150, 75
	glPushMatrix();
	{
		glTranslatef(-100.f, 50.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 150.f, 0.0f);
		glVertex3f(0.0f, -50.f, 0.0f);
		glEnd();
		Rect();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(100.f, 75.f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-50.f, 0.0f, 0.0f);
		glVertex3f(150.f, 0.0f, 0.0f);
		glEnd();
		Shpere();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(50.f, -200.f, 0.0f);
		glRotatef(45.f, 0.0f, 1.0f, 0.0f);
		glRotatef(-45.f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-50.f, 0.0f, 0.0f);
		glVertex3f(150.f, 0.0f, 0.0f);
		glEnd();
		Shpere_Trus();
	}
	glPopMatrix();
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

void Init()
{
	Cube_Rotate.fX = 0.f;
	Cube_Rotate.fY = 0.f;
	Cube_Rotate.fZ = 0.0f;
	Cube_RotatePlus.fX = 10.f;
	Cube_RotatePlus.fY = 10.f;
	Cube_RotatePlus.fZ = 10.f;
	Cube_Trans.fX = -50.f;
	Cube_Trans.fY = 50.f;
	Cube_Trans.fZ = 0.0f;
	///////////////////////////////////
	Shpere_Rotate.fX = 0.0f;
	Shpere_Rotate.fY = 0.0f;
	Shpere_Rotate.fZ = 0.0f;
	Shpere_RotatePlus.fX = 10.f;
	Shpere_RotatePlus.fY = 10.f;
	Shpere_RotatePlus.fZ = 10.f;
	Shpere_Trans.fX = 50.f;
	Shpere_Trans.fY = 50.f;
	Shpere_Trans.fZ = 0.0f;
	//////////////////////////////////
	Shpere_Trus_Rotate.fX = 0.0f;
	Shpere_Trus_Rotate.fY = 0.0f;
	Shpere_Trus_Rotate.fZ = 0.0f;
	Shpere_Trus_RotatePlus.fX = 10.f;
	Shpere_Trus_RotatePlus.fY = 10.f;
	Shpere_Trus_RotatePlus.fZ = 10.f;
	Shpere_Trus_Trans.fX = 75.f;
	Shpere_Trus_Trans.fY = 75.f;
	Shpere_Trus_Trans.fZ = 0.0f;

	//////////

	Trus_Rotate.fX = 0.0f;
	Trus_Rotate.fY = 0.0f;
	Trus_Rotate.fZ = 0.0f;
	Trus_RotatePlus.fX = 10.f;
	Trus_RotatePlus.fY = 10.f;
	Trus_RotatePlus.fZ = 10.f;
	Trus_Trans.fX = 50.f;
	Trus_Trans.fY = 50.f;
	Trus_Trans.fZ = 50.f;
}

void TimerFunc(int value)
{
	Cube_Rotate.fY += Cube_RotatePlus.fY;
	Shpere_Rotate.fX += Shpere_RotatePlus.fX;
	Shpere_Trus_Rotate.fZ += Shpere_Trus_RotatePlus.fZ;

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunc, 1);
}

void Rect()
{
	glColor3f(1.f, 0.0f, 0.0f);
	glRotatef(Cube_Rotate.fY, 0.0f, 1.0f, 0.0f);
	glTranslatef(Cube_Trans.fX, Cube_Trans.fY, Cube_Trans.fZ);
	glutSolidCube(50);
}

void Shpere()
{
	glColor3f(0.f, 1.f, 0.0f);
	glRotatef(Shpere_Rotate.fX, 1.0f, 0.0f, 0.0f);
	glTranslatef(Shpere_Trans.fX, Shpere_Trans.fY, Shpere_Trans.fZ);
	//glutSolidSphere(40, 25, 25);
	glutWireSphere(40, 25, 25);
}

void Shpere_Trus()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(Shpere_Trus_Rotate.fX, 1.0f, 0.0f, 0.0f);
	//glRotatef(Shpere_Trus_Rotate.fY, 0.0f, 1.0f, 0.0f);
	glRotatef(Shpere_Trus_Rotate.fZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(Shpere_Trus_Trans.fX, Shpere_Trus_Trans.fY, Shpere_Trus_Trans.fZ);
	glutSolidSphere(20, 15, 15);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidTorus(10, 50, 30, 30);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'y')
	{
		fRotate_Y += fRotate_Plus_Y;
	}
	else if (key == 'Y')
	{
		fRotate_Y -= fRotate_Plus_Y;
	}
	else if (key == '1')
	{
		if (bLight == false)
			bLight = true;
		else if (bLight == true)
			bLight = false;
	}
	else if (key == 'a')
	{
		fAmbient_Light += 0.1f;
	}
	else if (key == 'A')
	{
		fAmbient_Light -= 0.1f;
	}
	else if (key == 'd')
	{
		fDiffuse_Light += 0.1f;
	}
	else if (key == 'D')
	{
		fDiffuse_Light -= 0.1f;
	}
	else if (key == 's')
	{
		fSpecre_f += 0.1f;
	}
	else if (key == 'S')
	{
		fSpecre_f -= 0.1f;
	}
}