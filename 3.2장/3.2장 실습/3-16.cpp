#include <gl/glut.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Ground();
void WireSphere();
void Sphere_Translate();
void Sphere_Rotate();
float fX;
float fY;
float fZ;
float fAngle_X = 0.0f;
float fAngle_Y = 0.0f;
float fAngle_Z = 0.0f;
float fX_Rotate = 0.0f;
float fZ_Rotate = 0.0f;
float fZoom = 0.0f;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-16");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 500.0f + fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	Ground();

	glPushMatrix();
	glTranslatef(0.0f, -50.0f, 0.0);
	Sphere_Translate();
	Sphere_Rotate();
	WireSphere();
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

void Ground(void)
{
	glColor3f(0.9f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-200.0f, -100.0f, 300.0f);
	glVertex3f(-200.0f, -100.0f, -300.0f);
	glVertex3f(200.0f, -100.0f, -300.0f);
	glVertex3f(200.0f, -100.0f, 300.0f);
	glEnd();
}

void WireSphere()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireSphere(50.0, 25.0, 25.0);
}

void Sphere_Translate()
{
	glTranslatef(fX, 0.0f, fZ);
}

void Sphere_Rotate()
{
	glRotatef(fAngle_X, 0.0f, 0.0f, 1.0f);
	glRotatef(fAngle_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(fAngle_Z, 1.0f, 0.0f, 0.0f);
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'X')
	{
		if (fX == 180.0f)
			fX = 180.0f;
		else
			fX += 5.0f;
		fAngle_X -= 5.0f;
	}
	else if (key == 'x')
	{
		if (fX == -180.0f)
			fX = -180.0f;
		else
			fX -= 5.0f;
		fAngle_X += 5.0f;
	}

	else if (key == 'y')
	{
		fAngle_Y += 5.0f;
	}

	else if (key == 'Y')
	{
		fAngle_Y -= 5.0f;
	}

	else if (key == 'z')
	{
		if (fZ == -300.0f)
			fZ = -300.0f;
		else
			fZ -= 5.0f;
		fAngle_Z -= 5.0f;
	}

	else if (key == 'Z')
	{
		if (fZ == 300.0f)
			fZ = 300.0f;
		else
			fZ += 5.0f;
		fAngle_Z += 5.0f;
	}

	else if (key == '+')
		fZoom -= 10.0f;

	else if (key == '-')
		fZoom += 10.0f;

	else if (key == 'i')
	{
		fZoom = 0;
		fX = 0.0f;
		fZ = 0.0f;
		fAngle_X = 0.0f;
		fAngle_Y = 0.0f;
		fAngle_Z = 0.0f;
	}

	glutPostRedisplay();
}

