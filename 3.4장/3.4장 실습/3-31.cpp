#include <gl/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef struct strGround
{
	float fX[60][60];
	float fY[60][60];
	float fZ[60][60];
}strGround;

typedef struct Crash
{
	float fCenter_X[4];
	float fCenter_Y[4];
	float fCenter_Z[4];
	float fRadius[4];
	float fCrash[4];
}Crash;

float fLeft_Right_Y = 100.f;
float fCenter_Y = -100.f;
float fLeft_Right_Y_Plus = 10.f;
float fCenter_Y_Plus = 10.f;
float fRect_Z = 50.f;
float fRect_Z_Plus = 10.f;
float fRect_Z2 = -50.f;
float fRect_Z_Plus2 = 10.f;

GLfloat fLeft_Ground[3][3][3] = { { { -300.f, 0.f, 100.f }, { -200.f, fLeft_Right_Y, 100.f }, { -100.f, 0.0f, 100.f } },
{ { -300.f, 0.f, -200.f }, { -200.f, fLeft_Right_Y, -200.f }, { -100.f, 0.0f, -200.f } },
{ { -300.f, 0.f, -500.f }, { -200.f, fLeft_Right_Y, -500.f }, { -100.f, 0.0f, -500.f } } };

GLfloat fCenter_Ground[3][3][3] = { { { -100.f, 0.f, 100.f }, { 0.f, fCenter_Y, 100.f }, { 100.f, 0.0f, 100.f } },
{ { -100.f, 0.f, -200.f }, { 0.f, fCenter_Y, -200.f }, { 100.f, 0.0f, -200.f } },
{ { -100.f, 0.f, -500.f }, { 0.f, fCenter_Y, -500.f }, { 100.f, 0.0f, -500.f } } };

GLfloat fRight_Ground[3][3][3] = { { { 100.f, 0.f, 100.f }, { 200.f, fLeft_Right_Y, 100.f }, { 300.f, 0.0f, 100.f } },
{ { 100.f, 0.f, -200.f }, { 200.f, fLeft_Right_Y, -200.f }, { 300.f, 0.0f, -200.f } },
{ { 100.f, 0.f, -500.f }, { 200.f, fLeft_Right_Y, -500.f }, { 300.f, 0.0f, -500.f } } };

GLfloat fRect[3][3][3] = { { { -50.f, 50.f, 50.f }, { 0.0f, 50.f, fRect_Z }, { 50.f, 50.f, 50.f } },
{ { -50.0f, 0.0f, 50.f }, { 0.0f, 0.0f, fRect_Z }, { 50.0f, 0.0f, 50.f } },
{ { -50.f, -50.f, 50.f }, { 0.0f, -50.f, fRect_Z }, { 50.f, -50.f, 50.f } } };

GLfloat fRect2[3][3][3] = { { { -50.f, 50.f, -50.f }, { 0.0f, 50.f, fRect_Z2 }, { 50.f, 50.f, -50.f } },
{ { -50.0f, 0.0f, -50.f }, { 0.0f, 0.0f, fRect_Z2 }, { 50.0f, 0.0f, -50.f } },
{ { -50.f, -50.f, -50.f }, { 0.0f, -50.f, fRect_Z2 }, { 50.f, -50.f, -50.f } } };

/*glBegin(GL_POLYGON);
glVertex3f(50.f, -50.f, -50.f);
glVertex3f(-50.f, -50.f, -50.f);
glVertex3f(-50.f, 50.f, -50.f);
glVertex3f(50.f, 50.f, -50.f);
glEnd();*/

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void TimerFunc(int value);
double randomDouble(void)
{
	return (double)rand() / RAND_MAX;
}

void Road();
void First_Rect();
void Second_Rect();
void Third_Rect();
void fourth_Rect();
void fifth_Rect();
void sixth_Rect();
void seventh_Rect();
void Player();
void Particle();


float yyy = 0.0f;
float yyy1 = 10.f;
strGround Ground;
Crash strCrash;


float fZoom = 800.f;
float fZoom_Plus = 10.f;
float fRotate_X = 0.0f;
float fRotate_Y = 0.0f;
float fRotate_Plus_X = 10.f;
float fRotate_Plus_Y = 10.f;
float fPlayer_X = 0.0f;
float fPlayer_Z = 0.f;
float fPlayer_Plus_X = 5.f;
float fPlayer_Plus_Z = 5.f;

