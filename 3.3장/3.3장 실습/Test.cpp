#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <random>
using namespace std;
#define PI 3.141592

//-----------------------------------------------

enum PLANET
{
	PL_1,
	PL_2,
	PL_3,
};

//enum{ zoomi, rotatestate, zoomo };
//int anistate = zoomi;

struct translate
{
	float x;
	float y;
	float z;
};

bool LIGHT0 = true;
bool LIGHT1 = true;
bool LIGHT2 = true;
bool LIGHT3 = true;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void keyboard(unsigned char key, int x, int y);
GLvoid drawSolarSystem(PLANET ePlanet);
GLvoid InitSnow();

GLfloat rotX = 10;
GLfloat rotY = 0;
GLfloat rotZ = 0;

GLfloat rotX1 = 0;
GLfloat rotY1 = 0;
GLfloat rotZ1 = 0;

float planetOneRotateAngle, planetTwoRotateAngle = 0;
float planetOneAngle, planetTwoAngle = 0;
float innerPlanetOneAngle, innerPlanetTwoAngle = 0;

GLfloat AmbientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat DiffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 1.0 };

GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat zoom = 500.0;

class Snow{
	int x, y, z, size, speed;
public:
	void Init()
	{
		x = rand() % 400 - 200;
		y = rand() % 400 + 300;
		z = rand() % 400 - 200;
		size = rand() % 3 + 2;
		speed = rand() % 3 + 2;
	}
	void Draw()
	{
		Fall();
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(x, y, z);
		glutSolidSphere(size, 10, 10);
		glPopMatrix();
	}
	void Fall()
	{
		y -= speed;
		if (y <= -100)	{
			Init();
		}
	}
};

Snow snow[100];

