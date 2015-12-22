#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#define PI 3.141592

typedef struct  
{
	float fX;
	float fY;
}strZigzag, strMouse;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerLine(int value);
void TimerTornado(int value);
void TimerZigzag(int value);
void TimerMouse(int value);
void Mouse(int button, int state, int x, int y);

/////////////////////////
bool bChange = false;

bool bTriangle = false;
float fLine_Triangle_X;
float fLine_Triangle_Y;
float fLine_Triangle_Move = 0.0f;

bool bLine = false;
float fLine_Start_X = -0.5f;
float fLine_Start_Y = 0.5f;
float fLine_End_X = 0.5f;
float fLine_End_Y = -0.5f;
////////////////////////
bool bTornado = false;
bool bTriangle2 = false;
float fTornado_X[100];
float fTornado_Y[100];
float fAngle = 0.0f;
float fDistance = 0.0f;
float fTornado_Triangle_X;
float fTornado_Triangle_Y;
int iCount = 0;
int iCount_Count = 1;
float fTornado_Triangle_Move_X[100];
float fTornado_Triangle_Move_Y[100];
/////////////////////////
bool bZigzag = false;
bool bTriangle3 = false;
int iPosition = 0;
float fZigzag_Triangle_Move_X = 0.0f;
float fZigzag_Triangle_Move_Y = 0.0f;
strZigzag _strZigzag[6];
float fZigzag_Triangle_X;
float fZigzag_Triangle_Y;
bool bPosition1 = false;
bool bPosition2 = false;
bool bPosition3 = false;
bool bPosition4 = false;
////////////////////////////////
bool bMouse = false;
bool bMouse_Render = false;
bool bTriangle4 = false;
strMouse _strMouse[5];
int iClick_Count = 0;
float fMouse_Triangle_X;
float fMouse_Triangle_Y;
float fMouse_Triangle_Move_X = 0.0f;
float fMouse_Triangle_Move_Y = 0.0f;
int Mouse_Count = 0;
int Mouse_Move = 0;