float fPlayer_Center_X = 0.0f;
float fPlayer_Center_Y = 0.0f;
float fPlayer_Center_Z = 0.0f;
float fPlayer_Radius = 0.0f;
float fPlayer_to_Rect_Radius[4];
bool bCrash = false;

float fAmbient_Light = 0.3f;
float fAmbient_Light2 = 0.3f;
float fAmbient_Light3 = 0.3f;
float fDiffuse_Light = 0.5f;
float fDiffuse_Light2 = 0.5f;
float fDiffuse_Light3 = 0.5f;
float fSpecre_f = 0.2f;
float fAmbient_Plus = 0.1f;
float fDiffuse_Plus = 0.1f;
float fCutOff = 30.f;
float fCutOff_Plus = 5.f;
bool bOnOff = false;
bool bParticle = false;
bool bParticle_Small = false;
float Particle_Shpere = 15.f;
float Particle_X = 0.0f;
float Particle_Y = 0.0f;
float Particle_Plus_X = 10.0f;
float Particle_Plus_Y = 10.0f;



void main()
{
	//초기화 함수들
	/*for (int i = 0; i < 20; i++)
	{
	for (int j = 0; j < 20; j++)
	{

	Ground.fX[i][j] = -300.0f + (10 * i);
	Ground.fY[i][j] = 0.0f;
	Ground.fZ[i][j] = -500.0f + (10 * j);

	}
	}*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-31");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunc, 1);
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
	gluLookAt(0.0, yyy, fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	glRotatef(fRotate_X, 1.0f, 0.0f, 0.0f);
	glRotatef(fRotate_Y, 0.0f, 1.0f, 0.0f);

	GLfloat diffuseLight[] = { fDiffuse_Light, fDiffuse_Light2, fDiffuse_Light3, 1.0f };
	GLfloat ambientLight[] = { fAmbient_Light, fAmbient_Light2, fAmbient_Light3, 1.0f };
	GLfloat specref[] = { fSpecre_f, fSpecre_f, fSpecre_f, 1.0f };

	GLfloat diffuseLight2[] = { 1, 1, 1, 1.0f };
	GLfloat ambientLight2[] = { 0, 0, 0, 1.0f };
	GLfloat specref2[] = { 1, 1, 1, 1.0f };
	GLfloat spotlightDirection[] = { 0.0f, -1.0f, 0.0f };              // 스포트라이트 방향 
	GLfloat cutoff[] = { fCutOff };
	GLfloat exponent[] = { 15 };

	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	if (bOnOff == false)
		glEnable(GL_LIGHT1);
	else if (bOnOff == true)
		glDisable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { 0, 300.f, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat lightPos2[] = { fPlayer_X, 50.f, fPlayer_Z, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정



	glPushMatrix();
	glTranslatef(0.0f, -300.f, 0.0f);
	glRotatef(180.f, 1.0f, 0.0f, 0.0f);
	Road();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-250.f, -175.0f, 100.0f);
	First_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslated(270.f, -255.0f, 300.0f);
	Second_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.f, -250.f, 150.f);
	Third_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-250.f, -250.f, 200.f);
	fourth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100.f, -200.f, 0.f);
	fifth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, -100.f, 0.f);
	sixth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100.f, -200.f, 0.f);
	seventh_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, -250.f, 0.f);
	glTranslatef(fPlayer_X, 0.0f, fPlayer_Z);

	if (bParticle == false)
		Player();
	else if (bParticle == true)
		Particle();

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
	gluPerspective(60.0, 1.0, 1.0, 3000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
		fRotate_X += fRotate_Plus_X;

	else if (key == 'X')
		fRotate_X -= fRotate_Plus_X;

	else if (key == 'y')
		fRotate_Y += fRotate_Plus_Y;

	else if (key == 'Y')
		fRotate_Y -= fRotate_Plus_Y;

	else if (key == 'Z')
		fZoom -= fZoom_Plus;

	else if (key == 'z')
		fZoom += fZoom_Plus;

	else if (key == 'q')
		yyy -= yyy1;

	else if (key == 'Q')
		yyy += yyy1;

	else if (key == '+')
		fCutOff += fCutOff_Plus;

	else if (key == '-')
		fCutOff -= fCutOff_Plus;

	else if (key == '3')
	{
		if (bOnOff == false)
			bOnOff = true;
		else if (bOnOff == true)
			bOnOff = false;
	}

	else if (key == '4')
	{
		if (bParticle == false)
			bParticle = true;
		else if (bParticle == true)
			bParticle = false;
	}

	else if (key == '1')
	{
		if (fLeft_Right_Y == 120.f || fLeft_Right_Y == -120.f)
			fLeft_Right_Y_Plus *= -1;

		if (fCenter_Y == 120.f || fCenter_Y == -120.f)
			fCenter_Y_Plus *= -1;

		fLeft_Right_Y += fLeft_Right_Y_Plus;
		fCenter_Y -= fCenter_Y_Plus;
	}

	else if (key == '2')
	{
		if (fRect_Z == 100 || fRect_Z == 0)
			fRect_Z_Plus *= -1;

		if (fRect_Z2 == -100 || fRect_Z2 == 0)
			fRect_Z_Plus2 *= -1;

		fRect_Z += fRect_Z_Plus;
		fRect_Z2 += fRect_Z_Plus2;
	}

	glutPostRedisplay();

}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		fPlayer_X -= fPlayer_Plus_X;

	}
	else if (key == GLUT_KEY_RIGHT)
	{
		fPlayer_X += fPlayer_Plus_X;

	}

	else if (key == GLUT_KEY_UP)
	{
		fPlayer_Z -= fPlayer_Plus_Z;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		fPlayer_Z += fPlayer_Plus_Z;
	}

	glutPostRedisplay();

}

void TimerFunc(int value)
{

	if (fAmbient_Light >= 1.0f || fAmbient_Light <= 0.0f)
		fAmbient_Plus *= -1;

	fAmbient_Light += fAmbient_Plus;
	fAmbient_Light2 += fAmbient_Plus;
	fAmbient_Light3 += fAmbient_Plus;

	if (bParticle == true)
	{

		if (Particle_Y > 50.f)
		{
			Particle_Plus_Y *= -1;
			bParticle_Small = true;

		}
		else if (Particle_Y < -20.f)
			Particle_Plus_Y *= -1;

		Particle_X += Particle_Plus_X;
		Particle_Y += Particle_Plus_Y;

		if (bParticle_Small == true)
		{
			if (Particle_Shpere != 0.0f)
				Particle_Shpere -= 2.f;
		}


	}

	else if (bParticle == false)
	{
		bParticle_Small = false;
		Particle_X = 0.0f;
		Particle_Y = 0.0f;
		Particle_Shpere = 15.f;

	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

void Road()
{
	for (int i = 0; i < 3; i++)
	{
		fLeft_Ground[i][1][1] = fLeft_Right_Y;
		fCenter_Ground[i][1][1] = fCenter_Y;
		fRight_Ground[i][1][1] = fLeft_Right_Y;
	}
	glColor3f(1.0f, 0.0f, 0.0f);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &fLeft_Ground[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10., 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);


	glPointSize(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3f(fLeft_Ground[i][0][j], fLeft_Ground[i][0][j], fLeft_Ground[i][0][j]);
	glEnd();


	glColor3f(0.0f, 1.0f, 0.0f);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &fCenter_Ground[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10., 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);


	glPointSize(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3f(fCenter_Ground[i][0][j], fCenter_Ground[i][0][j], fCenter_Ground[i][0][j]);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &fRight_Ground[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10., 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);


	glPointSize(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3f(fRight_Ground[i][0][j], fRight_Ground[i][0][j], fRight_Ground[i][0][j]);
	glEnd();
	/*glBegin(GL_POLYGON);
	for (int i = 0; i < 60; i++)
	{
	for (int j = 0; j < 60; j++)
	{
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(Ground.fX[i][j], Ground.fY[i][j], Ground.fZ[i][j]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(Ground.fX[i][j] + 10.f, Ground.fY[i][j], Ground.fZ[i][j]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(Ground.fX[i][j] + 10.f, Ground.fY[i][j], Ground.fZ[i][j]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(Ground.fX[i][j], Ground.fY[i][j], Ground.fZ[i][j]);

	}
	}
	glEnd();*/
}