void main(int argc, char *argv[])
{
	InitSnow();
	srand(unsigned int(time(NULL)));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Practice23");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(50, Timerfunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//GLfloat AmbientLight0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//GLfloat DiffuseLight0[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPos0[] = { 200, 0, 200 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	GLfloat lightPos2[] = { -200, 0, -200 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	GLfloat lightPos3[] = { 200, 0, -200 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

	GLfloat lightPos1[] = { -200, 0, 200 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	if (LIGHT0 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	if (LIGHT1 == true)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	if (LIGHT2 == true)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);

	if (LIGHT3 == true)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);

	glPushMatrix();


	glColor3f(1.0, 1.0, 0.0);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(200, -150, -200);
		glVertex3f(-200, -150, -200);
		glVertex3f(-200, -150, 200);
		glVertex3f(200, -150, 200);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();

	glRotatef(rotX1, 1, 0, 0);
	glRotatef(rotY1, 0, 1, 0);
	glRotatef(rotZ1, 0, 0, 1);

	glColor3f(1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(200, 0, 200);
	glutSolidCone(5, 5, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 0, -200);
	glutSolidCone(5, 5, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 0, -200);
	glutSolidCone(5, 5, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 0, 200);
	glutSolidCone(5, 5, 5, 5);
	glPopMatrix();

	//GLfloat AmbientLight1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//GLfloat DiffuseLight1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	//GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };

	glPopMatrix();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	{
		glTranslatef(0, 100, 0);
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(50, 0, 0);
		glEnd();
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 50, 0);
		glEnd();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 50);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(60, -150, 40);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(140, -150, 40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(60, -150, -40);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(60, -150, 40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(140, -150, 40);
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(140, -150, -40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(140, -150, -40);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(60, -150, -40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(100.0, -50.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			glRotatef(planetOneRotateAngle, 0, 1, 0);
			drawSolarSystem(PL_1);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(-140, -150, 40);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(-60, -150, 40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-140, -150, -40);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(-140, -150, 40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(-60, -150, 40);
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(-60, -150, -40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(-60, -150, -40);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-140, -150, -40);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-100, -50, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-100.0, -50.0, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			glRotatef(planetTwoRotateAngle, 0, 1, 0);
			drawSolarSystem(PL_2);
		}
		glPopMatrix();
	}
	glPopMatrix();


	for (int i = 0; i < 100; ++i)
	{
		snow[i].Draw();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w / h, 1.0, 1000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void Timerfunction(int value)
{
	planetOneAngle += 5;
	planetTwoAngle += 5;
	innerPlanetOneAngle += 15;
	innerPlanetTwoAngle += 15;

	/*if (anistate == zoomi)
	{
	zoom -= 10;
	if (zoom == 300)
	anistate = rotatestate;
	}

	if (anistate == rotatestate)
	{
	rotY += 10;
	if (rotY >= 400)
	{
	anistate = zoomo;
	}
	}

	if (anistate == zoomo)
	{
	rotY = 0;
	zoom += 10;
	if (zoom > 400)
	anistate = zoomi;
	}*/

	glutPostRedisplay();
	glutTimerFunc(50, Timerfunction, 1);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		rotX1 += 5;
		break;
	case 'w':
		rotX1 -= 5;
		break;
	case 'e':
		rotY1 += 5;
		break;
	case 'r':
		rotY1 -= 5;
		break;
	case 'x':
		rotX += 5;
		break;
	case 'X':
		rotX -= 5;
		break;
	case 'y':
		rotY += 5;
		break;
	case 'Y':
		rotY -= 5;
		break;
	case 'z':
		rotZ += 5;
		break;
	case 'Z':
		rotZ -= 5;
		break;
	case '+':
		zoom -= 10;
		break;
	case '-':
		zoom += 10;
		break;
	}

	//if (key == '1')
	//{
	//	if (LIGHT0)
	//	{
	//		LIGHT0 = false;
	//		glDisable(GL_LIGHT0);
	//	}
	//	else
	//	{
	//		LIGHT0 = true;
	//		glEnable(GL_LIGHT0);
	//	}
	//}
	if (key == 'A')
	{
		if (LIGHT0 == true)
			LIGHT0 = false;
		else
			LIGHT0 = true;

		if (LIGHT1 == true)
			LIGHT1 = false;
		else
			LIGHT1 = true;

		if (LIGHT2 == true)
			LIGHT2 = false;
		else
			LIGHT2 = true;

		if (LIGHT3 == true)
			LIGHT3 = false;
		else
			LIGHT3 = true;
	}
	//if (key == '2')
	//{
	//	if (LIGHT1 == true)
	//		LIGHT1 = false;
	//	else
	//		LIGHT1 = true;
	//}

	//if (key == '3')
	//{
	//	if (LIGHT2 == true)
	//		LIGHT2 = false;
	//	else
	//		LIGHT2 = true;
	//}

	//if (key == '4')
	//{
	//	if (LIGHT3 == true)
	//		LIGHT3 = false;
	//	else
	//		LIGHT3 = true;
	//}

	/*if (key == 'A')
	{
	for (int i = 0; i < 3; i++)
	{
	AmbientLight[i] += 0.1;
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	}
	}
	*/
	if (key == 'a')
	{
		for (int i = 0; i < 3; i++)
		{
			AmbientLight[i] -= 0.1;
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
		}
	}

	if (key == 'D')
	{
		for (int i = 0; i < 3; i++)
		{
			DiffuseLight[i] += 0.1;
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
		}
	}

	if (key == 'd')
	{
		for (int i = 0; i < 3; i++)
		{
			DiffuseLight[i] -= 0.1;
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
		}
	}

	if (key == 'S')
	{
		for (int i = 0; i < 3; i++)
		{
			SpecularLight[i] += 0.1;
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
		}
	}

	if (key == 's')
	{
		for (int i = 0; i < 3; i++)
		{
			SpecularLight[i] -= 0.1;
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
		}
	}

	if (key == 'N')
	{

	}

	glutPostRedisplay();
}

GLvoid drawSolarSystem(PLANET ePlanet)
{
	//행성
	switch (ePlanet)
	{
	case PL_1:
		glTranslatef(70 * cos(planetOneAngle*PI / 180), 0.0, 70 * sin(planetOneAngle*PI / 180));
		break;
	case PL_2:
		glTranslatef(70 * cos(planetTwoAngle*PI / 180), 0.0, 100 * sin(planetTwoAngle*PI / 180));
		break;
	}
	glutSolidSphere(35, 35, 35);

	//위성
	switch (ePlanet)
	{
	case PL_1:
		glColor3f(1.0, 0.5, 0.0);
		glTranslatef(50 * cos((innerPlanetOneAngle)*PI / 180), 0.0, 50 * sin((innerPlanetOneAngle)*PI / 180));
		break;
	case PL_2:
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(50 * cos((innerPlanetTwoAngle)*PI / 180), 0.0, 50 * sin((innerPlanetTwoAngle)*PI / 180));
		break;
	}
	glutSolidSphere(15, 15, 15);
}

GLvoid InitSnow()
{
	for (int i = 0; i < 100; i++){
		snow[i].Init();
	}
}

void GetNormal(GLfloat a[3], GLfloat b[3], GLfloat c[3], GLfloat normal[3])
{
	GLfloat ba[3];
	GLfloat ca[3];
	GLfloat n[3];

	// 두 정점간의 벡터 계산
	ba[0] = b[0] - a[0]; ba[1] = b[1] - a[1]; ba[2] = b[2] - a[2];
	ca[0] = c[0] - a[0]; ca[1] = c[1] - a[1]; ca[2] = c[2] - a[2];

	// 외적 구함
	n[0] = ba[1] * ca[2] - ca[1] * ba[2];
	n[1] = ca[0] * ba[2] - ba[0] * ca[2];
	n[2] = ba[0] * ca[1] - ca[0] * ba[1];

	// 정규화
	GLfloat l = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	normal[0] = n[0] / l; normal[1] = n[1] / l; normal[2] = n[2] / l;
}