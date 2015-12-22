#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct Rotate
{
	float fX;
	float fY;
	float fZ;
}Rotate;

typedef struct Snow
{
	float fX;
	float fY;
	float fZ;
}Snow;

typedef struct Nomal
{
	float fX;
	float fY;
	float fZ;
}Nomal;

typedef struct NomalVector
{
	float PQ_X;
	float PQ_Y;
	float PQ_Z;
	float PR_X;
	float PR_Y;
	float PR_Z;
	float PQ_X_PR;
	float PQ_Y_PR;
	float PQ_Z_PR;
}NomalVector;

Rotate Rotation;
Snow Snow_Shower[50];
Nomal Nomal_Vector1[3];
Nomal Nomal_Vector2[3];
Nomal Nomal_Vector3[3];
Nomal Nomal_Vector4[3];
NomalVector _Nomal_Vector[4];

float fX_Rotation = 10.f;
float fY_Rotation = 10.f;
float fZ_Rotation = 10.f;
float Circle_Sphere1_Y = 0.0f;
float fY_Circle1 = 5.f;
float fZoom = 600.0f;
float fPlus = 10.f;
float fLight_Y = 0.0f;
float fLightPlus_Y = 10.f;
float fLight_Y2 = 0.f;
float fLightPlus_Y2 = 10.f;
float fLight_Y3 = 0.f;
float fLightPlus_Y3 = 10.f;
float fLight_Y4 = 0.f;
float fLightPlus_Y4 = 10.f;
float Random_X[50];
float Random_Y[50];
float Random_Z[50];
float Down_Y[50];
/////////////////////////////////
float ambient_Light = 0.3f;
float diffuse_Light = 0.2f;
float specre_f = 0.2f;
float ambient_Plus = 0.1f;
float diffuseLight_Plus = 0.1f;
float specref_Plus = 0.1f;
float Snow_Y = 10.f;
float fNomal1 = 0.0f;
float fNomal2 = 0.0f;
float fNomal3 = 0.0f;
float fNomal_Rotate = 0.0f;
float fNomal_Rotate_Plus = 10.f;
bool Light1 = false;
bool Light2 = false;
bool Light3 = false;
bool Light4 = false;
bool bNomal = false;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunc(int value);
void Keyboard(unsigned char key, int x, int y);
void Ground();
void Triangle();
void Circle_Sphere1();
void Circle_Sphere2();
int randomRange(int n1, int n2);

