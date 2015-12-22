#include <gl/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

typedef struct strRect
{
	float fLeft_Top_X;
	float fLeft_Top_Y;
	float fRight_Top_X;
	float fRight_Top_Y;
	float fRight_Bottom_X;
	float fRight_Bottom_Y;
	float fLeft_Bottom_X;
	float fLeft_Bottom_Y;

	strRect(float a, float b, float c, float d, float e, float f, float g, float h)
	{
		fLeft_Top_X = a;
		fLeft_Top_Y = b;
		fRight_Top_X = c;
		fRight_Top_Y = d;
		fRight_Bottom_X = e;
		fRight_Bottom_Y = f;
		fLeft_Bottom_X = g;
		fLeft_Bottom_Y = h;
	}
}strRect;

typedef struct strMouse
{
	float fX;
	float fY;
}strMouse;

typedef struct Point
{
	float fUnder;
	float fT;
	float fS;
	float _fT;
	float _fS;
	float fX;
	float fY;
}Point;

typedef struct Triangle
{
	float fX1[10];
	float fY1[10];
	float fX2[10];
	float fY2[10];
	float fX3[10];
	float fY3[10];
}Triangle;

typedef struct FourRect
{
	float fX1[10];
	float fY1[10];
	float fX2[10];
	float fY2[10];
	float fX3[10];
	float fY3[10];
	float fX4[10];
	float fY4[10];
}FourRect;

typedef struct FiveRect
{
	float fX1;
	float fY1;
	float fX2;
	float fY2;
	float fX3;
	float fY3;
	float fX4;
	float fY4;
	float fX5;
	float fY5;
}FiveRect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int vlaue);
void TimerWaterWave(int vlaue);
void MoveRect();
void MoveBox();
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Cliping();
strMouse _Mouse[2];
Triangle triagnle;
FourRect fourRect_1;
FourRect fourRect_2;
FourRect Temp;
FiveRect fiveRect;
strRect ptrRect(-50.f, 200.f, 50.f, 200.f, 50.f, 100.f, -50.f, 100.f);
Point strPoint[4] = { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } };
bool Create_Rect = true;
bool bMouse = false;
bool bLine = false;
bool bTriagle = false;
bool bFourRect = false;

float fSlope1 = 0.f;
float P1 = 0.f;
float fSlope2 = 0.f;
float P2 = 0.f;
int iMove = 0;
int iCheck = 0;
int iMouse_Count = 0;
float P;
float Vertex_To_Line1;
float Vertex_To_Line2;
float Rect_Translate = 0.f;
float Rect_Move = 1.5f;
float Rect_Move2 = 1.5f;
float aaa = 1.5f;
float Rect_Move3 = 0.0f;
float Window_Translate = 0.0f;
float Window_Move = 1.5f;
float Box_Translate = 0.f;
float Box_Move = 2.0f;
float Box_Move2 = 0.0f;
bool Box_Move_No = true;
bool Box_Move_No2 = true;
float Water[9] = { -220.f, -220.f, -200.f, -200.f, -200.f, -200.f, -200.f, -200.f, -200.f };
float Water_Wave[9] = { 2.5f, 1.5f, 2.5f, 1.0f, 2.5f, 2.5f, 1.5f, 2.5f, 1.5f, };
float Water_X1 = -100.f;
float Water_X2 = 100.f;
float Water_X3 = 100.f;
float Water_X4 = -100.f;
int iTriCount = 0;
int iFourCount = 0;
float Box_X1 = -100.f;
float Box_Y1 = -150.f;
float Box_X2 = 100.f;
float Box_Y2 = -150.f;
float Box_a = -100.f;
float Box_aY = -250.f;
float Box_b = 100.f;
float Box_bY = -250.f;

float fFirst_X;
float fFirst_Y;
float fSecond_X;
float fSecond_Y;
float fTriMove = -1.0f;
float fTranslate_Tri = 0.f;
float fFourMove1 = -1.0f;
float fTranslate_Four1 = 0.f;
float fFourMove2 = -1.0f;
float fTranslate_Four2 = 0.f;
float fFiveMove = -1.0f;
float fTranslate_Five = 0.f;

bool Box_Cli = false;
bool Box_Cli2 = false;
bool Box_Cli3 = false;
bool Box_Cli4 = false;
bool Box_Cli5 = false;
bool Box_to = false;
bool Box_to_four = false;
bool Box_to_four2 = false;
bool Box_to_four3 = false;
bool Attack = false;
bool over = false;

float Attack1;
float Attack2;
float Attack_Rotate = 0.f;
float Attack_Rotate_Plus = 1.f;
float Attack_TransX = 0.f;
float Attack_TransY = 0.f;
float Attack_Trans_Plus = 1.f;

float Cliping_X = 0.f;
float Cliping_Y = 0.f;
float Cliping_M = 0.0f;
float Cliping_P = 0.0f;

float fCross_X1 = 0.0f;
float fCross_Y1 = 0.0f;
float fCross_X2 = 0.0f;
float fCross_Y2 = 0.0f;
float fCross_Cross1 = 0.0f;
float fCross_Cross2 = 0.0f;
float fCross_Slope1 = 0.0f;
float fCross_Slope2 = 0.0f;
float fCross_P1 = 0.0f;
float fCross_P2 = 0.0f;
float fCross_fT1 = 0.0f;
float fCross_fS1 = 0.0f;
float fCrossfT1 = 0.0f;
float fCrossfS1 = 0.f;
float fCrossX1 = 0.0f;
float fCrossY1 = 0.0f;
float fCross_fT2 = 0.0f;
float fCross_fS2 = 0.0f;
float fCrossfT2 = 0.0f;
float fCrossfS2 = 0.f;
float fCrossX2 = 0.0f;
float fCrossY2 = 0.0f;
float fUnder1 = 0.0f;
float fUnder2 = 0.0f;


