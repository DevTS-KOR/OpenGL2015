#include <gl/glut.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
float fRotate_X = 0;
float fRotate_Y = 0;
float fRotate_Z = 0;
float fAll_Rotate_Angle = 0.0f;

int iLeft_Draw = 0;
int iRight_Draw = 0;
float fLeft_Rotate_Vertex = 0.0f;
float fLeft_Rotate_Vertex2 = 0.0f;
float fLeft_Rotate_Vertex3 = 0.0f;
float fRight_Rotate_Vertex = 0.0f;
float fRight_Rotate_Vertex2 = 0.0f;
float fRight_Rotate_Vertex3 = 0.0f;
float fLeft_Rotate_X = 0.0f;
float fLeft_Rotate_Y = 0.0f;
float fLeft_Rotate_Z = 0.0f;
float fRight_Rotate_X = 0.0f;
float fRight_Rotate_Y = 0.0f;
float fRight_Rotate_Z = 0.0f;


void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-13");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);

	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(fAll_Rotate_Angle, fRotate_X, fRotate_Y, fRotate_Z);
	fAll_Rotate_Angle = 0.0f;
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.8f, 0.0f);
	glVertex3f(-200.0f, -200.0f, 100.f);
	glVertex3f(-200.0f, -100.0f, -100.f);
	glVertex3f(200.0f, -100.0f, -100.f);
	glVertex3f(200.0f, -200.0f, 100.f);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);
	glEnd();

	glPushMatrix();
	glLineWidth(1);
	if (iLeft_Draw == 1)
	{
		glColor3f(0.5f, 0.0f, 1.0f);
		glTranslatef(-100.0f, 0.0f, 0.0f);
		glRotatef(fLeft_Rotate_Vertex, fLeft_Rotate_X, 0.f, 0.f);
		glRotatef(fLeft_Rotate_Vertex2, 0.f, fLeft_Rotate_Y, 0.f);
		glRotatef(fLeft_Rotate_Vertex3, 0.f, 0.f, fLeft_Rotate_Z);
		glutSolidSphere(50.0f, 25.0f, 25.0f);
	}

	else if (iLeft_Draw == 2)
	{
		glColor3f(0.5f, 0.0f, 1.0f);
		glTranslatef(-100.0f, 0.0f, 0.0f);
		glRotatef(fLeft_Rotate_Vertex, fLeft_Rotate_X, 0.f, 0.f);
		glRotatef(fLeft_Rotate_Vertex2, 0.f, fLeft_Rotate_Y, 0.f);
		glRotatef(fLeft_Rotate_Vertex3, 0.f, 0.f, fLeft_Rotate_Z);
		glutSolidCube(50.0);
	}

	else if (iLeft_Draw == 3)
	{
		glColor3f(0.5f, 0.0f, 1.0f);
		glTranslatef(-100.0f, 0.0f, 0.0f);
		glRotatef(fLeft_Rotate_Vertex, fLeft_Rotate_X, 0.f, 0.f);
		glRotatef(fLeft_Rotate_Vertex2, 0.f, fLeft_Rotate_Y, 0.f);
		glRotatef(fLeft_Rotate_Vertex3, 0.f, 0.f, fLeft_Rotate_Z);
		glutSolidCone(50.0f, 100.0f, 25.0f, 25.0f);
	}

	else if (iLeft_Draw == 4)
	{
		glColor3f(0.5f, 0.0f, 1.0f);
		glTranslatef(-100.0f, 0.0f, 0.0f);
		glRotatef(fLeft_Rotate_Vertex, fLeft_Rotate_X, 0.f, 0.f);
		glRotatef(fLeft_Rotate_Vertex2, 0.f, fLeft_Rotate_Y, 0.f);
		glRotatef(fLeft_Rotate_Vertex3, 0.f, 0.f, fLeft_Rotate_Z);
		glutSolidTeapot(50.0f);
	}
	glPopMatrix();

	glPushMatrix();
	glLineWidth(1);
	if (iRight_Draw == 4)
	{
		glColor3f(0.0f, 0.5f, 1.0f);
		glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(fRight_Rotate_Vertex, fRight_Rotate_X, 0.f, 0.f);
		glRotatef(fRight_Rotate_Vertex2, 0.f, fRight_Rotate_Y, 0.f);
		glRotatef(fRight_Rotate_Vertex3, 0.f, 0.f, fRight_Rotate_Z);
		glutWireSphere(50.0f, 25.0f, 25.0f);
	}
	else if (iRight_Draw == 5)
	{
		glColor3f(0.0f, 0.5f, 1.0f);
		glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(fRight_Rotate_Vertex, fRight_Rotate_X, 0.f, 0.f);
		glRotatef(fRight_Rotate_Vertex2, 0.f, fRight_Rotate_Y, 0.f);
		glRotatef(fRight_Rotate_Vertex3, 0.f, 0.f, fRight_Rotate_Z);
		glutWireCube(50.0);
	}
	else if (iRight_Draw == 6)
	{
		glColor3f(0.0f, 0.5f, 1.0f);
		glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(fRight_Rotate_Vertex, fRight_Rotate_X, 0.f, 0.f);
		glRotatef(fRight_Rotate_Vertex2, 0.f, fRight_Rotate_Y, 0.f);
		glRotatef(fRight_Rotate_Vertex3, 0.f, 0.f, fRight_Rotate_Z);
		glutWireCone(50.0f, 100.0f, 25.0f, 25.0f);
	}

	else if (iRight_Draw == 7)
	{
		glColor3f(0.0f, 0.5f, 1.0f);
		glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(fRight_Rotate_Vertex, fRight_Rotate_X, 0.f, 0.f);
		glRotatef(fRight_Rotate_Vertex2, 0.f, fRight_Rotate_Y, 0.f);
		glRotatef(fRight_Rotate_Vertex3, 0.f, 0.f, fRight_Rotate_Z);
		glutWireTeapot(50.0f);
	}
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x' || key == 'X')
	{
		fRotate_X = 1.0f;
		fRotate_Y = 0.0f;
		fRotate_Z = 0.0f;
		fAll_Rotate_Angle = 5.0f;
	}

	else if (key == 'y' || key == 'Y')
	{
		fRotate_X = 0.0f;
		fRotate_Y = 1.0f;
		fRotate_Z = 0.0f;
		fAll_Rotate_Angle = 5.0f;
	}

	else if (key == 'z' || key == 'Z')
	{
		fRotate_X = 0.0f;
		fRotate_Y = 0.0f;
		fRotate_Z = 1.0f;
		fAll_Rotate_Angle = 5.0f;
	}

	if (key == 'a' || key == 'A')
	{
		fLeft_Rotate_X = 1.0f;
		fLeft_Rotate_Vertex += 5.0f;
	}

	else if (key == 's' || key == 'S')
	{
		fLeft_Rotate_Y = 1.0f;
		fLeft_Rotate_Vertex2 += 5.0f;
	}

	else if (key == 'd' || key == 'D')
	{
		fLeft_Rotate_Z = 1.0f;
		fLeft_Rotate_Vertex3 += 5.0f;
	}

	if (key == 'j' || key == 'J')
	{
		fRight_Rotate_X = 1.0f;
		fRight_Rotate_Vertex += 5.0f;
	}

	else if (key == 'k' || key == 'K')
	{
		fRight_Rotate_Y = 1.0f;
		fRight_Rotate_Vertex2 += 5.0f;
	}

	else if (key == 'l' || key == 'L')
	{
		fRight_Rotate_Z = 1.0f;
		fRight_Rotate_Vertex3 += 5.0f;
	}

	if (key == '1')
		iLeft_Draw = 1;

	else if (key == '2')
		iLeft_Draw = 2;

	else if (key == '3')
		iLeft_Draw = 3;

	else if (key == '4')
		iLeft_Draw = 4;

	if (key == '5')
		iRight_Draw = 4;

	else if (key == '6')
		iRight_Draw = 5;

	else if (key == '7')
		iRight_Draw = 6;

	else if (key == '8')
		iRight_Draw = 7;

	glutPostRedisplay();
}