void main()
{
	//초기화 함수들
	srand((unsigned)time(NULL));

	for (int i = 0; i < 50; i++)
	{
		Random_X[i] = rand() % 500 - 250;
		Random_Y[i] = 200.f;
		Random_Z[i] = rand() % 500 - 250;
		Down_Y[i] = 2.5f;
	}

	for (int i = 0; i < 50; i++)
	{
		Snow_Shower[i].fX = Random_X[i];
		Snow_Shower[i].fY = Random_Y[i];
		Snow_Shower[i].fZ = Random_Z[i];
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-24");
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
	gluLookAt(0.0, 300.0, fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	GLfloat diffuseLight[] = { diffuse_Light, diffuse_Light, diffuse_Light, 1.0f };
	GLfloat ambientLight[] = { ambient_Light, ambient_Light, ambient_Light, 1.0f };
	GLfloat specref[] = { specre_f, specre_f, specre_f, 1.0f };

	glEnable(GL_LIGHTING);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	if (Light1 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	if (Light2 == true)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	if (Light3 == true)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);

	if (Light4 == true)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);

	glShadeModel(GL_SMOOTH);


	glRotatef(Rotation.fX, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.fY, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.fZ, 0.0f, 0.0f, 1.0f);


	GLfloat lightPos[] = { -25.f, fLight_Y, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat lightPos2[] = { 25.f, fLight_Y2, 0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	GLfloat lightPos3[] = { 25.f, fLight_Y2, 50.f, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos3);

	GLfloat lightPos4[] = { -25.f, fLight_Y2, 50.f, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos4);


	glPushMatrix();
	glRotatef(fNomal_Rotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(100.f, 0.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);
	glPopMatrix();


	glPushMatrix();
	{

		for (int i = 0; i < 50; i++)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(Snow_Shower[i].fX, Snow_Shower[i].fY, Snow_Shower[i].fZ);
			glutSolidCone(5, 5, 5, 5);

			if (Snow_Shower[i].fY <= -200.f)
				Snow_Shower[i].fY = 200.f;
		}

		for (int i = 0; i < 50; i++)
			Snow_Shower[i].fY -= Down_Y[i];
	}

	glPopMatrix();

	glPushMatrix();
	{
		Ground();
	}
	glPopMatrix();

	glPushMatrix();
	{
		Triangle();
	}

	glPushMatrix();
	{
		glRotatef(Circle_Sphere1_Y, 0.0f, 1.0f, 0.0f);
		glTranslatef(200.0f, 0.f, 0.0f);
		Circle_Sphere1();

		glRotatef(Circle_Sphere1_Y, 0.0f, 1.0f, 0.0f);
		glTranslatef(100.0f, 0.f, 0.0f);
		Circle_Sphere2();
	}

	glPopMatrix();
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

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'X')
		Rotation.fX += fX_Rotation;
	else if (key == 'x')
		Rotation.fX -= fX_Rotation;
	else if (key == 'Y')
		Rotation.fY += fY_Rotation;
	else if (key == 'y')
		Rotation.fY -= fY_Rotation;
	else if (key == 'Z')
		Rotation.fZ += fZ_Rotation;
	else if (key == 'z')
		Rotation.fZ -= fZ_Rotation;
	else if (key == 'A')
	{
		if (Light1 == true)
			Light1 = false;
		else
			Light1 = true;

		if (Light2 == true)
			Light2 = false;
		else
			Light2 = true;

		if (Light3 == true)
			Light3 = false;
		else
			Light3 = true;

		if (Light4 == true)
			Light4 = false;
		else
			Light4 = true;
	}
	else if (key == 'N')
	{
		if (bNomal == true)
			bNomal = false;
		else
			bNomal = true;
	}
	else if (key == ']')
		fZoom += fPlus;
	else if (key == '[')
		fZoom -= fPlus;
	else if (key == '9')
		fLight_Y += fLightPlus_Y;
	else if (key == '0')
		fLight_Y -= fLightPlus_Y;
	else if (key == '7')
		fLight_Y2 += fLightPlus_Y2;
	else if (key == '8')
		fLight_Y2 -= fLightPlus_Y2;
	else if (key == 'a')
		ambient_Light -= ambient_Plus;
	else if (key == 's')
		ambient_Light += ambient_Plus;
	else if (key == 'd')
		diffuse_Light -= diffuseLight_Plus;
	else if (key == 'f')
		diffuse_Light += diffuseLight_Plus;
	else if (key == 'g')
		specre_f -= specref_Plus;
	else if (key == 'h')
		specre_f += specref_Plus;

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	Circle_Sphere1_Y += fY_Circle1;

	fNomal_Rotate += fNomal_Rotate_Plus;
	//if (fZ_Zoom == 0)


	glutPostRedisplay();
	glutTimerFunc(50, TimerFunc, 1);
}

void Ground()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	//glRotatef(45.f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -200.f, 0.0f);
	glScalef(1.5f, 0.1f, 1.0f);
	glutSolidCube(500);

}

void Triangle()
{

	Nomal_Vector1[0].fX = -25.f;
	Nomal_Vector1[0].fY = 0.0f;
	Nomal_Vector1[0].fZ = 0.0f;
	Nomal_Vector1[1].fX = 25.f;
	Nomal_Vector1[1].fY = 0.0f;
	Nomal_Vector1[1].fZ = 0.0f;
	Nomal_Vector1[2].fX = 0.f;
	Nomal_Vector1[2].fY = 100.0f;
	Nomal_Vector1[2].fZ = 25.0f;

	_Nomal_Vector[0].PQ_X = Nomal_Vector1[1].fX - Nomal_Vector1[0].fX;
	_Nomal_Vector[0].PQ_Y = Nomal_Vector1[1].fY - Nomal_Vector1[0].fY;
	_Nomal_Vector[0].PQ_Z = Nomal_Vector1[1].fZ - Nomal_Vector1[0].fZ;
	_Nomal_Vector[0].PR_X = Nomal_Vector1[2].fX - Nomal_Vector1[0].fX;
	_Nomal_Vector[0].PR_Y = Nomal_Vector1[2].fY - Nomal_Vector1[0].fY;
	_Nomal_Vector[0].PR_Z = Nomal_Vector1[2].fZ - Nomal_Vector1[0].fZ;

	_Nomal_Vector[0].PQ_X_PR = _Nomal_Vector[0].PQ_Y * _Nomal_Vector[0].PR_Z 
		- _Nomal_Vector[0].PQ_Z * _Nomal_Vector[0].PR_Y;
	_Nomal_Vector[0].PQ_Y_PR = _Nomal_Vector[0].PQ_Z * _Nomal_Vector[0].PR_X
		- _Nomal_Vector[0].PQ_X * _Nomal_Vector[0].PR_Z;
	_Nomal_Vector[0].PQ_Z_PR = _Nomal_Vector[0].PQ_X * _Nomal_Vector[0].PR_Y
		- _Nomal_Vector[0].PQ_Y * _Nomal_Vector[0].PR_X;

	glTranslatef(0.f, -100.f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	if (bNomal == true)
		glNormal3f(_Nomal_Vector[0].PQ_X_PR, _Nomal_Vector[0].PQ_Y_PR, _Nomal_Vector[0].PQ_Z_PR);
	glVertex3f(-25.f, 0.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();

	Nomal_Vector2[0].fX = 25.f;
	Nomal_Vector2[0].fY = 0.0f;
	Nomal_Vector2[0].fZ = 0.0f;
	Nomal_Vector2[1].fX = 25.f;
	Nomal_Vector2[1].fY = 0.0f;
	Nomal_Vector2[1].fZ = 50.0f;
	Nomal_Vector2[2].fX = 0.f;
	Nomal_Vector2[2].fY = 100.0f;
	Nomal_Vector2[2].fZ = 25.0f;

	_Nomal_Vector[1].PQ_X = Nomal_Vector2[1].fX - Nomal_Vector2[0].fX;
	_Nomal_Vector[1].PQ_Y = Nomal_Vector2[1].fY - Nomal_Vector2[0].fY;
	_Nomal_Vector[1].PQ_Z = Nomal_Vector2[1].fZ - Nomal_Vector2[0].fZ;
	_Nomal_Vector[1].PR_X = Nomal_Vector2[2].fX - Nomal_Vector2[0].fX;
	_Nomal_Vector[1].PR_Y = Nomal_Vector2[2].fY - Nomal_Vector2[0].fY;
	_Nomal_Vector[1].PR_Z = Nomal_Vector2[2].fZ - Nomal_Vector2[0].fZ;

	_Nomal_Vector[1].PQ_X_PR = _Nomal_Vector[1].PQ_Y * _Nomal_Vector[1].PR_Z
		- _Nomal_Vector[1].PQ_Z * _Nomal_Vector[1].PR_Y;
	_Nomal_Vector[1].PQ_Y_PR = _Nomal_Vector[1].PQ_Z * _Nomal_Vector[1].PR_X
		- _Nomal_Vector[1].PQ_X * _Nomal_Vector[1].PR_Z;
	_Nomal_Vector[1].PQ_Z_PR = _Nomal_Vector[1].PQ_X * _Nomal_Vector[1].PR_Y
		- _Nomal_Vector[1].PQ_Y * _Nomal_Vector[1].PR_X;

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	if (bNomal == true)
		glNormal3f(_Nomal_Vector[1].PQ_X_PR, _Nomal_Vector[1].PQ_Y_PR, _Nomal_Vector[1].PQ_Z_PR);
	glVertex3f(25.f, 0.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 50.f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();



	Nomal_Vector3[0].fX = 25.f;
	Nomal_Vector3[0].fY = 0.0f;
	Nomal_Vector3[0].fZ = 50.0f;
	Nomal_Vector3[1].fX = -25.f;
	Nomal_Vector3[1].fY = 0.0f;
	Nomal_Vector3[1].fZ = 50.0f;
	Nomal_Vector3[2].fX = 0.f;
	Nomal_Vector3[2].fY = 100.0f;
	Nomal_Vector3[2].fZ = 25.0f;

	_Nomal_Vector[2].PQ_X = Nomal_Vector3[1].fX - Nomal_Vector3[0].fX;
	_Nomal_Vector[2].PQ_Y = Nomal_Vector3[1].fY - Nomal_Vector3[0].fY;
	_Nomal_Vector[2].PQ_Z = Nomal_Vector3[1].fZ - Nomal_Vector3[0].fZ;
	_Nomal_Vector[2].PR_X = Nomal_Vector3[2].fX - Nomal_Vector3[0].fX;
	_Nomal_Vector[2].PR_Y = Nomal_Vector3[2].fY - Nomal_Vector3[0].fY;
	_Nomal_Vector[2].PR_Z = Nomal_Vector3[2].fZ - Nomal_Vector3[0].fZ;

	_Nomal_Vector[2].PQ_X_PR = _Nomal_Vector[2].PQ_Y * _Nomal_Vector[2].PR_Z
		- _Nomal_Vector[2].PQ_Z * _Nomal_Vector[2].PR_Y;
	_Nomal_Vector[2].PQ_Y_PR = _Nomal_Vector[2].PQ_Z * _Nomal_Vector[2].PR_X
		- _Nomal_Vector[2].PQ_X * _Nomal_Vector[2].PR_Z;
	_Nomal_Vector[2].PQ_Z_PR = _Nomal_Vector[2].PQ_X * _Nomal_Vector[2].PR_Y
		- _Nomal_Vector[2].PQ_Y * _Nomal_Vector[2].PR_X;


	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	if (bNomal == true)
		glNormal3f(_Nomal_Vector[2].PQ_X_PR, _Nomal_Vector[2].PQ_Y_PR, _Nomal_Vector[2].PQ_Z_PR);
	glVertex3f(25.f, 0.0f, 50.f);
	glVertex3f(-25.f, 0.0f, 50.f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();

	Nomal_Vector4[0].fX = -25.f;
	Nomal_Vector4[0].fY = 0.0f;
	Nomal_Vector4[0].fZ = 50.0f;
	Nomal_Vector4[1].fX = -25.f;
	Nomal_Vector4[1].fY = 0.0f;
	Nomal_Vector4[1].fZ = 0.0f;
	Nomal_Vector4[2].fX = 0.f;
	Nomal_Vector4[2].fY = 100.0f;
	Nomal_Vector4[2].fZ = 25.0f;

	_Nomal_Vector[3].PQ_X = Nomal_Vector4[1].fX - Nomal_Vector4[0].fX;
	_Nomal_Vector[3].PQ_Y = Nomal_Vector4[1].fY - Nomal_Vector4[0].fY;
	_Nomal_Vector[3].PQ_Z = Nomal_Vector4[1].fZ - Nomal_Vector4[0].fZ;
	_Nomal_Vector[3].PR_X = Nomal_Vector4[2].fX - Nomal_Vector4[0].fX;
	_Nomal_Vector[3].PR_Y = Nomal_Vector4[2].fY - Nomal_Vector4[0].fY;
	_Nomal_Vector[3].PR_Z = Nomal_Vector4[2].fZ - Nomal_Vector4[0].fZ;

	_Nomal_Vector[3].PQ_X_PR = _Nomal_Vector[3].PQ_Y * _Nomal_Vector[3].PR_Z
		- _Nomal_Vector[3].PQ_Z * _Nomal_Vector[3].PR_Y;
	_Nomal_Vector[3].PQ_Y_PR = _Nomal_Vector[3].PQ_Z * _Nomal_Vector[3].PR_X
		- _Nomal_Vector[3].PQ_X * _Nomal_Vector[3].PR_Z;
	_Nomal_Vector[3].PQ_Z_PR = _Nomal_Vector[3].PQ_X * _Nomal_Vector[3].PR_Y
		- _Nomal_Vector[3].PQ_Y * _Nomal_Vector[3].PR_X;

	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	if (bNomal == true)
		glNormal3f(_Nomal_Vector[3].PQ_X_PR, _Nomal_Vector[3].PQ_Y_PR, _Nomal_Vector[3].PQ_Z_PR);
	glVertex3f(-25.f, 0.0f, 50.f);
	glVertex3f(-25.f, 0.0f, 0.f);
	glVertex3f(0.0f, 100.f, 25.f);
	glEnd();

}

void Circle_Sphere1()
{
	glColor3f(1.f, 0.0f, 0.0f);
	glutSolidSphere(30, 25, 25);
}

void Circle_Sphere2()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(20, 20, 20);
}

int randomRange(int n1, int n2)
{
	return (int)(rand() % (n2 - n1 + 1)) + n1;
}
