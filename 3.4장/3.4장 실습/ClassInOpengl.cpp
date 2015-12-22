#include <gl/glut.h> // includes gl.h glu.h
#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <chrono>
#include "Timer.h"
using namespace std;
using namespace chrono;
#define PI 3.141592
int g_iCount = 0;
struct ThreePoints
{
	float fX;
	float fY;
	float fZ;
};
struct RGBColor
{
	float R;
	float G;
	float B;
};
struct TwoPoints
{
	float fX;
	float fY;
};
enum FigureType
{
	FT_PLANE,
	FT_TORUS
};

class CModel
{
	ThreePoints	m_tPosition;
	RGBColor	m_tColor;
	FigureType	m_eType;
	float		m_fAngle;
	float		m_fInnerRadius;
	float		m_fOutterRadius;
	float		m_fHeight;
	float		m_fRoute;
	bool		m_isDown;
public:
	float GetAngle()
	{
		return m_fAngle;
	}
	float GetHeight()
	{
		return m_fHeight;
	}
	RGBColor GetColor()
	{
		return m_tColor;
	}
	ThreePoints GetPosition()
	{
		return m_tPosition;
	}
public:
	GLvoid Initialize(int& _count)
	{
		m_tColor = { rand() % 30000, rand() % 30000, rand() % 30000 };
		m_fRoute = 50;
		m_isDown = true;
		m_tPosition.fY = 300;
		m_fInnerRadius = 10.0;
		m_fOutterRadius = 100.0;
		m_fHeight = m_fInnerRadius * 2;
		m_fAngle = 0;
		if ((_count != 0) && (_count % 3 == 0))
		{
			m_eType = FT_PLANE;
		}
		else
			m_eType = FT_TORUS;

	}
	GLvoid Initialize()
	{
		m_tColor = { rand() % 30000, rand() % 30000, rand() % 30000 };
		m_fRoute = 50;
		m_isDown = true;
		m_tPosition.fY = 300;
		m_fInnerRadius = 10.0;
		m_fOutterRadius = 300.0;
		m_fHeight = m_fInnerRadius * 2;
		m_fAngle = 0;
		if ((g_iCount != 0) && (g_iCount % 3 == 0))
		{
			m_eType = FT_PLANE;
		}
		else
			m_eType = FT_TORUS;

	}
	GLvoid DrawModel()
	{
		glColor3f(m_tColor.R / 30000, m_tColor.G / 30000, m_tColor.B / 30000);
		glTranslatef(m_fRoute * cos(m_fAngle*PI / 180), m_tPosition.fY, m_fRoute * sin(m_fAngle*PI / 180));

		if (m_eType == FT_TORUS)
		{
			glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glutWireTorus(m_fInnerRadius, m_fOutterRadius, 10, 30);
			glPopMatrix();
		}
		else if (m_eType == FT_PLANE)
		{
			glPushMatrix();
			glScalef(2.0, 0.2, 2.0);
			glutSolidCube(m_fOutterRadius);
			glPopMatrix();
		}

	}
	GLvoid Update(int& _count)
	{
		if (m_tPosition.fY > 20 + m_fHeight*_count)
		{
			m_tPosition.fY -= 2;
			m_fAngle = ((int)m_fAngle + 5) % 360;
		}
		if (m_tPosition.fY == 20 + m_fHeight*_count && m_isDown == true)
		{
			m_fRoute = 0;
			_count += 1;
			m_isDown = false;
		}
	}
public:
	CModel(){
		Initialize();
		g_iCount += 1;
		if (g_iCount == 14)
			g_iCount = 0;
	}

};

GLvoid	Initialize();
GLvoid	drawScene(GLvoid);
GLvoid	Reshape(int w, int h);
GLvoid	Keyboard(unsigned char key, int x, int y);
GLvoid	SpecialKeyboard(int key, int x, int y);
GLvoid	moveModel(int value);
GLvoid	Initialize();
GLvoid	MenuFunc(int button);
GLvoid	Mouse(int button, int state, int x, int y);
GLvoid	MotionFunc(int x, int y);
GLvoid	DrawTorus();


int iLimit = 0;
float worldRotateAngle_X, worldRotateAngle_Y, worldRotateAngle_Z = 0;
float cameraX = 700.0;
bool isDepthTestOn = true;
bool isCullOn = true;
bool isSmoothOn = true;
bool isUpFaceOn = true;
bool isFrontFaceOn = true;
float torusAngle = 0;
float torusX = 0;
float torusY = 300;
float torusZ = 0;

TwoPoints	tMousePos;
CGameTimer	GameTimer;
CModel		cModel[15];

char test[256] = {};
int frameCount = 0;
float fps = 0;
int currentTime = 0, previousTime = 0;

void main(int argc, char *argv[])
{
	//초기화 함수들 

	srand(unsigned int(time(NULL)));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정 
	glutCreateWindow("실습21"); // 윈도우 생성 (윈도우 이름) 
	Initialize();
	glutDisplayFunc(drawScene);// 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MotionFunc);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, moveModel, 1);
	glutMainLoop();

}