void First_Rect()
{
	glColor3f(0.f, 0.f, 0.8f);
	glScalef(1.0f, 5.f, 1.f);
	glutSolidCube(50);

	//glTranslated(0.f, -100.0f, 0.0f);
	glScalef(1.0f, 0.2f, 1.f);
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-25.f, -125.f, 25.f);
	glVertex3f(25.f, -125.f, 25.f);
	glVertex3f(25.f, 125.f, 25.f);
	glVertex3f(-25.f, 125.f, 25.f);
	glVertex3f(-25.f, -125.f, 25.f);
	glVertex3f(-25.f, -125.f, -25.f);
	glVertex3f(25.f, -125.f, -25.f);
	glVertex3f(25.f, -125.f, 25.f);
	glVertex3f(25.f, -125.f, -25.f);
	glVertex3f(25.f, 125.f, -25.f);
	glVertex3f(25.f, 125.f, 25.f);
	glVertex3f(25.f, 125.f, -25.f);
	glVertex3f(-25.f, 125.f, -25.f);
	glVertex3f(-25.f, 125.f, 25.f);
	glVertex3f(-25.f, 125.f, -25.f);
	glVertex3f(-25.f, -125.f, -25.f);
	glEnd();

}

void Second_Rect()
{
	glColor3f(0.9f, 0.2f, 0.2f);
	glScalef(2.0f, 3.0f, 2.0f);
	glutSolidCube(30);

	glScalef(0.5f, 0.333f, 0.5f);
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(30.f, -45.f, 30.f);
	glVertex3f(30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(-30.f, 45.f, 30.f);
	glVertex3f(-30.f, 45.f, -30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(30.f, -45.f, -30.f);
	glVertex3f(30.f, 45.f, -30.f);
	glVertex3f(-30.f, 45.f, -30.f);
	glVertex3f(-30.f, 45.f, 30.f);
	glVertex3f(30.f, 45.f, 30.f);
	glVertex3f(30.f, 45.f, -30.f);
	glEnd();
}

void Third_Rect()
{
	glColor3f(0.2f, 0.9f, 0.2f);
	glutSolidCube(100);

	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glEnd();
}

void fourth_Rect()
{
	/*GLfloat fRect[3][3][3] = { { { -50.f, 50.f, 50.f }, { 0.0f, 50.f, 50.f }, { 50.f, 50.f, 50.f } },
	{ { -50.0f, 0.0f, 50.f }, { 0.0f, 0.0f, 50.f }, { 50.0f, 0.0f, 50.f } },
	{ { -50.f, -50.f, 50.f }, { 0.0f, -50.f, 50.f }, { 50.f, -50.f, 50.f } } };*/

	for (int i = 0; i < 3; i++)
	{
		fRect[i][1][2] = fRect_Z;
		fRect[i][1][2] = fRect_Z;
		fRect[i][1][2] = fRect_Z;

		fRect2[i][1][2] = fRect_Z2;
		fRect2[i][1][2] = fRect_Z2;
		fRect2[i][1][2] = fRect_Z2;
	}

	glColor3f(1.0f, 0.2f, 0.0f);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &fRect[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);


	glPointSize(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3f(fRect[i][0][j], fRect[i][0][j], fRect[i][0][j]);
	glEnd();


	glColor3f(0.0f, 1.0f, 0.2f);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &fRect2[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);


	glPointSize(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3f(fRect2[i][0][j], fRect2[i][0][j], fRect2[i][0][j]);
	glEnd();


	glColor3f(0.0f, 0.8f, 1.0f);
	//glScalef(2.0f, 2.0f, 2.0f);
	glBegin(GL_POLYGON);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glEnd();*/

	glBegin(GL_POLYGON);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glEnd();
	//glutSolidCube(50);

	glScalef(0.5f, 0.5, 0.5f);
	glLineWidth(3);
	glScalef(2.0f, 2.0f, 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glEnd();
}

void fifth_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(50);
}

void sixth_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(5.0f, 1.0f, 1.0f);
	glutSolidCube(50);
}

void seventh_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(50);
}

void Player()
{
	glColor3f(1.0f, 0.3f, 0.7f);
	glutSolidSphere(50, 25, 25);

	//sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)));
	fPlayer_Center_X = fPlayer_X;
	fPlayer_Center_Y = -250.0f;
	fPlayer_Center_Z = fPlayer_Z;
	fPlayer_Radius = 50.f;
	cout << "1 : " << fPlayer_Center_X << ", " << fPlayer_Center_Y << ", " << fPlayer_Center_Z << endl;

	/*strCrash.fCenter_X[0] = -275.f;
	strCrash.fCenter_Y[0] = -250.f;
	strCrash.fCenter_Z[0] = 100.f;
	strCrash.fRadius[0] = 25.f;

	cout << "2 : " << strCrash.fCenter_X[0] << ", " << strCrash.fCenter_Y[0] << ", " << strCrash.fCenter_Z[0] << endl;
	fPlayer_to_Rect_Radius[0] = fPlayer_Radius + strCrash.fRadius[0];

	strCrash.fCrash[0] = sqrt(((strCrash.fCenter_X[0] - fPlayer_Center_X) * (strCrash.fCenter_X[0] - fPlayer_Center_X)
	+ (strCrash.fCenter_Y[0] - fPlayer_Center_Y)*(strCrash.fCenter_Y[0] - fPlayer_Center_Y)
	+ (strCrash.fCenter_Z[0] - fPlayer_Center_Z)*(strCrash.fCenter_Z[0] - fPlayer_Center_Z)));

	if (fPlayer_to_Rect_Radius[0] > strCrash.fCrash[0])
	cout << "충돌" << endl;*/

	if (fPlayer_Center_X < -175.f && fPlayer_Center_Z < 175.f && fPlayer_Center_Z > 25.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 30.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 170.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 30.f && fPlayer_Center_Z < 170.f && fPlayer_Center_X <= -175.f)
			fPlayer_X += 5.f;

	}
	//300   30+50 -30-50
	else if (fPlayer_Center_X > 195.f && fPlayer_Center_Z < 380.f && fPlayer_Center_Z > 220.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 225.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 375.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 225.f && fPlayer_Center_Z < 375.f && fPlayer_Center_X >= 195.f)
			fPlayer_X -= 5.f;

	}
	//150  50+50	-50-50
	else if (fPlayer_Center_X > 150.f && fPlayer_Center_Z < 250.f && fPlayer_Center_Z > 50.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 55.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 245.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 55.f && fPlayer_Center_Z < 245.f && fPlayer_Center_X >= 150.f)
			fPlayer_X -= 5.f;

	}
	//200 50+50 -50-50
	else if (fPlayer_Center_X < -150.f && fPlayer_Center_Z < 300.f && fPlayer_Center_Z > 100.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 105.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 295.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 105.f && fPlayer_Center_Z < 295.f && fPlayer_Center_X <= -155.f)
			fPlayer_X += 5.f;
	}

	else if (fPlayer_Center_X < -25.f && fPlayer_Center_X > -175.f && fPlayer_Center_Z < 75.f && fPlayer_Center_Z > -75.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_X >= -30.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X += 5.f;
		else if (fPlayer_Center_X <= -170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X -= 5.f;
		else if (fPlayer_Center_X < -30.f && fPlayer_Center_X > -170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= 70.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_X < -30.f && fPlayer_Center_X > -170.f && fPlayer_Center_Z >= -75.f && fPlayer_Center_Z <= -70.f)
			fPlayer_Z -= 5.f;
	}

	else if (fPlayer_Center_X > 25.f && fPlayer_Center_X < 175.f && fPlayer_Center_Z < 75.f && fPlayer_Center_Z > -75.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_X >= 30.f && fPlayer_Center_X <= 35.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X -= 5.f;
		else if (fPlayer_Center_X <= 170.f && fPlayer_Center_X >= 165.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X += 5.f;
		else if (fPlayer_Center_X > 30.f && fPlayer_Center_X < 170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= 70.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_X > 30.f && fPlayer_Center_X < 170.f && fPlayer_Center_Z >= -75.f && fPlayer_Center_Z <= -70.f)
			fPlayer_Z -= 5.f;
	}

	else if (fPlayer_X > -75.f && fPlayer_X < 75.f && fPlayer_Z < 10.f && fPlayer_Z > -10.f)
	{
		fDiffuse_Light = randomDouble();
		fDiffuse_Light2 = randomDouble();
		fDiffuse_Light3 = randomDouble();
	}

}

void Particle()
{
	//glColor3f(1.0f, 0.3f, 0.7f);
	//glutSolidSphere(50, 25, 25);

	////sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)));
	//fPlayer_Center_X = fPlayer_X;
	//fPlayer_Center_Y = -250.0f;
	//fPlayer_Center_Z = fPlayer_Z;
	//fPlayer_Radius = 50.f;

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(0.5f, 0.0f, 0.5f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(0.0f, 0.5f, 0.5f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);

	glRotatef(60.f, 0.0f, 1.0f, 0.0f);
	glTranslatef(Particle_X, Particle_Y, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(Particle_Shpere, Particle_Shpere, Particle_Shpere);
	glTranslatef(-Particle_X, -Particle_Y, 0.0f);
}