void main()
{
	fLine_Triangle_X = fLine_Start_X;
	fLine_Triangle_Y = fLine_Start_Y;

	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-12");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (bLine == true)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(fLine_Start_X, fLine_Start_Y);
		glVertex2f(fLine_End_X, fLine_End_Y);
		glEnd();
	}

	if (bTornado == true)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; i++)
		{
			fTornado_X[i] = sin(fAngle * PI) * fDistance;
			fTornado_Y[i] = cos(fAngle * PI) * fDistance;
			fTornado_Triangle_Move_X[i] = fTornado_X[i];
			fTornado_Triangle_Move_Y[i] = fTornado_Y[i];
			glVertex2f(fTornado_X[i], fTornado_Y[i]);
			fAngle += 0.05f;
			fDistance += 0.005f;
			if (i == 99)
			{
				fAngle = 0.0f;
				fDistance = 0.0f;
			}
		}
		fTornado_Triangle_X = fTornado_X[0];
		fTornado_Triangle_Y = fTornado_Y[0];
		glEnd();

	}

	if (bTornado == false)
	{
		for (int i = 0; i < 100; i++)
		{
			fTornado_X[i] = 0;
			fTornado_Y[i] = 0;
		}
		fAngle = 0.0f;
		fDistance = 0.0f;
	}

	if (bZigzag == true)
	{
		_strZigzag[0].fX = -0.5f;
		_strZigzag[0].fY = 0.5f;
		_strZigzag[1].fX = 0.5f;
		_strZigzag[1].fY = 0.5f;
		_strZigzag[2].fX = 0.5f;
		_strZigzag[2].fY = 0.0f;
		_strZigzag[3].fX = -0.5f;
		_strZigzag[3].fY = 0.0f;
		_strZigzag[4].fX = -0.5f;
		_strZigzag[4].fY = -0.5f;
		_strZigzag[5].fX = 0.5f;
		_strZigzag[5].fY = -0.5f;
		fZigzag_Triangle_X = _strZigzag[0].fX;
		fZigzag_Triangle_Y = _strZigzag[0].fY;
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 6; i++)
			glVertex2f(_strZigzag[i].fX, _strZigzag[i].fY);
		glEnd();

	}

	if (bMouse == true && bMouse_Render == true)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 5; i++)
			glVertex2f(_strMouse[i].fX, _strMouse[i].fY);
	

		glEnd();
	}

	glPushMatrix();
	if (bTriangle == true && bLine == true)
	{
		glTranslatef(fLine_Triangle_Move, -fLine_Triangle_Move, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(fLine_Triangle_X, fLine_Triangle_Y + 0.2f);
		glVertex2f(fLine_Triangle_X + 0.2f, fLine_Triangle_Y - 0.1f);
		glVertex2f(fLine_Triangle_X - 0.2f, fLine_Triangle_Y - 0.1f);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	if (bTriangle2 == true && bTornado == true)
	{
		glTranslatef(fTornado_Triangle_Move_X[iCount], fTornado_Triangle_Move_Y[iCount], 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(fTornado_Triangle_X, fTornado_Triangle_Y + 0.2f);
		glVertex2f(fTornado_Triangle_X + 0.2f, fTornado_Triangle_Y - 0.1f);
		glVertex2f(fTornado_Triangle_X - 0.2f, fTornado_Triangle_Y - 0.1f);

		iCount += iCount_Count;

		if (iCount >= 99 || iCount <= 0)
			iCount_Count *= -1;

		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	if (bTriangle3 == true && bZigzag == true)
	{
		glTranslatef(fZigzag_Triangle_Move_X, fZigzag_Triangle_Move_Y, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(fZigzag_Triangle_X, fZigzag_Triangle_Y + 0.2f);
		glVertex2f(fZigzag_Triangle_X + 0.2f, fZigzag_Triangle_Y - 0.1f);
		glVertex2f(fZigzag_Triangle_X - 0.2f, fZigzag_Triangle_Y -0.1f);
		glEnd();
	}
	glPopMatrix();
	if (bTriangle4 == true && bMouse == true)
	{
		//glTranslatef(fMouse_Triangle_Move_X, fMouse_Triangle_Move_Y, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		printf("좌표변환 값 : %f, %f\n", fMouse_Triangle_X, fMouse_Triangle_Y);
		glVertex2f(fMouse_Triangle_X, fMouse_Triangle_Y + 0.2f);
		glVertex2f(fMouse_Triangle_X + 0.2f, fMouse_Triangle_Y - 0.1f);
		glVertex2f(fMouse_Triangle_X - 0.2f, fMouse_Triangle_Y - 0.1f);
		glEnd();
	}
	glPushMatrix();
	glPopMatrix();


	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '7')
	{
		if (bTriangle == true)
			bTriangle = false;
		else
			bTriangle = true;
		
		glutTimerFunc(100, TimerLine, 1);
	}

	if (key == '8')
	{
		if (bTriangle2 == true)
			bTriangle2 = false;
		else
			bTriangle2 = true;

		glutTimerFunc(100, TimerTornado, 2);
	}

	if (key == '9')
	{
		if (bTriangle3 == true)
			bTriangle3 = false;
		else
			bTriangle3 = true;

		glutTimerFunc(100, TimerZigzag, 3);
	}

	if (key == '0')
	{
		if (bTriangle4 == true)
			bTriangle4 = false;
		else
			bTriangle4 = true;

		glutTimerFunc(100, TimerMouse, 4);
	}

	if (key == '1')
	{
		if (bLine == true)
			bLine = false;
		else
		{
			bTornado = false;
			bZigzag = false;
			bMouse = false;
			bLine = true;
		}
	}


	if (key == '2')
	{
		if (bTornado == true)
			bTornado = false;
		else
		{
			bLine = false;
			bZigzag = false;
			bMouse = false;
			bTornado = true;
		}
		
	}

	if (key == '3')
	{
		if (bZigzag == true)
			bZigzag = false;
		else
		{
			bLine = false;
			bTornado = false;
			bMouse = false;
			bZigzag = true;
		}
	}

	if (key == '4')
	{
		if (bMouse == true)
			bMouse = false;
		else
		{
			bLine = false;
			bTornado = false;
			bZigzag = false;
			bMouse = true;
		}
	}

	glutPostRedisplay();
}

void TimerLine(int value)
{

	if (bChange == false)
		fLine_Triangle_Move += 0.05f;

	else if (bChange == true)
		fLine_Triangle_Move -= 0.05f;

	if (fLine_Triangle_Move >= 1.0f)
	{
		bChange = true;
	}

	else if (fLine_Triangle_Move <= 0.0f)
	{
		bChange = false;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerLine, 1);
}

void TimerTornado(int value)
{

	glutPostRedisplay();
	glutTimerFunc(100, TimerTornado, 2);
}

void TimerZigzag(int value)
{
	if (fZigzag_Triangle_Move_X >= 1.0f)
		iPosition = 1;

	if (fZigzag_Triangle_Move_Y <= -0.5f && bPosition1 == false)
		iPosition = 2;

	if (fZigzag_Triangle_Move_X <= 0.0f && iPosition == 2)
		iPosition = 3;

	if (fZigzag_Triangle_Move_Y <= -1.0f && bPosition1 == false)
		iPosition = 4;

	if (fZigzag_Triangle_Move_X >= 1.0f && iPosition == 4)
		iPosition = 5;

	if (fZigzag_Triangle_Move_X <= 0.0f && bPosition1 == true)
		iPosition = 6;

	if (fZigzag_Triangle_Move_Y >= -0.5f && bPosition2 == true)
		iPosition = 7;

	if (fZigzag_Triangle_Move_X >= 1.0f && bPosition3 == true)
		iPosition = 8;

	if (fZigzag_Triangle_Move_Y >= 0.0f && bPosition4 == true)
		iPosition = 9;

	if (iPosition == 0)
	{
		fZigzag_Triangle_Move_X += 0.05f;
	}

	else if (iPosition == 1)
	{
		fZigzag_Triangle_Move_X = 1.0f;
		fZigzag_Triangle_Move_Y -= 0.05f;
	}

	else if (iPosition == 2)
	{
		fZigzag_Triangle_Move_Y = -0.5f;
		fZigzag_Triangle_Move_X -= 0.05f;
	}

	else if (iPosition == 3)
	{
		fZigzag_Triangle_Move_X = 0.0f;
		fZigzag_Triangle_Move_Y -= 0.05f;
	}

	else if (iPosition == 4)
	{
		fZigzag_Triangle_Move_Y = -1.0f;
		fZigzag_Triangle_Move_X += 0.05f;
	}

	else if (iPosition == 5)
	{
		bPosition1 = true;
		fZigzag_Triangle_Move_Y = -1.0f;
		fZigzag_Triangle_Move_X -= 0.05f;
	}

	else if (iPosition == 6)
	{
		bPosition2 = true;
		fZigzag_Triangle_Move_X = 0.0f;
		fZigzag_Triangle_Move_Y += 0.05f;
	}

	else if (iPosition == 7)
	{
		bPosition3 = true;
		fZigzag_Triangle_Move_Y = -0.5f;
		fZigzag_Triangle_Move_X += 0.05f;
	}

	else if (iPosition == 8)
	{
		bPosition4 = true;
		fZigzag_Triangle_Move_X = 1.0f;
		fZigzag_Triangle_Move_Y += 0.05f;
	}

	else if (iPosition == 9)
	{
		fZigzag_Triangle_Move_Y = 0.0f;
		fZigzag_Triangle_Move_X -= 0.05f;

		if (fZigzag_Triangle_Move_X <= 0.0f)
		{
			iPosition = 0;
			bPosition1 = false;
			bPosition2 = false;
			bPosition3 = false;
			bPosition4 = false;
		}
	
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerZigzag, 3);
}


void TimerMouse(int value)
{
	float aX = _strMouse[1].fX - _strMouse[0].fX;
	float aY = _strMouse[1].fY - _strMouse[0].fY;
	float bX = _strMouse[2].fX - _strMouse[1].fX;
	float bY = _strMouse[2].fY - _strMouse[1].fY;
	float cX = _strMouse[3].fX - _strMouse[2].fX;
	float cY = _strMouse[3].fY - _strMouse[2].fY;
	float dX = _strMouse[4].fX - _strMouse[3].fX;
	float dY = _strMouse[4].fY - _strMouse[3].fY;

	//////////////////////////////////////////////////

	if (Mouse_Count == 0)
	{
		if (_strMouse[1].fX < _strMouse[0].fX)
			aX = _strMouse[0].fX - _strMouse[1].fX;

		if (_strMouse[1].fY < _strMouse[0].fY)
			aY = _strMouse[0].fY - _strMouse[1].fY;

		if (fMouse_Triangle_X <= _strMouse[1].fX)
			fMouse_Triangle_X += aX / 50.f;
		else
			fMouse_Triangle_X -= aX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[1].fY)
			fMouse_Triangle_Y += aY / 50.f;
		else
			fMouse_Triangle_Y -= aY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[1].fX;
			fMouse_Triangle_Y = _strMouse[1].fY;
		}

		if (fMouse_Triangle_X == _strMouse[1].fX && fMouse_Triangle_Y == _strMouse[1].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 1;
		}

	}
	//////
	if (Mouse_Count == 1)
	{
		if (_strMouse[2].fX < _strMouse[1].fX)
			bX = _strMouse[1].fX - _strMouse[2].fX;

		if (_strMouse[2].fY < _strMouse[1].fY)
			bY = _strMouse[1].fY - _strMouse[2].fY;

		if (fMouse_Triangle_X <= _strMouse[2].fX)
			fMouse_Triangle_X += bX / 50.f;
		else
			fMouse_Triangle_X -= bX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[2].fY)
			fMouse_Triangle_Y += bY / 50.f;
		else
			fMouse_Triangle_Y -= bY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[2].fX;
			fMouse_Triangle_Y = _strMouse[2].fY;
		}
		if (fMouse_Triangle_X == _strMouse[2].fX && fMouse_Triangle_Y == _strMouse[2].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 2;
		}
	}

	if (Mouse_Count == 2)
	{
		if (_strMouse[3].fX < _strMouse[2].fX)
			cX = _strMouse[2].fX - _strMouse[3].fX;

		if (_strMouse[3].fY < _strMouse[2].fY)
			cY = _strMouse[2].fY - _strMouse[3].fY;

		if (fMouse_Triangle_X <= _strMouse[3].fX)
			fMouse_Triangle_X += cX / 50.f;
		else
			fMouse_Triangle_X -= cX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[3].fY)
			fMouse_Triangle_Y += cY / 50.f;
		else
			fMouse_Triangle_Y -= cY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[3].fX;
			fMouse_Triangle_Y = _strMouse[3].fY;
		}
		if (fMouse_Triangle_X == _strMouse[3].fX && fMouse_Triangle_Y == _strMouse[3].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 3;
		}

	}

	if (Mouse_Count == 3)
	{

		if (_strMouse[4].fX < _strMouse[3].fX)
			dX = _strMouse[3].fX - _strMouse[4].fX;

		if (_strMouse[4].fY < _strMouse[3].fY)
			dY = _strMouse[3].fY - _strMouse[4].fY;

		if (fMouse_Triangle_X <= _strMouse[4].fX)
			fMouse_Triangle_X += dX / 50.f;

		else
			fMouse_Triangle_X -= dX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[4].fY)
			fMouse_Triangle_Y += dY / 50.f;
		else
			fMouse_Triangle_Y -= dY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[4].fX;
			fMouse_Triangle_Y = _strMouse[4].fY;
		}
		if (fMouse_Triangle_X == _strMouse[4].fX && fMouse_Triangle_Y == _strMouse[4].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 4;
		}
	}

	if (Mouse_Count == 4)
	{
		if (_strMouse[4].fX < _strMouse[3].fX)
			dX = _strMouse[3].fX - _strMouse[4].fX;

		if (_strMouse[4].fY < _strMouse[3].fY)
			dY = _strMouse[3].fY - _strMouse[4].fY;

		if (fMouse_Triangle_X <= _strMouse[3].fX)
			fMouse_Triangle_X += dX / 50.f;

		else
			fMouse_Triangle_X -= dX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[3].fY)
			fMouse_Triangle_Y += dY / 50.f;
		else
			fMouse_Triangle_Y -= dY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[3].fX;
			fMouse_Triangle_Y = _strMouse[3].fY;
		}
		if (fMouse_Triangle_X == _strMouse[3].fX && fMouse_Triangle_Y == _strMouse[3].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 5;
		}
	}

	if (Mouse_Count == 5)
	{
		if (_strMouse[3].fX < _strMouse[2].fX)
			cX = _strMouse[2].fX - _strMouse[3].fX;

		if (_strMouse[3].fY < _strMouse[2].fY)
			cY = _strMouse[2].fY - _strMouse[3].fY;

		if (fMouse_Triangle_X <= _strMouse[2].fX)
			fMouse_Triangle_X += cX / 50.f;
		else
			fMouse_Triangle_X -= cX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[2].fY)
			fMouse_Triangle_Y += cY / 50.f;
		else
			fMouse_Triangle_Y -= cY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[2].fX;
			fMouse_Triangle_Y = _strMouse[2].fY;
		}
		if (fMouse_Triangle_X == _strMouse[2].fX && fMouse_Triangle_Y == _strMouse[2].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 6;
		}

	}
	 
	if (Mouse_Count == 6)
	{
		if (_strMouse[2].fX < _strMouse[1].fX)
			bX = _strMouse[1].fX - _strMouse[2].fX;

		if (_strMouse[2].fY < _strMouse[1].fY)
			bY = _strMouse[1].fY - _strMouse[2].fY;

		if (fMouse_Triangle_X <= _strMouse[1].fX)
			fMouse_Triangle_X += bX / 50.f;
		else
			fMouse_Triangle_X -= bX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[1].fY)
			fMouse_Triangle_Y += bY / 50.f;
		else
			fMouse_Triangle_Y -= bY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[1].fX;
			fMouse_Triangle_Y = _strMouse[1].fY;
		}
		if (fMouse_Triangle_X == _strMouse[1].fX && fMouse_Triangle_Y == _strMouse[1].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 7;
		}
	}


	if (Mouse_Count == 7)
	{
		if (_strMouse[1].fX < _strMouse[0].fX)
			aX = _strMouse[0].fX - _strMouse[1].fX;

		if (_strMouse[1].fY < _strMouse[0].fY)
			aY = _strMouse[0].fY - _strMouse[1].fY;

		if (fMouse_Triangle_X <= _strMouse[0].fX)
			fMouse_Triangle_X += aX / 50.f;
		else
			fMouse_Triangle_X -= aX / 50.f;

		if (fMouse_Triangle_Y <= _strMouse[0].fY)
			fMouse_Triangle_Y += aY / 50.f;
		else
			fMouse_Triangle_Y -= aY / 50.f;

		Mouse_Move++;

		if (Mouse_Move == 50)
		{
			fMouse_Triangle_X = _strMouse[0].fX;
			fMouse_Triangle_Y = _strMouse[0].fY;
		}

		if (fMouse_Triangle_X == _strMouse[0].fX && fMouse_Triangle_Y == _strMouse[0].fY)
		{
			Mouse_Move = 0;
			Mouse_Count = 0;
		}

	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerMouse, 4);
}

void Mouse(int button, int state, int x, int y)
{
	float MX = ((float)x - 400.0f) / 400.f;
	float MY = (300.0f - (float)y) / 300.f;
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (iClick_Count <= 4)
		{
			_strMouse[iClick_Count].fX = MX;
			_strMouse[iClick_Count].fY = MY;
			if (iClick_Count == 0)
			{
				fMouse_Triangle_X = _strMouse[0].fX;
				fMouse_Triangle_Y = _strMouse[0].fY;
			}
			if (iClick_Count == 4)
				bMouse_Render = true;

			iClick_Count++;
		}
	}

	glutPostRedisplay();
}

