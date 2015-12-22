#include <gl/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

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
void Player();

float Player_X = 0.f;
float Player_Y = 25.f;
float Player_Z = 500.f;
float Player_Plus_X = 18.75f;
float Player_Plus_Y = 10.f;
float Player_Plus_Z = -6.25f;
float Player_Move_X = 5.f;
float Player_Rotate = 0.0f;
float Player_Rotate_Z = 45.f;
float Player_Down_Y = -5.f;
float Right_X = 0.f;
float Right_Y = 25.0f;
float Right_Z = 500.0f;

bool bX_Right = false;
bool bX_Left = false;
bool bX_Down = false;
bool bJump = false;
int iCount = 0;
int aaa = 0;

float fAmbient_Light = 0.3f;
float fAmbient_Light2 = 0.3f;
float fAmbient_Light3 = 0.3f;
float fDiffuse_Light = 0.2f;
float fDiffuse_Light2 = 0.2f;
float fDiffuse_Light3 = 0.2f;
float fSpecre_f = 0.2f;


void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-26");
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
	gluLookAt(0.0, 0.0, 800.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);


	glPushMatrix();

	/*glTranslatef(Right_X, Right_Y, Right_Z);
	glRotatef(Player_Rotate, 0.0f, 0.0f, 1.0f);

	GLfloat diffuseLight[] = { fDiffuse_Light, fDiffuse_Light, fDiffuse_Light, 1.0f };
	GLfloat ambientLight[] = { fAmbient_Light, fAmbient_Light, fAmbient_Light, 1.0f };
	GLfloat specref[] = { fSpecre_f, fSpecre_f, fSpecre_f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { Right_X, Right_Y + 40.f, Right_Z, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);*/
	glPopMatrix();


	glPushMatrix();


	Road();

	Player();
	glPopMatrix();

	glPushMatrix();
	//Player();
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

void Road()
{
	glTranslatef(0.0f, 200.f, 0.0f);
	glRotatef(30.f, 1.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 0.3f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 1.0f, 0.0f);
	glVertex3f(50.f, 1.0f, 0.0f);
	glVertex3f(50.f, 1.0f, 600.f);
	glVertex3f(-50.f, 1.0f, 600.f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-200.f, 1.0f, 0.0f);
	glVertex3f(-100.f, 1.0f, 0.0f);
	glVertex3f(-100.f, 1.0f, 600.f);
	glVertex3f(-200.f, 1.0f, 600.f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(100.f, 1.0f, 0.0f);
	glVertex3f(200.f, 1.0f, 0.0f);
	glVertex3f(200.f, 1.0f, 600.f);
	glVertex3f(100.f, 1.0f, 600.f);
	glEnd();
}

void Player()
{

	glTranslatef(Player_X, Player_Y, Player_Z);
	glRotatef(Player_Rotate, 0.0f, 0.0f, 1.0f);

	cout << "1 : " << Player_Y << endl;

	if (bJump == true && aaa == 0)
	{
		aaa++;
		fDiffuse_Light = randomDouble();
		fDiffuse_Light2 = randomDouble();
		fDiffuse_Light3 = randomDouble();
		fAmbient_Light = randomDouble();
		fAmbient_Light2 = randomDouble();
		fAmbient_Light3 = randomDouble();
	}
		

	GLfloat diffuseLight[] = { fDiffuse_Light, fDiffuse_Light2, fDiffuse_Light3, 1.0f };
	GLfloat ambientLight[] = { fAmbient_Light, fAmbient_Light2, fAmbient_Light3, 1.0f };
	GLfloat specref[] = { fSpecre_f, fSpecre_f, fSpecre_f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { Player_X, Player_Y + 200.f, Player_Z, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	cout << "2 : " << Player_Y << endl;
	if (bX_Down == true && bJump == false)
		glTranslatef(0, Player_Y, 0);

	glColor3f(0.0f, 0.5f, 0.5f);
	glutSolidSphere(25, 25, 25);
	//glutSolidCube(50);

}

void Keyboard(unsigned char key, int x, int y)
{
	bX_Right = false;
	bX_Left = false;

	if (key == 'd')
	{
		bX_Right = true;
		bJump = true;
		

		//Player_X += Player_Plus_X;
		//Player_Z += Player_Plus_Z;

		if (Player_Z <= 100.f)
			Player_Plus_Z *= -1;
		else if (Player_Z >= 550.f)
			Player_Plus_Z *= -1;

	}
	else if (key == 'a')
	{

		bX_Left = true;
		bJump = true;
		
		//Player_X -= Player_Plus_X;
		//Player_Z += Player_Plus_Z;

		if (Player_Z <= 100.f)
			Player_Plus_Z *= -1;
		else if (Player_Z >= 550.f)
			Player_Plus_Z *= -1;
	}

	else if (key == 'Z')
	{
		fAmbient_Light += 0.1f;
		fAmbient_Light2 += 0.1f;
		fAmbient_Light3 += 0.1f;
	}
	else if (key == 'z')
	{
		fAmbient_Light -= 0.1f;
		fAmbient_Light2 -= 0.1f;
		fAmbient_Light3 -= 0.1f;
	}
	else if (key == 'X')
	{
		fDiffuse_Light += 0.1f;
		fDiffuse_Light2 += 0.1f;
		fDiffuse_Light3 += 0.1f;
	}
	else if (key == 'x')
	{
		fDiffuse_Light -= 0.1f;
		fDiffuse_Light2 -= 0.1f;
		fDiffuse_Light3 -= 0.1f;
	}
	else if (key == 'C')
	{
		fSpecre_f += 0.1f;
	}
	else if (key == 'c')
	{
		fSpecre_f -= 0.1f;
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		Player_X -= Player_Move_X;
		Right_X -= Player_Move_X;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		Player_X += Player_Move_X;
		Right_X += Player_Move_X;
	}

	glutPostRedisplay();

}

void TimerFunc(int value)
{
	if (bX_Right == true && iCount <= 8)
	{
		Player_X += Player_Plus_X;
		Player_Y += Player_Plus_Y;
		Player_Z += Player_Plus_Z;
		Right_X += Player_Plus_X;
		Right_Y += Player_Plus_Y;
		Right_Z += Player_Plus_Z;
		Player_Rotate += Player_Rotate_Z;

		if (Player_Y == 65.f)
			Player_Plus_Y *= -1;

		iCount++;
		if (iCount == 8)
		{
			iCount = 0;
			Player_Plus_Y *= -1;
			bX_Right = false;
			bJump = false;
		}
	}

	if (bX_Left == true && iCount <= 8)
	{
		Player_X -= Player_Plus_X;
		Player_Y += Player_Plus_Y;
		Player_Z += Player_Plus_Z;
		Right_X -= Player_Plus_X;
		Right_Y += Player_Plus_Y;
		Right_Z += Player_Plus_Z;
		Player_Rotate += Player_Rotate_Z;

		if (Player_Y == 65.f)
			Player_Plus_Y *= -1;

		iCount++;
		if (iCount == 8)
		{
			iCount = 0;
			Player_Plus_Y *= -1;
			bX_Left = false;
			bJump = false;
			aaa = 0;
		}
	}

	if (bJump == false)
		if (Player_X >= 200 || (Player_X >= 50 && Player_X <= 100) || (Player_X <= -50 && Player_X >= -100) || Player_X <= -200)
		{
			bX_Down = true;
			Player_Y += Player_Down_Y;
			Right_Y += Player_Down_Y;
		}
		else
			bX_Down = false;


	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}