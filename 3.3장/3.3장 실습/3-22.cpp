#include <gl/glut.h>
#include <iostream>
using namespace std;

typedef struct Rotate
{
	float fX;
	float fY;
	float fZ;
}Rotate;
Rotate Rotation;

float fX_Rotation = 10.f;
float fY_Rotation = 10.f;
float fZ_Rotation = 10.f;
float Circle_Sphere1_Y = 0.0f;
float fY_Circle1 = 5.f;
float fZoom = 500.0f;
float fPlus = 10.f;
float fLight_Y = 200.f;
float fLightPlus_Y = 10.f;
float fLight_Y2 = 200.f;
float fLightPlus_Y2 = 10.f;
/////////////////////////////////
float ambient_Light = 0.3f;
float diffuse_Light = 0.2f;
float specre_f = 0.2f;
float ambient_Plus = 0.1f;
float diffuseLight_Plus = 0.1f;
float specref_Plus = 0.1f;
bool Light1 = false;
bool Light2 = false;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunc(int value);
void Keyboard(unsigned char key, int x, int y);
void Ground();
void Triangle();
void Circle_Sphere1();
void Circle_Sphere2();


void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-22");
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
	gluLookAt(0.0, 200.0, fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);


	GLfloat diffuseLight[] = { diffuse_Light, diffuse_Light, diffuse_Light, 1.0f };
	GLfloat ambientLight[] = { ambient_Light, ambient_Light, ambient_Light, 1.0f };
	GLfloat specref[] = { specre_f, specre_f, specre_f, 1.0f };
	/////////////////////////////////////////////////////////
	/*GLfloat diffuseLight2[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat ambientLight2[] = { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat specref2[] = { 0.2f, 0.2f, 0.2f, 1.0f };*/


	glEnable(GL_LIGHTING);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
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
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);

	glShadeModel(GL_SMOOTH);

	glRotatef(Rotation.fX, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.fY, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.fZ, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslatef(200, 190, -60);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 190, -60);
	glutSolidCube(5);
	glPopMatrix();

	GLfloat lightPos[] = { 200, fLight_Y, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat lightPos2[] = { -200, fLight_Y2, 0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	

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
	else if (key == '1')
	{
		if (Light1 == true)
			Light1 = false;
		else
			Light1 = true;
	}
	else if (key == '2')
	{
		if (Light2 == true)
			Light2 = false;
		else
			Light2 = true;
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
	glTranslatef(0.f, -100.f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 0.f, 1.f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-25.f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 50.f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(25.f, 0.0f, 50.f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-25.f, 0.0f, 50.f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 100.f, 25.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-25.f, 0.0f, 50.f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-25.f, 0.0f, 0.f);
	glColor3f(0.0f, 0.0f, 1.0f);
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
