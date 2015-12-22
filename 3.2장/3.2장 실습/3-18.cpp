#include <gl/glut.h>
#include <iostream>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void ground();
void First_Rect();
void Second_Rect();
void Third_Rect();
void Sphere();
void Crush();
float fRotate_X = 0.f;
float fRotate_Y = 0.f;
float fX = 0.f;
float fX_Move = 1.0f;
float fSphere_MoveX = 0.f;
float fSphere_MoveZ = 0.f;
float fSphere_RotateX = 0.f;
float fSphere_RotateZ = 0.f;
///////충돌체크를 위한 변수////////
//크레인의 중점과 반지름
float fCrane_CenterX = 0.f;
float fCrane_CenterY = 0.f;
float fCrane_CenterZ = 0.f;
float fCrane_Rad = 0.f;

//구의 중점과 반지름
float fSphere_CenterX = 0.f;
float fSphere_CenterY = 0.f;
float fSphere_CenterZ = 0.f;
float fSphere_Rad = 0.f;

//멈추게 하는 bool 변수
bool Move = true;
int iCount = 0;

//카메라회전, 줌인, 줌아웃 변수
float fTwist_Y = 0.f;
float fCamera = 500.f;
float fCamera_InOut = 0.f;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-18");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, fCamera + fCamera_InOut, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	glRotatef(fTwist_Y, 0.f, 1.0f, 0.f);

	ground();
	glPushMatrix();
	First_Rect();
	glPushMatrix();
	Second_Rect();
	glPushMatrix();
	Third_Rect();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	Sphere();
	glPopMatrix();

	Crush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (Move == true)
	{
		if (key == 'w')
		{
			fSphere_RotateX -= 10.f;
			fSphere_MoveZ -= 5.f;
		}
		else if (key == 's')
		{
			fSphere_RotateX += 10.f;
			fSphere_MoveZ += 5.f;
		}
		else if (key == 'a')
		{
			fSphere_RotateZ += 10.f;
			fSphere_MoveX -= 5.f;
		}
		else if (key == 'd')
		{
			fSphere_RotateZ -= 10.f;
			fSphere_MoveX += 5.f;
		}
	}

	if (key == '+')
		fCamera_InOut -= 5.f;

	else if (key == '-')
		fCamera_InOut += 5.f;

	else if (key == 'y' || key == 'Y')
		fTwist_Y += 10.f;

	glutPostRedisplay();
}

void ground()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-200.f, -100.f, 200.f);
	glVertex3f(-200.f, -100.f, -500.f);
	glVertex3f(200.f, -100.f, -500.f);
	glVertex3f(200.f, -100.f, 200.f);
	glEnd();
}

void First_Rect()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(fX, -75.0f, 100.f);
	glutSolidCube(50);
	if (Move == true)
		fCrane_CenterX += fX_Move;
	fCrane_CenterY = -75.f;
	fCrane_CenterZ = 100.f;
	fCrane_Rad = 25.f;			//각 모서리의 길이가 50이므로 반지름은 25 ???
}

void Second_Rect()
{
	glColor3f(0.f, 1.f, 0.f);
	glTranslatef(0.f, 45.f, 0.0f);
	glutWireCube(40);

}

void Third_Rect()
{
	glColor3f(0.f, 0.f, 1.f);
	glTranslatef(0.f, 40.f, 0.0f);
	glutWireCube(40);
}

void TimerFunction(int value)
{
	if (Move == true)
	{
		fX += fX_Move;

		if (fX == 150.f || fX == -150.f)
			fX_Move *= (-1);
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void Sphere()
{
	glColor3f(0.f, 0.f, 1.f);
	glTranslatef(0.f, -70.f, 0.f);
	glTranslatef(fSphere_MoveX, 0.f, fSphere_MoveZ);
	glRotatef(fSphere_RotateZ, 0.f, 0.f, 1.f);
	glRotatef(fSphere_RotateX, 1.f, 0.f, 0.f);
	glutSolidSphere(30, 25, 25);
	fSphere_CenterX = fSphere_MoveX;
	fSphere_CenterY = -70.f;
	fSphere_CenterZ = fSphere_MoveZ;
	fSphere_Rad = 30.f;
}

void Crush()
{
	float Vertex_to_Vertex = sqrt(((fSphere_CenterX - fCrane_CenterX) * (fSphere_CenterX - fCrane_CenterX))
								/*+ ((fSphere_CenterY - fCrane_CenterY) * (fSphere_CenterY - fCrane_CenterY))*/
								+ ((fSphere_CenterZ - fCrane_CenterZ) * (fSphere_CenterZ - fCrane_CenterZ)));

	float Rad_to_Rad = fCrane_Rad + fSphere_Rad;

	if (Vertex_to_Vertex == Rad_to_Rad || Vertex_to_Vertex < Rad_to_Rad)
	{
		Move = false;
		if (iCount == 0)
		{
			cout << "충돌발생! " << endl << "점과 점사이의 거리 : " << Vertex_to_Vertex << "이며 반지름과 반지름사이의 거리 : " << Rad_to_Rad
				<< endl << " 따라서 충돌조건 만족!" << endl;
			cout << "사각형의 x, y, z좌표 : " << fCrane_CenterX << ", " << fCrane_CenterY << ", " << fCrane_CenterZ << endl;
			cout << "구의	 x, y, z좌표 : " << fSphere_CenterX << ", " << fSphere_CenterY << ", " << fSphere_CenterZ << endl;
		}
		iCount++;
	}

	
}