void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("숙제1");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(100, TimerWaterWave, 2);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);				//이동, 회전, 신축을 위함이다.(현재의 행렬 모드를 설정)

	glPushMatrix();
	//위에서 움직이는 사각형
	MoveRect();
	if (bLine == true)
	{
		//glPushMatrix();
		glLineWidth(2);
		glBegin(GL_LINES);
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(_Mouse[0].fX, _Mouse[0].fY, 0.f);
		glVertex3f(_Mouse[1].fX, _Mouse[1].fY, 0.f);
		glEnd();
		//glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	//밑에서 움직이는 바구니
	MoveBox();
	Cliping();
	glPopMatrix();

	//glPushMatrix();
	//Cliping();
	//glPopMatrix();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}

void TimerFunction(int vlaue)
{
	if (iMove == 0 && Box_Move_No2 == true)
	{
		Rect_Translate += Rect_Move;
	}

	if (Box_Move_No2 == true)
	{
		Rect_Move3 += Rect_Move2;
	
		if (Rect_Move3 > 250.f || Rect_Move3 < -250.f)
		{
			Rect_Move2 *= -1.f;
			Rect_Move *= (-1.f);
		}
	}
	if (ptrRect.fLeft_Top_X >= 150.f)
	{
		//Rect_Move2 *= (-1.f);
		//Rect_Move *= (-1.f);
	}
	if (ptrRect.fLeft_Top_X <= -350.f)
	{
		//Rect_Move2 *= (-1.f);
		//Rect_Move *= (-1.f);
	}

	if (Box_Move_No == true)
		Box_Move2 += Box_Move;

	if (Box_Move2 > 150.f || Box_Move2 < -150.f)
		Box_Move *= -1.f;

	/*if (Box_X1 >= 150.f)
		Box_Move *= (-1.f);
	if (Box_X1 <= -350.f)
		Box_Move *= (-1.f);*/

	if (bMouse == true && iCheck != 0)
	{
		iMove = 1;
		if (iCheck == 1 || iCheck == 4 || iCheck == 5 || iCheck == 9)
			fTranslate_Tri += fTriMove;

		if (iCheck == 2 || iCheck == 3)
			fTranslate_Four1 += fFourMove1;

		fTranslate_Four2 += fFourMove2;
		fTranslate_Five += fFiveMove;

		if (Attack == true)
		{
			Attack_Rotate += Attack_Rotate_Plus;
			Attack_TransX += Attack_Trans_Plus;
			Attack_TransY -= Attack_Trans_Plus;
		}

	}


	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void MoveRect()
{

	if (fTranslate_Five <= -1000 || fTranslate_Four1 <= -1000)
	{
		fTranslate_Tri = 0.f;
		fTranslate_Five = 0.f;
		fTranslate_Four1 = 0.f;
		fTranslate_Four2 = 0.f;

		_Mouse[0].fX = 0.f;
		_Mouse[0].fY = 0.f;
		_Mouse[1].fX = 0.f;
		_Mouse[1].fY = 0.f;

		Create_Rect = true;
		bMouse = false;
		bLine = false;
		Attack = false;
		bTriagle = false;
		iMove = 0;
		iCheck = 0;
		Rect_Move3 = 0.0f;
		bFourRect = false;
		Box_Move_No = true;
		Box_Move_No2 = true;
		Box_Cli = false;
		Box_Cli2 = false;
		Box_Cli3 = false;
		Box_to = false;
		Box_to_four = false;
		Box_to_four2 = false;
		over = false;
		Attack_TransX = 0.f;
		fTranslate_Tri = 0.0f;
		Attack_TransY = 0.0f;
		Attack_Rotate = 0.0f;
		fTriMove = -1.f;
		//iFourCount++;

	}
	if (Create_Rect == true && iCheck == 0)
	{

		//좌표를 변수로 바꿔야 한다?
		glColor3f(1.f, 0.f, 0.f);
		glBegin(GL_POLYGON);
		if (Box_Move_No2 == true)
		{
			ptrRect.fLeft_Top_X += Rect_Move2;
			ptrRect.fRight_Top_X += Rect_Move2;
			ptrRect.fRight_Bottom_X += Rect_Move2;
			ptrRect.fLeft_Bottom_X += Rect_Move2;
		}

		glVertex3f(ptrRect.fLeft_Top_X, ptrRect.fLeft_Top_Y, 0.f);
		glVertex3f(ptrRect.fRight_Top_X, ptrRect.fRight_Top_Y, 0.f);
		glVertex3f(ptrRect.fRight_Bottom_X, ptrRect.fRight_Bottom_Y, 0.f);
		glVertex3f(ptrRect.fLeft_Bottom_X, ptrRect.fLeft_Bottom_Y, 0.f);
		glEnd();

		for (int i = 0; i < iFourCount; i++)
		{
			glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
			glBegin(GL_POLYGON);
			glRotatef(45.f, 1.f, 0.0f, 0.0f);
			glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount], 0.0f);
			glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount], 0.0f);
			glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount], 0.0f);
			glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount], 0.0f);
			glEnd();
		}
	}

	if (bMouse == true)
	{

		strPoint[0].fUnder = (200.f - 200.f) * (_Mouse[1].fX - _Mouse[0].fX) - (50.f - (-50.f)) * (_Mouse[1].fY - _Mouse[0].fY);
		strPoint[0]._fT = (50.f - (-50.f)) * (_Mouse[0].fY - 200.f) - (200.f - 200.f) * (_Mouse[0].fX - (-50.f));
		strPoint[0]._fS = (_Mouse[1].fX - _Mouse[0].fX) * (_Mouse[0].fY - 200.f) - (_Mouse[1].fY - _Mouse[0].fY) * (_Mouse[0].fX - (-50.f));
		strPoint[0].fT = strPoint[0]._fT / strPoint[0].fUnder;
		strPoint[0].fS = strPoint[0]._fS / strPoint[0].fUnder;
		strPoint[0].fX = _Mouse[0].fX + strPoint[0].fT * (_Mouse[1].fX - _Mouse[0].fX);
		strPoint[0].fY = _Mouse[0].fY + strPoint[0].fT * (_Mouse[1].fY - _Mouse[0].fY);
		/////////////////////////////////////////////////////////////////////////////////////////
		strPoint[1].fUnder = (100.f - 200.f) * (_Mouse[1].fX - _Mouse[0].fX) - (50.f - 50.f) * (_Mouse[1].fY - _Mouse[0].fY);
		strPoint[1]._fT = (50.f - 50.f) * (_Mouse[0].fY - 200.f) - (100.f - 200.f) * (_Mouse[0].fX - 50.f);
		strPoint[1]._fS = (_Mouse[1].fX - _Mouse[0].fX) * (_Mouse[0].fY - 200.f) - (_Mouse[1].fY - _Mouse[0].fY) * (_Mouse[0].fX - 50.f);
		strPoint[1].fT = strPoint[1]._fT / strPoint[1].fUnder;
		strPoint[1].fS = strPoint[1]._fS / strPoint[1].fUnder;
		strPoint[1].fX = _Mouse[0].fX + strPoint[1].fT * (_Mouse[1].fX - _Mouse[0].fX);
		strPoint[1].fY = _Mouse[0].fY + strPoint[1].fT * (_Mouse[1].fY - _Mouse[0].fY);
		//////////////////////////////////////////////////////////////////////////////////////////
		strPoint[2].fUnder = (100.f - 100.f) * (_Mouse[1].fX - _Mouse[0].fX) - ((-50.f) - 50.f) * (_Mouse[1].fY - _Mouse[0].fY);
		strPoint[2]._fT = ((-50.f) - 50.f) * (_Mouse[0].fY - 100.f) - (100.f - 100.f) * (_Mouse[0].fX - 50.f);
		strPoint[2]._fS = (_Mouse[1].fX - _Mouse[0].fX) * (_Mouse[0].fY - 100.f) - (_Mouse[1].fY - _Mouse[0].fY) * (_Mouse[0].fX - 50.f);
		strPoint[2].fT = strPoint[2]._fT / strPoint[2].fUnder;
		strPoint[2].fS = strPoint[2]._fS / strPoint[2].fUnder;
		strPoint[2].fX = _Mouse[0].fX + strPoint[2].fT * (_Mouse[1].fX - _Mouse[0].fX);
		strPoint[2].fY = _Mouse[0].fY + strPoint[2].fT * (_Mouse[1].fY - _Mouse[0].fY);
		//////////////////////////////////////////////////////////////////////////////////////////
		strPoint[3].fUnder = (200.f - 100.f) * (_Mouse[1].fX - _Mouse[0].fX) - ((-50.f) - (-50.f)) * (_Mouse[1].fY - _Mouse[0].fY);
		strPoint[3]._fT = ((-50.f) - (-50.f)) * (_Mouse[0].fY - 100.f) - (200.f - 100.f) * (_Mouse[0].fX - (-50.f));
		strPoint[3]._fS = (_Mouse[1].fX - _Mouse[0].fX) * (_Mouse[0].fY - 100.f) - (_Mouse[1].fY - _Mouse[0].fY) * (_Mouse[0].fX - (-50.f));
		strPoint[3].fT = strPoint[3]._fT / strPoint[3].fUnder;
		strPoint[3].fS = strPoint[3]._fS / strPoint[3].fUnder;
		strPoint[3].fX = _Mouse[0].fX + strPoint[3].fT * (_Mouse[1].fX - _Mouse[0].fX);
		strPoint[3].fY = _Mouse[0].fY + strPoint[3].fT * (_Mouse[1].fY - _Mouse[0].fY);


		if (strPoint[0].fX > -50.f && strPoint[0].fX < 50.f && strPoint[1].fY < 200.f && strPoint[1].fY > 100.f)
		{
			bLine = true;
			iCheck = 1;
			triagnle.fX1[iTriCount] = strPoint[0].fX;		triagnle.fY1[iTriCount] = strPoint[0].fY;
			triagnle.fX2[iTriCount] = strPoint[1].fX;		triagnle.fY2[iTriCount] = strPoint[1].fY;
			triagnle.fX3[iTriCount] = 50.f;				triagnle.fY3[iTriCount] = 200.f;

			fiveRect.fX1 = strPoint[0].fX;		fiveRect.fY1 = strPoint[0].fY;
			fiveRect.fX2 = strPoint[1].fX;		fiveRect.fY2 = strPoint[1].fY;
			fiveRect.fX3 = 50.f;				fiveRect.fY3 = 100.f;
			fiveRect.fX4 = -50.f;				fiveRect.fY4 = 100.f;
			fiveRect.fX5 = -50.f;				fiveRect.fY5 = 200.f;

		}

		if (strPoint[0].fX > -50.f && strPoint[0].fX < 50.f && strPoint[2].fX > -50.f && strPoint[2].fX < 50.f && bMouse == true)
		{
			bLine = true;
			iCheck = 2;
			fourRect_1.fX1[iFourCount] = strPoint[0].fX;	fourRect_1.fY1[iFourCount] = strPoint[0].fY;
			fourRect_1.fX2[iFourCount] = strPoint[2].fX;	fourRect_1.fY2[iFourCount] = strPoint[2].fY;
			fourRect_1.fX3[iFourCount] = 50.f;				fourRect_1.fY3[iFourCount] = 100.f;
			fourRect_1.fX4[iFourCount] = 50.f;				fourRect_1.fY4[iFourCount] = 200.f;

			fourRect_2.fX1[iFourCount] = strPoint[0].fX;	fourRect_2.fY1[iFourCount] = strPoint[0].fY;
			fourRect_2.fX2[iFourCount] = strPoint[2].fX;	fourRect_2.fY2[iFourCount] = strPoint[2].fY;
			fourRect_2.fX3[iFourCount] = -50.f;			fourRect_2.fY3[iFourCount] = 100.f;
			fourRect_2.fX4[iFourCount] = -50.f;			fourRect_2.fY4[iFourCount] = 200.f;

		}

		if (strPoint[0].fX > -50.f && strPoint[0].fX < 50.f && strPoint[3].fY > 100.f && strPoint[3].fY < 200.f)
		{
			iCheck = 9;
			bLine = true;
			triagnle.fX1[iTriCount] = strPoint[0].fX;		triagnle.fY1[iTriCount] = strPoint[0].fY;
			triagnle.fX2[iTriCount] = strPoint[3].fX;		triagnle.fY2[iTriCount] = strPoint[3].fY;
			triagnle.fX3[iTriCount] = -50.f;				triagnle.fY3[iTriCount] = 200.f;

			fiveRect.fX1 = strPoint[0].fX;		fiveRect.fY1 = strPoint[0].fY;
			fiveRect.fX2 = strPoint[3].fX;		fiveRect.fY2 = strPoint[3].fY;
			fiveRect.fX3 = -50.f;				fiveRect.fY3 = 100.f;
			fiveRect.fX4 = 50.f;				fiveRect.fY4 = 100.f;
			fiveRect.fX5 = 50.f;				fiveRect.fY5 = 200.f;

		}

		if (strPoint[1].fY > 100.f && strPoint[1].fY < 200.f && strPoint[2].fX > -50.f && strPoint[2].fX < 50.f)
		{
			iCheck = 4;
			bLine = true;
			triagnle.fX1[iTriCount] = strPoint[1].fX;		triagnle.fY1[iTriCount] = strPoint[1].fY;
			triagnle.fX2[iTriCount] = strPoint[2].fX;		triagnle.fY2[iTriCount] = strPoint[2].fY;
			triagnle.fX3[iTriCount] = 50.f;					triagnle.fY3[iTriCount] = 100.f;

			fiveRect.fX1 = strPoint[1].fX;		fiveRect.fY1 = strPoint[1].fY;
			fiveRect.fX2 = strPoint[2].fX;		fiveRect.fY2 = strPoint[2].fY;
			fiveRect.fX3 = -50.f;				fiveRect.fY3 = 100.f;
			fiveRect.fX4 = -50.f;				fiveRect.fY4 = 200.f;
			fiveRect.fX5 = 50.f;				fiveRect.fY5 = 200.f;

		}
		if (strPoint[3].fY > 100.f && strPoint[3].fY < 200.f && strPoint[2].fX > -50.f && strPoint[2].fX < 50.f)
		{
			iCheck = 5;
			bLine = true;
			triagnle.fX1[iTriCount] = strPoint[3].fX;		triagnle.fY1[iTriCount] = strPoint[3].fY;
			triagnle.fX2[iTriCount] = strPoint[2].fX;		triagnle.fY2[iTriCount] = strPoint[2].fY;
			triagnle.fX3[iTriCount] = -50.f;				triagnle.fY3[iTriCount] = 100.f;

			fiveRect.fX1 = strPoint[3].fX;		fiveRect.fY1 = strPoint[3].fY;
			fiveRect.fX2 = strPoint[2].fX;		fiveRect.fY2 = strPoint[2].fY;
			fiveRect.fX3 = 50.f;				fiveRect.fY3 = 100.f;
			fiveRect.fX4 = 50.f;				fiveRect.fY4 = 200.f;
			fiveRect.fX5 = -50.f;				fiveRect.fY5 = 200.f;
		}
		if (strPoint[1].fY > 100.f && strPoint[1].fY < 200.f && strPoint[3].fY > 100.f && strPoint[3].fY < 200.f)
		{
			iCheck = 3;
			bLine = true;
			fourRect_1.fX1[iFourCount] = strPoint[1].fX;	fourRect_1.fY1[iFourCount] = strPoint[1].fY;
			fourRect_1.fX2[iFourCount] = strPoint[3].fX;	fourRect_1.fY2[iFourCount] = strPoint[3].fY;
			fourRect_1.fX3[iFourCount] = -50.f;				fourRect_1.fY3[iFourCount] = 200.f;
			fourRect_1.fX4[iFourCount] = 50.f;				fourRect_1.fY4[iFourCount] = 200.f;

			fourRect_2.fX1[iFourCount] = strPoint[1].fX;	fourRect_2.fY1[iFourCount] = strPoint[1].fY;
			fourRect_2.fX2[iFourCount] = strPoint[3].fX;	fourRect_2.fY2[iFourCount] = strPoint[3].fY;
			fourRect_2.fX3[iFourCount] = -50.f;				fourRect_2.fY3[iFourCount] = 100.f;
			fourRect_2.fX4[iFourCount] = 50.f;				fourRect_2.fY4[iFourCount] = 100.f;
		}
		

		if (iCheck == 1 && bTriagle == true && Box_to == false)
		{
			Create_Rect = false;

			glPushMatrix();
			if (Attack == true)
			{
				glTranslatef(Attack_TransX, fTranslate_Tri + Attack_TransY, 0.0f);
				glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);
			}

			else
			{

				triagnle.fY1[iTriCount] += fTranslate_Tri;
				triagnle.fY2[iTriCount] += fTranslate_Tri;
				triagnle.fY3[iTriCount] += fTranslate_Tri;

			}

			if (over == false)
				glColor3f(0.5f, 0.5f, 0.0f);
			if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(triagnle.fX1[iTriCount], triagnle.fY1[iTriCount], 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

			glPopMatrix();

			glTranslatef(fTranslate_Five, 0.0f, 0.0f);
			glColor3f(0.5f, 0.0f, 0.5f);
			glBegin(GL_POLYGON);
			glVertex3f(fiveRect.fX1, fiveRect.fY1, 0.0f);
			glVertex3f(fiveRect.fX2, fiveRect.fY2, 0.0f);
			glVertex3f(fiveRect.fX3, fiveRect.fY3, 0.0f);
			glVertex3f(fiveRect.fX4, fiveRect.fY4, 0.0f);
			glVertex3f(fiveRect.fX5, fiveRect.fY5, 0.0f);
			glEnd();



			fSlope1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) / (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]);
			P1 = triagnle.fY2[iTriCount] - (fSlope1 * triagnle.fX2[iTriCount]);

			if (Box_Y1 > fSlope1 * Box_X1 + P1 && triagnle.fY1[iTriCount] > Box_Y1 && triagnle.fX1[iTriCount] < Box_X1 && triagnle.fX2[iTriCount] > Box_X1)
			{
				cout << "충돌" << endl;
				Attack = true;
			}

			else if (Box_Y2 > fSlope1 * Box_X2 + P1 && triagnle.fY1[iTriCount] > Box_Y2 && triagnle.fX1[iTriCount] < Box_X2 && triagnle.fX2[iTriCount] > Box_X2)
			{
				cout << "충돌" << endl;
				Attack = true;
			}

			else if (Box_aY > fSlope1 * Box_a + P1 && triagnle.fX1[iTriCount] < Box_a && triagnle.fX2[iTriCount] > Box_a)
			{
				cout << "충돌2" << endl;
				Attack = true;
			}

			else if (Box_bY > fSlope1 * Box_b + P1 && triagnle.fX1[iTriCount] < Box_b && triagnle.fX2[iTriCount] > Box_b)
			{
				cout << "충돌3" << endl;
				Attack = true;
			}
			
			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2 
				&& triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[1])
			{

				Box_to = true;
				fTriMove = 0.f;
			}
			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2 
				&& triagnle.fY1[iTriCount] > Water[0] && triagnle.fY1[iTriCount] > Water[1])
			{
				Box_Cli = true;
				fTriMove = 0.f;
			}

		}

		if (iCheck == 9 && bTriagle == true && Box_to == false)
		{
			Create_Rect = false;

			glPushMatrix();
			if (Attack == true)
			{
				glTranslatef(Attack_TransX, fTranslate_Tri + Attack_TransY, 0.0f);
				glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

			}

			else 
			{

				triagnle.fY1[iTriCount] += fTranslate_Tri;
				triagnle.fY2[iTriCount] += fTranslate_Tri;
				triagnle.fY3[iTriCount] += fTranslate_Tri;
			}

			if (over == false)
				glColor3f(0.5f, 0.5f, 0.0f);
			if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(triagnle.fX1[iTriCount], triagnle.fY1[iTriCount], 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

			glPopMatrix();

			glTranslatef(fTranslate_Five, 0.0f, 0.0f);
			glColor3f(0.5f, 0.0f, 0.5f);
			glBegin(GL_POLYGON);
			glVertex3f(fiveRect.fX1, fiveRect.fY1, 0.0f);
			glVertex3f(fiveRect.fX2, fiveRect.fY2, 0.0f);
			glVertex3f(fiveRect.fX3, fiveRect.fY3, 0.0f);
			glVertex3f(fiveRect.fX4, fiveRect.fY4, 0.0f);
			glVertex3f(fiveRect.fX5, fiveRect.fY5, 0.0f);
			glEnd();


			fSlope1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) / (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]);
			P1 = triagnle.fY2[iTriCount] - (fSlope1 * triagnle.fX2[iTriCount]);

			if (Box_Y1 > fSlope1 * Box_X1 + P1 && triagnle.fY1[iTriCount] > Box_Y1 && triagnle.fX1[iTriCount] > Box_X1 && triagnle.fX2[iTriCount] < Box_X1)
			{
				cout << "충돌" << endl;
				Attack = true;
			}

			else if (Box_Y2 > fSlope1 * Box_X2 + P1 && triagnle.fY1[iTriCount] > Box_Y2 && triagnle.fX1[iTriCount] > Box_X2 && triagnle.fX2[iTriCount] < Box_X2)
			{
				cout << "충돌" << endl;
				Attack = true;
			}
			
			else if (Box_aY > fSlope1 * Box_a + P1 && triagnle.fX1[iTriCount] > Box_a && triagnle.fX2[iTriCount] < Box_a)
			{
				cout << "충돌2" << endl;
				Attack = true;
			}

			else if (Box_bY > fSlope1 * Box_b + P1 && triagnle.fX1[iTriCount] > Box_b && triagnle.fX3[iTriCount] < Box_b
				&& triagnle.fY2[iTriCount] < Box_Y2 && triagnle.fY2[iTriCount] > Box_bY)
			{
				cout << "충돌3" << endl;
				Attack = true;
			}


			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1
				&& triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[1])
			{
				Box_to = true;
				fTriMove = 0.f;
			}
			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1
				&& triagnle.fY1[iTriCount] > Water[0] && triagnle.fY1[iTriCount] > Water[1])
			{
				Box_Cli = true;
				fTriMove = 0.f;
			}
		}

		if (iCheck == 4 && bTriagle == true && Box_to == false)
		{
			Create_Rect = false;

			glPushMatrix();
			if (Attack == true)
			{

				glTranslatef(Attack_TransX, fTranslate_Tri + Attack_TransY, 0.0f);
				glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

			}

			else
			{

				triagnle.fY1[iTriCount] += fTranslate_Tri;
				triagnle.fY2[iTriCount] += fTranslate_Tri;
				triagnle.fY3[iTriCount] += fTranslate_Tri;
			}

			if (over == false)
				glColor3f(0.5f, 0.5f, 0.0f);
			else if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(triagnle.fX1[iTriCount], triagnle.fY1[iTriCount], 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

			glPopMatrix();

			glTranslatef(fTranslate_Five, 0.0f, 0.0f);
			glColor3f(0.5f, 0.0f, 0.5f);
			glBegin(GL_POLYGON);
			glVertex3f(fiveRect.fX1, fiveRect.fY1, 0.0f);
			glVertex3f(fiveRect.fX2, fiveRect.fY2, 0.0f);
			glVertex3f(fiveRect.fX3, fiveRect.fY3, 0.0f);
			glVertex3f(fiveRect.fX4, fiveRect.fY4, 0.0f);
			glVertex3f(fiveRect.fX5, fiveRect.fY5, 0.0f);
			glEnd();


			fSlope1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) / (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]);
			P1 = triagnle.fY2[iTriCount] - (fSlope1 * triagnle.fX2[iTriCount]);

			if (Box_Y1 > fSlope1 * Box_X1 + P1 && triagnle.fY1[iTriCount] > Box_Y1 && triagnle.fX1[iTriCount] > Box_X1 && triagnle.fX2[iTriCount] < Box_X1)
			{
				cout << "충돌" << endl;
				Attack = true;
			}
			else if (Box_Y2 > fSlope1 * Box_X2 + P1 && triagnle.fY1[iTriCount] > Box_Y2 && triagnle.fX1[iTriCount] > Box_X2 && triagnle.fX2[iTriCount] < Box_X2)
			{
				cout << "충돌" << endl;
				Attack = true;
			}

			//Box_aY > fSlope1 * Box_a + P1 && triagnle.fX1[iTriCount] < Box_a && triagnle.fX2[iTriCount] > Box_a
			else if (Box_aY > fSlope1 * Box_a + P1 && triagnle.fX1[iTriCount] > Box_a && triagnle.fX2[iTriCount] < Box_a)
			{
				cout << "충돌2" << endl;
				Attack = true;
			}

			else if (Box_bY > fSlope1 * Box_b + P1 && triagnle.fX1[iTriCount] > Box_b && triagnle.fX2[iTriCount] < Box_b)
			{
				cout << "충돌3" << endl;
				Attack = true;
			}

			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1 
				&& triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[1])
			{
				Box_to = true;
				fTriMove = 0.f;
			}
			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1
				&& triagnle.fY1[iTriCount] > Water[0] && triagnle.fY1[iTriCount] > Water[1])
			{
				Box_Cli = true;
				fTriMove = 0.f;
			}

		}

		if (iCheck == 5 && bTriagle == true && Box_to == false)
		{
			Create_Rect = false;

			glPushMatrix();
			if (Attack == true)
			{

				glTranslatef(Attack_TransX, fTranslate_Tri + Attack_TransY, 0.0f);
				glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

			}

			else
			{
				triagnle.fY1[iTriCount] += fTranslate_Tri;
				triagnle.fY2[iTriCount] += fTranslate_Tri;
				triagnle.fY3[iTriCount] += fTranslate_Tri;
			}

			if (over == false)
				glColor3f(0.5f, 0.5f, 0.0f);
			else if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(triagnle.fX1[iTriCount], triagnle.fY1[iTriCount], 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

			glPopMatrix();

			glTranslatef(fTranslate_Five, 0.0f, 0.0f);
			glColor3f(0.5f, 0.0f, 0.5f);
			glBegin(GL_POLYGON);
			glVertex3f(fiveRect.fX1, fiveRect.fY1, 0.0f);
			glVertex3f(fiveRect.fX2, fiveRect.fY2, 0.0f);
			glVertex3f(fiveRect.fX3, fiveRect.fY3, 0.0f);
			glVertex3f(fiveRect.fX4, fiveRect.fY4, 0.0f);
			glVertex3f(fiveRect.fX5, fiveRect.fY5, 0.0f);
			glEnd();


			fSlope1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) / (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]);
			P1 = triagnle.fY2[iTriCount] - (fSlope1 * triagnle.fX2[iTriCount]);

			if (Box_Y1 > fSlope1 * Box_X1 + P1 && triagnle.fY1[iTriCount] > Box_Y1 && triagnle.fX1[iTriCount] < Box_X1 && triagnle.fX2[iTriCount] > Box_X1)
			{
				cout << "충돌" << endl;
				Attack = true;
			}
			if (Box_Y2 > fSlope1 * Box_X2 + P1 && triagnle.fY1[iTriCount] > Box_Y2 && triagnle.fX1[iTriCount] < Box_X2 && triagnle.fX2[iTriCount] > Box_X2)
			{
				cout << "충돌" << endl;
				Attack = true;
			}

			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2 
				&& triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[1])
			{
				Box_to = true;
				fTriMove = 0.f;
			}
			if (triagnle.fY2[iTriCount] <= Box_aY && triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2
				&& triagnle.fY1[iTriCount] > Water[0] && triagnle.fY1[iTriCount] > Water[1])
			{
				Box_Cli = true;
				fTriMove = 0.f;
			}

		}

		if (iCheck == 2 && bFourRect == true && Box_to_four == false)
		{
			Create_Rect = false;

			float fFirst_Area = (((strPoint[2].fX - fourRect_2.fX3[iFourCount]) + (strPoint[0].fX - fourRect_2.fX4[iFourCount]))
				* fourRect_2.fY4[iFourCount] - fourRect_2.fY3[iFourCount]) / 2.f;

			float fSecond_Area = (((fourRect_1.fX3[iFourCount] - strPoint[2].fX) + (fourRect_1.fX4[iFourCount] - strPoint[0].fX))
				* fourRect_1.fY4[iFourCount] - fourRect_1.fY3[iFourCount]) / 2.f;


			if (fFirst_Area > fSecond_Area)
			{
				glPushMatrix();
				if (Attack == true)
				{
					glTranslatef(Attack_TransX, fTranslate_Tri + fTranslate_Four1, 0.0f);
					glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

				}
				else
				{
					fourRect_1.fY1[iFourCount] += fTranslate_Four1;
					fourRect_1.fY2[iFourCount] += fTranslate_Four1;
					fourRect_1.fY3[iFourCount] += fTranslate_Four1;
					fourRect_1.fY4[iFourCount] += fTranslate_Four1;
				}

				fourRect_2.fX1[iFourCount] += fTranslate_Four2;
				fourRect_2.fX2[iFourCount] += fTranslate_Four2;
				fourRect_2.fX3[iFourCount] += fTranslate_Four2;
				fourRect_2.fX4[iFourCount] += fTranslate_Four2;

				glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount], 0.0f);
				glEnd();
				glPopMatrix();

				glColor3f(0.5f, 0.0f, 1.0f);			//왼쪽과 밑
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount], 0.0f);
				glEnd();

				if (Box_Y1 > fSlope1 * Box_X1 + P1 /*&& fourRect_1.fY3[iTriCount] > Box_Y1*/ && fourRect_1.fX2[iTriCount] < Box_X1 && fourRect_1.fX3[iTriCount] > Box_X1)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
				if (Box_Y2 > fSlope1 * Box_X2 + P1 /*&& fourRect_1.fY3[iTriCount] > Box_Y2*/ && fourRect_1.fX2[iTriCount] < Box_X2 && fourRect_1.fX3[iTriCount] > Box_X2)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
			}


			if (fFirst_Area < fSecond_Area)
			{
				glPushMatrix();
				if (Attack == true)
				{
					glTranslatef(Attack_TransX, fTranslate_Tri + fTranslate_Four2, 0.0f);
					glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

				}
				else
				{
					fourRect_2.fY1[iFourCount] += fTranslate_Four2;
					fourRect_2.fY2[iFourCount] += fTranslate_Four2;
					fourRect_2.fY3[iFourCount] += fTranslate_Four2;
					fourRect_2.fY4[iFourCount] += fTranslate_Four2;
				}

				fourRect_1.fX1[iFourCount] += fTranslate_Four1;
				fourRect_1.fX2[iFourCount] += fTranslate_Four1;
				fourRect_1.fX3[iFourCount] += fTranslate_Four1;
				fourRect_1.fX4[iFourCount] += fTranslate_Four1;

				glColor3f(0.5f, 0.0f, 0.0f);			//왼쪽과 밑
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount], 0.0f);
				glEnd();
				glPopMatrix();

				glColor3f(0.5f, 0.0f, 1.0f);			//오른쪽과 위
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount], 0.0f);
				glEnd();

				if (Box_Y1 > fSlope2 * Box_X1 + P2 /*&& fourRect_2.fY2[iTriCount] > Box_Y1*/ && fourRect_2.fX2[iTriCount] > Box_X1 && fourRect_2.fX3[iTriCount] < Box_X1)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
				if (Box_Y2 > fSlope2 * Box_X2 + P2 /*&& fourRect_2.fY2[iTriCount] > Box_Y2*/ && fourRect_2.fX2[iTriCount] > Box_X2 && fourRect_2.fX3[iTriCount] < Box_X2)
				{
					cout << "충돌" << endl;
					Attack = true;
				}

			}



			fSlope1 = (fourRect_1.fY3[iTriCount] - fourRect_1.fY2[iTriCount]) / (fourRect_1.fX3[iTriCount] - fourRect_1.fX2[iTriCount]);
			P1 = fourRect_1.fY3[iTriCount] - (fSlope1 * fourRect_1.fX3[iTriCount]);
			fSlope2 = (fourRect_2.fY2[iTriCount] - fourRect_2.fY3[iTriCount]) / (fourRect_2.fX2[iTriCount] - fourRect_2.fX3[iTriCount]);
			P2 = fourRect_2.fY2[iTriCount] - (fSlope2 * fourRect_2.fX2[iTriCount]);

			if (fourRect_1.fY2[iTriCount] <= Box_aY && fourRect_1.fX1[iTriCount] > Water_X1 && fourRect_1.fX4[iTriCount] < Water_X2
				&& fourRect_1.fX1[iTriCount] > Water[0] && fourRect_1.fX1[iTriCount] > Water[1])
			{
				//Box_to_four = true;
				Box_Cli3 = true;
				//Box_Cli = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}
			if (fourRect_2.fY2[iTriCount] <= Box_aY && fourRect_2.fX1[iTriCount] < Water_X2 && fourRect_2.fX4[iTriCount] > Water_X1
				&& fourRect_2.fX1[iTriCount] > Water[0] && fourRect_2.fX1[iTriCount] > Water[1])
			{
				//Box_to_four = true;
				Box_Cli2 = true;
				//Box_Cli = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}

		}

		if (iCheck == 3 && bFourRect == true && Box_to_four2 == false && Box_to_four3 == false)
		{
			Create_Rect = false;

			float fFirst_Area = (((fourRect_2.fY1[iFourCount] - fourRect_2.fY4[iFourCount]) + (fourRect_2.fY2[iFourCount] - fourRect_2.fY3[iFourCount]))
				* fourRect_2.fX4[iFourCount] - fourRect_2.fX3[iFourCount]) / 2.f;

			float fSecond_Area = (((fourRect_1.fY4[iFourCount] - fourRect_1.fY1[iFourCount]) + (fourRect_1.fY3[iFourCount] - fourRect_1.fY2[iFourCount]))
				* fourRect_1.fX4[iFourCount] - fourRect_1.fX3[iFourCount]) / 2.f;

			if (fFirst_Area > fSecond_Area)
			{
				glPushMatrix();
				if (Attack == true)
				{
					glTranslatef(Attack_TransX, fTranslate_Tri + fTranslate_Four1, 0.0f);
					glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

				}
				else
				{
					fourRect_1.fY1[iFourCount] += fTranslate_Four1;
					fourRect_1.fY2[iFourCount] += fTranslate_Four1;
					fourRect_1.fY3[iFourCount] += fTranslate_Four1;
					fourRect_1.fY4[iFourCount] += fTranslate_Four1;
				}
				fourRect_2.fX1[iFourCount] += fTranslate_Four2;
				fourRect_2.fX2[iFourCount] += fTranslate_Four2;
				fourRect_2.fX3[iFourCount] += fTranslate_Four2;
				fourRect_2.fX4[iFourCount] += fTranslate_Four2;

				if (over == false)
					glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
				if (over == true)
					glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount], 0.0f);
				glEnd();
				glPopMatrix();


				glColor3f(0.5f, 0.0f, 0.0f);			//왼쪽과 밑
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount], 0.0f);
				glEnd();

				if (Box_Y1 > fSlope1 * Box_X1 + P1 && fourRect_1.fY3[iTriCount] > Box_Y1 && fourRect_1.fX1[iTriCount] > Box_X1 && fourRect_1.fX2[iTriCount] < Box_X1)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
				if (Box_Y2 > fSlope1 * Box_X2 + P1 && fourRect_1.fY3[iTriCount] > Box_Y2 && fourRect_1.fX1[iTriCount] > Box_X2 && fourRect_1.fX2[iTriCount] < Box_X2)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
			}

			if (fFirst_Area < fSecond_Area)
			{
				glPushMatrix();
				if (Attack == true)
				{
					glTranslatef(Attack_TransX, fTranslate_Tri + fTranslate_Four2, 0.0f);
					glRotatef(Attack_Rotate, 0.0f, 0.0f, 1.0f);

				}
				else
				{
					fourRect_2.fY1[iFourCount] += fTranslate_Four2;
					fourRect_2.fY2[iFourCount] += fTranslate_Four2;
					fourRect_2.fY3[iFourCount] += fTranslate_Four2;
					fourRect_2.fY4[iFourCount] += fTranslate_Four2;
				}
				fourRect_1.fX1[iFourCount] += fTranslate_Four1;
				fourRect_1.fX2[iFourCount] += fTranslate_Four1;
				fourRect_1.fX3[iFourCount] += fTranslate_Four1;
				fourRect_1.fX4[iFourCount] += fTranslate_Four1;

				cout << over << endl;
				if (over == false)
					glColor3f(0.5f, 0.0f, 0.0f);			//왼쪽과 밑
				if (over == true)
					glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount], 0.0f);
				glEnd();

				glPopMatrix();


				glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
				glBegin(GL_POLYGON);
				glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount], 0.0f);
				glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount], 0.0f);
				glEnd();

				if (Box_Y1 > fSlope2 * Box_X1 + P2 && fourRect_2.fY1[iTriCount] > Box_Y1 && fourRect_2.fX3[iTriCount] < Box_X1 && fourRect_2.fX4[iTriCount] > Box_X1)
				{
					cout << "충돌" << endl;
					Attack = true;
				}
				if (Box_Y2 > fSlope2 * Box_X2 + P2 && fourRect_2.fY1[iTriCount] > Box_Y2 && fourRect_2.fX3[iTriCount] < Box_X2 && fourRect_2.fX4[iTriCount] > Box_X2)
				{
					cout << "충돌" << endl;
					Attack = true;
				}

			}

			fSlope1 = (fourRect_1.fY2[iTriCount] - fourRect_1.fY1[iTriCount]) / (fourRect_1.fX2[iTriCount] - fourRect_1.fX1[iTriCount]);
			P1 = fourRect_1.fY2[iTriCount] - (fSlope1 * fourRect_1.fX2[iTriCount]);
			fSlope2 = (fourRect_2.fY3[iTriCount] - fourRect_2.fY4[iTriCount]) / (fourRect_2.fX3[iTriCount] - fourRect_2.fX4[iTriCount]);
			P2 = fourRect_2.fY3[iTriCount] - (fSlope2 * fourRect_2.fX3[iTriCount]);

			Temp.fX1[iFourCount] = fourRect_2.fX4[iFourCount];
			Temp.fY1[iFourCount] = fourRect_2.fY4[iFourCount];
			Temp.fX2[iFourCount] = fourRect_2.fX3[iFourCount];
			Temp.fY2[iFourCount] = fourRect_2.fY3[iFourCount];
			Temp.fX3[iFourCount] = fourRect_2.fX2[iFourCount];
			Temp.fY3[iFourCount] = fourRect_2.fY2[iFourCount];
			Temp.fX4[iFourCount] = fourRect_2.fX1[iFourCount];
			Temp.fY4[iFourCount] = fourRect_2.fY1[iFourCount];
			
			if (fourRect_1.fY2[iTriCount] <= Box_aY )
				if(fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
				&& fourRect_1.fY3[iTriCount] < Water[0] && fourRect_1.fY3[iTriCount] < Water[1])
			{
				Box_to_four2 = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}
			if (fourRect_1.fY1[iTriCount] <= Box_aY )
				if( fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
				&& fourRect_1.fY3[iTriCount] < Water[0] && fourRect_1.fY3[iTriCount] < Water[1])
			{
				Box_to_four2 = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}

			if (fourRect_1.fY2[iTriCount] <= Box_aY)
				if ( fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
				&& fourRect_1.fY3[iTriCount] > Water[0] && fourRect_1.fY3[iTriCount] > Water[1])
			{
				Box_Cli4 = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}

			if (fourRect_1.fY1[iTriCount] <= Box_aY)
				if (fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
					&& fourRect_1.fY3[iTriCount] > Water[0] && fourRect_1.fY3[iTriCount] > Water[1])
				{
					Box_Cli4 = true;
					fFourMove1 = 0.f;
					fFourMove2 = 0.f;
				}
			//////////////////////////////////////////////////

			if (Temp.fY1[iFourCount] <= Box_aY )
				if( Temp.fX4[iFourCount] < Water_X2 && Temp.fX3[iFourCount] > Water_X1
				&& Temp.fY3[iFourCount] < Water[0] && Temp.fY3[iFourCount] < Water[1])
			{
				Box_to_four3 = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}
			if (Temp.fY1[iFourCount] <= Box_aY
				&& Temp.fX4[iFourCount] < Water_X2 && Temp.fX3[iFourCount] > Water_X1
				&& Temp.fY3[iFourCount] > Water[0] && Temp.fY3[iFourCount] > Water[1])
			{
				Box_Cli5 = true;
				fFourMove1 = 0.f;
				fFourMove2 = 0.f;
			}
		}


	}
}