GLvoid drawScene(GLvoid)
{

	// 윈도우 출력 함수
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	gluLookAt(0.0, 200.0, cameraX, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glRotatef(worldRotateAngle_X, 1, 0, 0);
	glRotatef(worldRotateAngle_Y, 0, 1, 0);
	glRotatef(worldRotateAngle_Z, 0, 0, 1);
	//
	glPushMatrix();
	{
		if (isDepthTestOn)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		glPushMatrix();
		{
			glColor3f(1.0, 0.0, 0.0);
			glLineWidth(3.0);
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 300.0, 0.0);
			glEnd();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor3f(0.7, 0.7, 0.7);
			glScalef(3.0, 0.1, 3.0);
			glutSolidCube(200);
		}
		glPopMatrix();
		glPushMatrix();
		{
			for (size_t i = 0; i <= g_iCount; i++)
			{
				if (i == 0)
					continue;
				glPushMatrix();
				{
					cModel[i].DrawModel();
				}
				glPopMatrix();
			}
			//DrawTorus();
		}
		glPopMatrix();

	}
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(60, 310, 0);
	for (int i = 0; i < 256; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, test[i]);
	}

	glutSwapBuffers(); // 결과 출력

}

GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0, w / h, 1.0, 1000.0);
	/*gluLookAt(0.0, 150.0, 700.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);*/
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '4':	// 키패드 왼쪽 방향키
		worldRotateAngle_Y += 1;
		break;
	case '5':	// 키패드 아래쪽 방향키
		worldRotateAngle_X -= 1;
		break;
	case '8':
		worldRotateAngle_X += 1;
		break;
	case 'q':	// 키패드 오른쪽 방향키
		worldRotateAngle_Z -= 1;
		break;
	case 'e':	// 키패드 위쪽 방향키
		worldRotateAngle_Z += 1;
		break;
	case '+':
		cameraX -= 2;
		break;
	case '-':
		cameraX += 2;
	case 'b':
		if (iLimit == 5)
			break;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid moveModel(int value)
{
	GameTimer.Tick();
	cModel[g_iCount].Update(g_iCount);
	if (g_iCount == 14)
	{
		for (int i = 0; i <= g_iCount; i++)
		{
			cModel[i].Initialize(i);
			//g_iCount += 1;
			//if (g_iCount == 14)
			//g_iCount = 0;
			printf("%d\n", g_iCount);
		}
		g_iCount = 0;
	}

	glutPostRedisplay();
	GameTimer.GetFrameRate(test + 12, 37);
	glutTimerFunc(10, moveModel, 1);
}


GLvoid MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		isDepthTestOn = true;
		break;
	case 2:
		isDepthTestOn = false;
		break;
	case 3:
		isCullOn = true;
		break;
	case 4:
		isCullOn = false;
		break;
	case 5:
		isSmoothOn = false;
		break;
	case 6:
		isSmoothOn = true;
		break;
	case 7:
		isUpFaceOn = true;
		break;
	case 8:
		isUpFaceOn = false;
		break;
	case 9:
		isFrontFaceOn = true;
		break;
	case 10:
		isFrontFaceOn = false;
		break;
	case 11:
		exit(0);
		break;
	}
	glutPostRedisplay();
}
GLvoid Initialize()
{


	int depthChoice = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("켜기", 1);
	glutAddMenuEntry("끄기", 2);
	int cullingChoice = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("켜기", 3);
	glutAddMenuEntry("끄기", 4);
	int shadeChoice = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("평면 쉐이딩", 5);
	glutAddMenuEntry("부드러운 쉐이딩", 6);
	int upFaceChoice = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("그리기", 7);
	glutAddMenuEntry("지우기", 8);
	int frontFaceChoice = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("그리기", 9);
	glutAddMenuEntry("지우기", 10);
	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면 제거", depthChoice);
	glutAddSubMenu("컬링", cullingChoice);
	glutAddSubMenu("쉐이딩", shadeChoice);
	glutAddSubMenu("윗면", upFaceChoice);
	glutAddSubMenu("앞면", frontFaceChoice);
	glutAddMenuEntry("종료", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

GLvoid	Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		tMousePos.fX = x;
		tMousePos.fY = 800 - y;
	}
	glutPostRedisplay();
}

GLvoid MotionFunc(int x, int y)
{
	TwoPoints tempMousePos = { x, 600 - y };
	if (tMousePos.fX > tempMousePos.fX)
	{
		worldRotateAngle_Y += 1;
	}
	else if (tMousePos.fX < tempMousePos.fX)
	{
		worldRotateAngle_Y -= 1;
	}
	glutPostRedisplay();
}

GLvoid DrawTorus()
{
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(50 * cos(torusAngle*PI / 180), torusY, 50 * sin(torusAngle*PI / 180));
	glRotatef(90, 1, 0, 0);
	glutWireTorus(10.0, 100.0, 10, 30);
}
