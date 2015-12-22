#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <random>
#include <windows.h>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void mouseMovement(int x, int y);
void camera(void);

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;

float lastx, lasty;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("3D 윈도우");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glEnable(GL_DEPTH_TEST);

	//ShowCursor(FALSE);
	glLoadIdentity();
	//gluLookAt(xpos, 0.0f, zpos, 0.0, 0.0, -1000.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0f, 0.0f, -200.f);

	//1인칭 카메라 함수
	camera();

	//총을 그려주는 사각형들
	/*glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(100.f, -200.f, 0.0f);
	glVertex3f(100.f, -200.f, 0.0f);
	glVertex3f(300.f, 0.f, -100.f);
	glVertex3f(300.f, 0.f, -100.f);
	glEnd();
	glPopMatrix();*/

	//움직임 확인 육면체
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -200.f);
	glutSolidCube(50);
	glTranslatef(0.0f, -25.f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, 25.f, 200.0f);
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
	gluPerspective(60.0, w / h, 1.0, 1000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		xrot += 1;
		if (xrot > 360) xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}


	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad)) * 3;
		zpos -= float(cos(yrotrad)) * 3;
		//ypos -= float(sin(xrotrad)) * 5;
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad)) * 3;
		zpos += float(cos(yrotrad)) * 3;
		//ypos += float(sin(xrotrad)) * 5;
	}

	if (key == 'd')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad)) * 3;
		zpos += float(sin(yrotrad)) * 3;
	}

	if (key == 'a')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 3;
		zpos -= float(sin(yrotrad)) * 3;
	}

	if (key == 27)
	{
		exit(0);
	}

	if (key == '1')
		glutFullScreen();

	else if (key == '2')
		glutReshapeWindow(800, 800);

	glutPostRedisplay();

}


void mouseMovement(int x, int y)
{
	int diffx = x - lastx; //check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += (float)diffy; //set the xrot to xrot with the additionof the difference in the y position
	yrot += (float)diffx;    //set the xrot to yrot with the additionof the difference in the x position


	glutPostRedisplay();
}

void camera(void) 
{

	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-xpos, 0.0, -zpos); //translate the screento the position of our camera
}