void MoveBox()
{
	//좌표값을 변수로 바꿔야 할꺼 같다.
	glLineWidth(1);
	glColor3f(0.f, 0.f, 0.f);
	//glTranslatef(Box_Translate, 0.f, 0.f);
	if (Box_Move_No == true)
	{
		Box_X1 += Box_Move;
		Box_X2 += Box_Move;
		Box_a += Box_Move;
		Box_b += Box_Move;
		Water_X1 += Box_Move;
		Water_X2 += Box_Move;
		Water_X3 += Box_Move;
		Water_X4 += Box_Move;

		/*if (Box_to == true)
		{
			
			cout << "이동전 : " << triagnle.fX1[iTriCount] << endl;
			triagnle.fX1[iTriCount] += Box_Move;
			triagnle.fX2[iTriCount] += Box_Move;
			triagnle.fX3[iTriCount] += Box_Move;
			cout << "박스무브 : " << Box_Move << endl;
			cout << triagnle.fX1[iTriCount] << endl;
		}*/
	}

	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glVertex3f(Box_X1, Box_Y1, 0.f);
	glVertex3f(Box_a, Box_aY, 0.f);
	glVertex3f(Box_b, Box_bY, 0.f);
	glVertex3f(Box_X2, Box_Y2, 0.f);
	glEnd();

	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_POLYGON);
	glVertex3f(Water_X1, Water[0], 0.f);
	glVertex3f(Water_X2, Water[1], 0.f);
	glVertex3f(Water_X3, -250.f, 0.f);
	glVertex3f(Water_X4, -250.f, 0.f);
	glEnd();
	
	if (Box_to == true)
	{

		if (over == false)
			glColor3f(0.5f, 0.5f, 0.0f);
		else if (over == true)
			glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		triagnle.fX1[iTriCount] += Box_Move2;
		triagnle.fX2[iTriCount] += Box_Move2;
		triagnle.fX3[iTriCount] += Box_Move2;
		glVertex3f(triagnle.fX1[iTriCount], triagnle.fY1[iTriCount] + fTranslate_Tri, 0.0f);
		glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount] + fTranslate_Tri, 0.0f);
		glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount] + fTranslate_Tri, 0.0f);
		glEnd();
	}

	if (Box_to_four == true)
	{
		float fFirst_Area = (((strPoint[2].fX - fourRect_2.fX3[iFourCount]) + (strPoint[0].fX - fourRect_2.fX4[iFourCount]))
			* fourRect_2.fY4[iFourCount] - fourRect_2.fY3[iFourCount]) / 2.f;

		float fSecond_Area = (((fourRect_1.fX3[iFourCount] - strPoint[2].fX) + (fourRect_1.fX4[iFourCount] - strPoint[0].fX))
			* fourRect_1.fY4[iFourCount] - fourRect_1.fY3[iFourCount]) / 2.f;
		//fTranslate_Tri + fTranslate_Four2


		if (fFirst_Area > fSecond_Area)
		{
			fourRect_1.fX1[iFourCount] += Box_Move2;
			fourRect_1.fX2[iFourCount] += Box_Move2;
			fourRect_1.fX3[iFourCount] += Box_Move2;
			fourRect_1.fX4[iFourCount] += Box_Move2;

			glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
			glBegin(GL_POLYGON);
			glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount] + fTranslate_Four1, 0.0f);
			glEnd();
		}

		if (fFirst_Area < fSecond_Area)
		{
			fourRect_2.fX1[iFourCount] += Box_Move2;
			fourRect_2.fX2[iFourCount] += Box_Move2;
			fourRect_2.fX3[iFourCount] += Box_Move2;
			fourRect_2.fX4[iFourCount] += Box_Move2;

			glColor3f(0.5f, 0.0f, 0.0f);			//왼쪽과 밑
			glBegin(GL_POLYGON);
			glVertex3f(fourRect_2.fX1[iFourCount], fourRect_2.fY1[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(fourRect_2.fX2[iFourCount], fourRect_2.fY2[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(fourRect_2.fX3[iFourCount], fourRect_2.fY3[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(fourRect_2.fX4[iFourCount], fourRect_2.fY4[iFourCount] + fTranslate_Four2, 0.0f);
			glEnd();
		}
	}

	if (Box_to_four2 == true)
	{
		float fFirst_Area = (((fourRect_2.fY1[iFourCount] - fourRect_2.fY4[iFourCount]) + (fourRect_2.fY2[iFourCount] - fourRect_2.fY3[iFourCount]))
			* fourRect_2.fX4[iFourCount] - fourRect_2.fX3[iFourCount]) / 2.f;

		float fSecond_Area = (((fourRect_1.fY4[iFourCount] - fourRect_1.fY1[iFourCount]) + (fourRect_1.fY3[iFourCount] - fourRect_1.fY2[iFourCount]))
			* fourRect_1.fX4[iFourCount] - fourRect_1.fX3[iFourCount]) / 2.f;

		if (fFirst_Area > fSecond_Area)
		{
			fourRect_1.fX1[iFourCount] += Box_Move2;
			fourRect_1.fX2[iFourCount] += Box_Move2;
			fourRect_1.fX3[iFourCount] += Box_Move2;
			fourRect_1.fX4[iFourCount] += Box_Move2;

			if (over == false)
				glColor3f(0.5f, 0.5f, 0.0f);			//오른쪽과 위
			if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fourRect_1.fX1[iFourCount], fourRect_1.fY1[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX2[iFourCount], fourRect_1.fY2[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX3[iFourCount], fourRect_1.fY3[iFourCount] + fTranslate_Four1, 0.0f);
			glVertex3f(fourRect_1.fX4[iFourCount], fourRect_1.fY4[iFourCount] + fTranslate_Four1, 0.0f);
			glEnd();
		}
	}

	if (Box_to_four3 == true)
	{
		float fFirst_Area = (((fourRect_2.fY1[iFourCount] - fourRect_2.fY4[iFourCount]) + (fourRect_2.fY2[iFourCount] - fourRect_2.fY3[iFourCount]))
			* fourRect_2.fX4[iFourCount] - fourRect_2.fX3[iFourCount]) / 2.f;

		float fSecond_Area = (((fourRect_1.fY4[iFourCount] - fourRect_1.fY1[iFourCount]) + (fourRect_1.fY3[iFourCount] - fourRect_1.fY2[iFourCount]))
			* fourRect_1.fX4[iFourCount] - fourRect_1.fX3[iFourCount]) / 2.f;

		if (fFirst_Area < fSecond_Area)
		{
			Temp.fX1[iFourCount] = fourRect_2.fX4[iFourCount];
			Temp.fY1[iFourCount] = fourRect_2.fY4[iFourCount];
			Temp.fX2[iFourCount] = fourRect_2.fX3[iFourCount];
			Temp.fY2[iFourCount] = fourRect_2.fY3[iFourCount];
			Temp.fX3[iFourCount] = fourRect_2.fX2[iFourCount];
			Temp.fY3[iFourCount] = fourRect_2.fY2[iFourCount];
			Temp.fX4[iFourCount] = fourRect_2.fX1[iFourCount];
			Temp.fY4[iFourCount] = fourRect_2.fY1[iFourCount];

			Temp.fX1[iFourCount] += Box_Move2;
			Temp.fX2[iFourCount] += Box_Move2;
			Temp.fX3[iFourCount] += Box_Move2;
			Temp.fX4[iFourCount] += Box_Move2;

			if (over == false)
				glColor3f(0.5f, 0.0f, 0.0f);			//왼쪽과 밑
			if (over == true)
				glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(Temp.fX4[iFourCount], Temp.fY4[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(Temp.fX3[iFourCount], Temp.fY3[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(Temp.fX2[iFourCount], Temp.fY2[iFourCount] + fTranslate_Four2, 0.0f);
			glVertex3f(Temp.fX1[iFourCount], Temp.fY1[iFourCount] + fTranslate_Four2, 0.0f);
			glEnd();

		}
	
		/*if (Box_Cli == true)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount] + fTranslate_Tri, 0.0f);
			glEnd();
		}*/
		
	}

	glPopMatrix();

}

void TimerWaterWave(int vlaue)
{

	for (int i = 0; i < 2; i++)
	{

		if (Water[i] >= -217.f || Water[i] <= -222.f)
		{
			Water_Wave[i] *= -1;
		}

		if (i % 2 == 0)
			Water[i] += Water_Wave[i];
		else
			Water[i] -= Water_Wave[i];

	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerWaterWave, 2);
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && iMove == 0)
	{
		_Mouse[0].fX = x - 400 - Rect_Translate;
		_Mouse[0].fY = -(y - 300);
		bMouse = false;

	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && iMove == 0)
	{
		_Mouse[1].fX = x - 400 - Rect_Translate;
		_Mouse[1].fY = -(y - 300);
		bMouse = true;
		//bLine = true;
		bTriagle = true;
		bFourRect = true;
	}


}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		if (Box_Move_No == false)
			Box_Move_No = true;
		else if (Box_Move_No == true)
			Box_Move_No = false;
	}
	else if (key == 's')
	{
		if (Box_Move_No2 == false)
			Box_Move_No2 = true;
		else if (Box_Move_No2 == true)
			Box_Move_No2 = false;
	}
}

void Cliping()
{

	/*Cliping_M = (Water[0] - Water[1]) / (Water_X1 - Water_X2);
	Cliping_P = Water[0] - Cliping_M * Water_X1;*/

	if (iCheck == 1)
	{
		if (triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[0]
			&& triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2)
		{
			over = true;
		}
		if (Box_Cli == true && over == false)
		{
			//1과 2
	

			fUnder1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]) * (Water[0] - triagnle.fY1[iTriCount])
				- (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) * (Water_X1 - triagnle.fX1[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY1[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX1[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//3과 2
			fUnder2 = (triagnle.fY2[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX2[iTriCount] - triagnle.fX3[iTriCount]) * (Water[1] - Water[0]);
			
			fCross_fT2 = (triagnle.fX2[iTriCount] - triagnle.fX3[iTriCount]) * (Water[0] - triagnle.fY3[iTriCount])
				- (triagnle.fY2[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);
			
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glEnd();

		}
	}

	if (iCheck == 9)
	{
		if (triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[0]
			&& triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1)
		{
			over = true;
		}
		if (Box_Cli == true && over == false)
		{
			//1과 2


			fUnder1 = (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (triagnle.fX2[iTriCount] - triagnle.fX1[iTriCount]) * (Water[0] - triagnle.fY1[iTriCount])
				- (triagnle.fY2[iTriCount] - triagnle.fY1[iTriCount]) * (Water_X1 - triagnle.fX1[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY1[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX1[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//3과 2
			fUnder2 = (triagnle.fY2[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX2[iTriCount] - triagnle.fX3[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (triagnle.fX2[iTriCount] - triagnle.fX3[iTriCount]) * (Water[0] - triagnle.fY3[iTriCount])
				- (triagnle.fY2[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glEnd();

		}
	}

	if (iCheck == 5)
	{
		if (triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[0]
			&& triagnle.fX1[iTriCount] > Water_X1 && triagnle.fX2[iTriCount] < Water_X2)
		{
			over = true;
		}
		if (Box_Cli == true && over == false)
		{
			//1과 3


			fUnder1 = (triagnle.fY1[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX1[iTriCount] - triagnle.fX3[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (triagnle.fX1[iTriCount] - triagnle.fX3[iTriCount]) * (Water[0] - triagnle.fY3[iTriCount])
				- (triagnle.fY1[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//1과 2
			fUnder2 = (triagnle.fY1[iTriCount] - triagnle.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX1[iTriCount] - triagnle.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (triagnle.fX1[iTriCount] - triagnle.fX2[iTriCount]) * (Water[0] - triagnle.fY2[iTriCount])
				- (triagnle.fY1[iTriCount] - triagnle.fY2[iTriCount]) * (Water_X1 - triagnle.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

		}
	}

	if (iCheck == 4)
	{
		if (triagnle.fY1[iTriCount] < Water[0] && triagnle.fY1[iTriCount] < Water[0]
			&& triagnle.fX1[iTriCount] < Water_X2 && triagnle.fX2[iTriCount] > Water_X1)
		{
			over = true;
		}
		if (Box_Cli == true && over == false)
		{
			//1과 3


			fUnder1 = (triagnle.fY1[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX1[iTriCount] - triagnle.fX3[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (triagnle.fX1[iTriCount] - triagnle.fX3[iTriCount]) * (Water[0] - triagnle.fY3[iTriCount])
				- (triagnle.fY1[iTriCount] - triagnle.fY3[iTriCount]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX3[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//1과 2
			fUnder2 = (triagnle.fY1[iTriCount] - triagnle.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (triagnle.fX1[iTriCount] - triagnle.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (triagnle.fX1[iTriCount] - triagnle.fX2[iTriCount]) * (Water[0] - triagnle.fY2[iTriCount])
				- (triagnle.fY1[iTriCount] - triagnle.fY2[iTriCount]) * (Water_X1 - triagnle.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - triagnle.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - triagnle.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(triagnle.fX2[iTriCount], triagnle.fY2[iTriCount], 0.0f);
			glVertex3f(triagnle.fX3[iTriCount], triagnle.fY3[iTriCount], 0.0f);
			glEnd();

		}
	}

	if (iCheck == 3)
	{
		/*Temp.fX1[iFourCount] = fourRect_2.fX4[iFourCount];
		Temp.fY1[iFourCount] = fourRect_2.fY4[iFourCount];
		Temp.fX2[iFourCount] = fourRect_2.fX3[iFourCount];
		Temp.fY2[iFourCount] = fourRect_2.fY3[iFourCount];
		Temp.fX3[iFourCount] = fourRect_2.fX2[iFourCount];
		Temp.fY3[iFourCount] = fourRect_2.fY2[iFourCount];
		Temp.fX4[iFourCount] = fourRect_2.fX1[iFourCount];
		Temp.fY4[iFourCount] = fourRect_2.fY1[iFourCount];*/

		if (fourRect_1.fY3[iFourCount] < Water[0] && fourRect_1.fY3[iFourCount] < Water[1]
			&& fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1)
		{
			over = true;
		}
	/*	if (fourRect_1.fY2[iTriCount] <= Box_aY && fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
			&& fourRect_1.fY3[iTriCount] < Water[0] && fourRect_1.fY3[iTriCount] < Water[1])
		{
			over = true;
		}
		if (fourRect_1.fY1[iTriCount] <= Box_aY && fourRect_1.fX1[iTriCount] < Water_X2 && fourRect_1.fX2[iTriCount] > Water_X1
			&& fourRect_1.fY3[iTriCount] < Water[0] && fourRect_1.fY3[iTriCount] < Water[1])
		{
			over = true;
		}*/

		if (Box_Cli4 == true && over == false)
		{
			//4와 1
			fUnder1 = (fourRect_1.fY4[iTriCount] - fourRect_1.fY1[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_1.fX4[iTriCount] - fourRect_1.fX1[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (fourRect_1.fX4[iTriCount] - fourRect_1.fX1[iTriCount]) * (Water[0] - fourRect_1.fY1[iTriCount])
				- (fourRect_1.fY4[iTriCount] - fourRect_1.fY1[iTriCount]) * (Water_X1 - fourRect_1.fX1[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - fourRect_1.fY1[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_1.fX1[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//3과 2
			fUnder2 = (fourRect_1.fY3[iTriCount] - fourRect_1.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_1.fX3[iTriCount] - fourRect_1.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (fourRect_1.fX3[iTriCount] - fourRect_1.fX2[iTriCount]) * (Water[0] - fourRect_1.fY2[iTriCount])
				- (fourRect_1.fY3[iTriCount] - fourRect_1.fY2[iTriCount]) * (Water_X1 - fourRect_1.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - fourRect_1.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_1.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(fourRect_1.fX2[iTriCount], fourRect_1.fY2[iTriCount], 0.0f);
			glVertex3f(fourRect_1.fX1[iTriCount], fourRect_1.fY1[iTriCount], 0.0f);
			glEnd();
		}
		
		if (Temp.fY3[iFourCount] < Water[0] && Temp.fY4[iFourCount] < Water[1]
			&& Temp.fX1[iTriCount] < Water_X2 && Temp.fX2[iTriCount] > Water_X1)
		{
			over = true;
		}

		if (Box_Cli5 == true && over == false)
		{

			//4와 1
			fUnder1 = (Temp.fY4[iTriCount] - Temp.fY1[iTriCount]) * (Water_X2 - Water_X1)
				- (Temp.fX4[iTriCount] - Temp.fX1[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (Temp.fX4[iTriCount] - Temp.fX1[iTriCount]) * (Water[0] - Temp.fY1[iTriCount])
				- (Temp.fY4[iTriCount] - Temp.fY1[iTriCount]) * (Water_X1 - Temp.fX1[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - Temp.fY1[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - Temp.fX1[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//3과 2
			fUnder2 = (Temp.fY3[iTriCount] - Temp.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (Temp.fX3[iTriCount] - Temp.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (Temp.fX3[iTriCount] - Temp.fX2[iTriCount]) * (Water[0] - Temp.fY2[iTriCount])
				- (Temp.fY3[iTriCount] - Temp.fY2[iTriCount]) * (Water_X1 - Temp.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - Temp.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - Temp.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(Temp.fX2[iTriCount], Temp.fY2[iTriCount], 0.0f);
			glVertex3f(Temp.fX1[iTriCount], Temp.fY1[iTriCount], 0.0f);
			glEnd();
		}

	}

	if (iCheck == 2)
	{
		if (Box_Cli2 == true && over == false)
		{
			//4와 3
			fUnder1 = (fourRect_2.fY4[iTriCount] - fourRect_2.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_2.fX4[iTriCount] - fourRect_2.fX3[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (fourRect_2.fX4[iTriCount] - fourRect_2.fX3[iTriCount]) * (Water[0] - fourRect_2.fY3[iTriCount])
				- (fourRect_2.fY4[iTriCount] - fourRect_2.fY3[iTriCount]) * (Water_X1 - fourRect_2.fX3[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - fourRect_2.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_2.fX3[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//1과 2
			fUnder2 = (fourRect_2.fY1[iTriCount] - fourRect_2.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_2.fX1[iTriCount] - fourRect_2.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (fourRect_2.fX1[iTriCount] - fourRect_2.fX2[iTriCount]) * (Water[0] - fourRect_2.fY2[iTriCount])
				- (fourRect_2.fY1[iTriCount] - fourRect_2.fY2[iTriCount]) * (Water_X1 - fourRect_2.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - fourRect_2.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_2.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(fourRect_2.fX2[iTriCount], fourRect_2.fY2[iTriCount], 0.0f);
			glVertex3f(fourRect_2.fX3[iTriCount], fourRect_2.fY3[iTriCount], 0.0f);
			glEnd();
		}

		if (Box_Cli3 == true && over == false)
		{
			//4와 3
			fUnder1 = (fourRect_1.fY4[iTriCount] - fourRect_1.fY3[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_1.fX4[iTriCount] - fourRect_1.fX3[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT1 = (fourRect_1.fX4[iTriCount] - fourRect_1.fX3[iTriCount]) * (Water[0] - fourRect_1.fY3[iTriCount])
				- (fourRect_1.fY4[iTriCount] - fourRect_1.fY3[iTriCount]) * (Water_X1 - fourRect_1.fX3[iTriCount]);

			fCross_fS1 = (Water_X2 - Water_X1) * (Water[0] - fourRect_1.fY3[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_1.fX3[iTriCount]);

			fCrossfT1 = fCross_fT1 / fUnder1;
			fCrossfS1 = fCross_fS1 / fUnder1;

			fCrossX1 = Water_X1 + fCrossfT1 * (Water_X2 - Water_X1);
			fCrossY1 = Water[0] + fCrossfT1 * (Water[1] - Water[0]);

			//1과 2
			fUnder2 = (fourRect_1.fY1[iTriCount] - fourRect_1.fY2[iTriCount]) * (Water_X2 - Water_X1)
				- (fourRect_1.fX1[iTriCount] - fourRect_1.fX2[iTriCount]) * (Water[1] - Water[0]);

			fCross_fT2 = (fourRect_1.fX1[iTriCount] - fourRect_1.fX2[iTriCount]) * (Water[0] - fourRect_1.fY2[iTriCount])
				- (fourRect_1.fY1[iTriCount] - fourRect_1.fY2[iTriCount]) * (Water_X1 - fourRect_1.fX2[iTriCount]);

			fCross_fS2 = (Water_X2 - Water_X1) * (Water[0] - fourRect_1.fY2[iTriCount])
				- (Water[1] - Water[0]) * (Water_X1 - fourRect_1.fX2[iTriCount]);

			fCrossfT2 = fCross_fT2 / fUnder2;
			fCrossfS2 = fCross_fS2 / fUnder2;

			fCrossX2 = Water_X1 + fCrossfT2 * (Water_X2 - Water_X1);
			fCrossY2 = Water[0] + fCrossfT2 * (Water[1] - Water[0]);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(fCrossX1, fCrossY1, 0.0f);
			glVertex3f(fCrossX2, fCrossY2, 0.0f);
			glVertex3f(fourRect_1.fX2[iTriCount], fourRect_1.fY2[iTriCount], 0.0f);
			glVertex3f(fourRect_1.fX3[iTriCount], fourRect_1.fY3[iTriCount], 0.0f);
			glEnd();
		}
	}


}
