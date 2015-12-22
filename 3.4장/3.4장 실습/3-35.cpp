#include <gl/glut.h>

#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
double randomDouble(void);


float fBlend1[9];
float fBlend2[9];
float fBlend3[9];

float fX[5];
float fY[5];
float fMove_X = 0;
float fMove_Y = 0;
bool blending[9];

void main()
{
	//초기화 함수들
	fX[0] = 300.f;	fX[1] = 600.f;	fX[2] = 600.f;	fX[3] = 300.f;	fX[4] = 300.f;
	fY[0] = 400.f;	fY[1] = 400.f;	fY[2] = 200.f;	fY[3] = 200.f;	fY[4] = 400.f;

	for (int i = 0; i < 9; i++)
	{
		fBlend1[i] = randomDouble();
		fBlend2[i] = randomDouble();
		fBlend3[i] = randomDouble();
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 600);
	glutCreateWindow("3-35");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1000.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	if (fX[0] == 0 && fY[0] == 600)
	{
		for (int i = 0; i < 9; i++)
		{
			blending[i] = false;
			blending[0] = true;
		}
	}

	if (fMove_X == -300.f && fMove_Y == 200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[0] = true;

	}
	else if (fMove_X == 0.f && fMove_Y == 200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[1] = true;
	}
	else if (fMove_X == 300.f && fMove_Y == 200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[2] = true;
	}
	else if (fMove_X == -300.f && fMove_Y == 0)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[3] = true;
	}
	else if (fMove_X == 0.f && fMove_Y == 0)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[4] = true;
	}
	else if (fMove_X == 300.f && fMove_Y == 0)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[5] = true;
	}
	else if (fMove_X == -300.f && fMove_Y == -200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[6] = true;
	}
	else if (fMove_X == 0.f && fMove_Y == -200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[7] = true;
	}
	else if (fMove_X == 300.f && fMove_Y == -200)
	{
		for (int i = 0; i < 9; i++)
			blending[i] = false;
		blending[8] = true;
	}
		
	//1
	glPushMatrix();
	glTranslatef(-300.f, 200.0f, 0.0f);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend1[0]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend2[0]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend3[0]);
	glutSolidTeapot(50);
	glTranslatef(300.f, -200.0f, 0.0f);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(0.f, 200.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend1[1]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend2[1]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend3[1]);
	glutSolidSphere(50, 30, 30);
	glTranslatef(0.f, -200.0f, 0.0f);
	glPopMatrix();

	//3
	glPushMatrix();
	glTranslatef(300.f, 200.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend1[2]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend2[2]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend3[2]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-300.f, -200.0f, 0.0f);
	glPopMatrix();

	//4
	glPushMatrix();
	glTranslatef(-300.f, 0.0f, 0.0f);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend1[3]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend2[3]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend3[3]);
	glutSolidTeapot(50);
	glTranslatef(300.f, 0.0f, 0.0f);
	glPopMatrix();


	//5
	glPushMatrix();
	glTranslatef(0.f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend1[4]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend2[4]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend3[4]);
	glutSolidSphere(50, 30, 30);
	glTranslatef(0.f, 0.0f, 0.0f);
	glPopMatrix();

	//6
	glPushMatrix();
	glTranslatef(300.f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend1[5]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend2[5]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend3[5]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-300.f, 0.0f, 0.0f);
	glPopMatrix();

	//7
	glPushMatrix();
	glTranslatef(-300.f, -200.0f, 0.0f);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend1[6]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend2[6]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend3[6]);
	glutSolidTeapot(50);
	glTranslatef(300.f, 200.0f, 0.0f);
	glPopMatrix();

	//8
	glPushMatrix();
	glTranslatef(0.f, -200.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend1[7]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend2[7]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend3[7]);
	glutSolidSphere(50, 30, 30);
	glTranslatef(0.f, 200.0f, 0.0f);
	glPopMatrix();

	//9
	glPushMatrix();
	glTranslatef(300.f, -200.0f, 0.0f);
	glColor4f(1.0f, 0.0f, 0.0f, fBlend1[8]);
	glutSolidTeapot(50);
	glColor4f(0.0f, 0.0f, 1.0f, fBlend2[8]);
	glutSolidSphere(50, 30, 30);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, fBlend3[8]);
	glutSolidCone(100, 75, 75, 75);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-300.f, 200.0f, 0.0f);
	glPopMatrix();

	///////////glTrans의 값을 바꾼다..
	glPushMatrix();
	glTranslatef(-450.f, -300.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 5; i++)
		glVertex3f(fX[i] + fMove_X, fY[i] + fMove_Y, 0);
	glEnd();
	glTranslatef(450.f, 300.0f, 0.0f);
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
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend1[i] -= 0.1f;
			}
		}
	}
	else if (key == '2')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend1[i] += 0.1f;
			}
		}
	}
	else if (key == '3')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend2[i] -= 0.1f;
			}
		}
	}
	else if (key == '4')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend2[i] += 0.1f;
			}
		}
	}
	else if (key == '5')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend3[i] -= 0.1f;
			}
		}
	}
	else if (key == '6')
	{
		for (int i = 0; i < 9; i++)
		{
			if (blending[i] == true)
			{
				fBlend3[i] += 0.1f;
			}
		}
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		fMove_X -= 300.f;
		
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		fMove_X += 300.f;

	}

	else if (key == GLUT_KEY_UP)
	{
		fMove_Y += 200.f;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		fMove_Y -= 200.f;
	}

	glutPostRedisplay();
}

double randomDouble(void) 
{
	return (double)rand() / RAND_MAX;
}