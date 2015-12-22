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
	int R;
	int G;
	int B;
};
struct TwoPoints
{
	float fX;
	float fY;
};
enum LIGHTNUM
{
	LIGHT0,
	LIGHT1,
	LIGHT2,
	LIGHT3,
	LIGHT4,
	LIGHT5,
	LIGHT6,
	LIGHT7
};

class CModel
{
	ThreePoints	m_tPosition;
	RGBColor	m_tColor;
	float		m_fAngle;
	float		m_fInnerAngle;
	float		m_fInnerRadius;
	float		m_fSize;
public:
	float GetAngle()
	{
		return m_fAngle;
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
	GLvoid Initialize()
	{
		m_tColor = { rand() % 255, rand() % 255, rand() % 255 };
		m_tPosition = { 100, 100, 0 };
		m_fAngle = 0;
		m_fInnerAngle = 0;

	}
	GLvoid DrawModel()
	{
		glTranslatef(0, m_tPosition.fY, 0);
		glRotatef(90, 1, 0, 0);
		glColor3ub(50, 50, 255);
		glTranslatef(m_fInnerRadius * cos(m_fAngle*PI / 180), m_fInnerRadius * sin(m_fAngle*PI / 180), 0.0);
		glutSolidSphere(m_fSize, 50, 50);
		glColor3ub(255, 255, 125);
		glTranslatef(50 * cos(m_fInnerAngle*PI / 180), 50 * sin(m_fInnerAngle*PI / 180), 0.0);
		glutSolidSphere(10, 50, 50);

		//	glTranslatef(m_tPosition.fX,m_tPosition.fY, m_tPosition.fZ);
		/*glColor3f(1.0, 0.0, 0.0);
		glTranslatef(50 * cos((innerPlanetOneAngle)*PI / 180), 50 * sin((innerPlanetOneAngle)*PI / 180), 0.0);
		glutSolidSphere(10, 10, 10);*/

	}
	GLvoid Update()
	{
		if (m_fAngle >360)
			m_fAngle = 0;
		if (m_fInnerAngle > 360)
			m_fInnerAngle = 0;
		m_fAngle += 1;
		m_fInnerAngle += 2;
	}
public:
	CModel(float _Size, float _InnerRadius){
		m_fSize = _Size;
		m_fInnerRadius = _InnerRadius;

	}

};

class CLight
{
	float m_fAmbientLight[4];
	float m_fDiffuseLight[4];
	float m_fSpecularLight[4];
	float m_fLightPos[4];
	LIGHTNUM m_eLightNum;
public:
	void SetAmbientLight(float _R, float _G, float _B, float _A = 1.0)
	{
		m_fAmbientLight[0] = _R;
		m_fAmbientLight[1] = _G;
		m_fAmbientLight[2] = _B;
		m_fAmbientLight[3] = _A;
	}
	void SetDiffuseLight(float _R, float _G, float _B, float _A = 1.0)
	{
		m_fDiffuseLight[0] = _R;
		m_fDiffuseLight[1] = _G;
		m_fDiffuseLight[2] = _B;
		m_fDiffuseLight[3] = _A;
	}
	void SetSpecularLight(float _R, float _G, float _B, float _A = 1.0)
	{
		m_fSpecularLight[0] = _R;
		m_fSpecularLight[1] = _G;
		m_fSpecularLight[2] = _B;
		m_fSpecularLight[3] = _A;
	}
	void SetLightPos(float _X, float _Y, float _Z, float _W = 1.0)
	{
		m_fLightPos[0] = _X;
		m_fLightPos[1] = _Y;
		m_fLightPos[2] = _Z;
		m_fLightPos[3] = _W;
	}
	void SetLightNum(LIGHTNUM _LightNum)
	{
		m_eLightNum = _LightNum;
	}
public:
	float* GetAmbientLight()
	{
		return m_fAmbientLight;
	}
	float* GetDiffuseLight()
	{
		return m_fDiffuseLight;
	}
	float* GetSpecularLight()
	{
		return m_fSpecularLight;
	}
	float* GetLightPos()
	{
		return m_fLightPos;
	}
public:
	void LightInit(LIGHTNUM _LightNum)
	{
		switch (_LightNum)
		{
		case LIGHT0:
			m_eLightNum = _LightNum;
			glLightfv(GL_LIGHT0, GL_AMBIENT, m_fAmbientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, m_fDiffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, m_fSpecularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, m_fLightPos);
			break;
		case LIGHT1:
			m_eLightNum = _LightNum;
			glLightfv(GL_LIGHT1, GL_AMBIENT, m_fAmbientLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, m_fDiffuseLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, m_fSpecularLight);
			glLightfv(GL_LIGHT1, GL_POSITION, m_fLightPos);
			break;
		case LIGHT2:
			break;
		case LIGHT3:
			break;
		case LIGHT4:
			break;
		case LIGHT5:
			break;
		case LIGHT6:
			break;
		case LIGHT7:
			break;
		}

	}
};


GLvoid	Initialize();
GLvoid	LightInit();
GLvoid	drawScene(GLvoid);
GLvoid	Reshape(int w, int h);
GLvoid	Keyboard(unsigned char key, int x, int y);
GLvoid	SpecialKeyboard(int key, int x, int y);
GLvoid	moveModel(int value);
GLvoid	Initialize();
GLvoid	MenuFunc(int button);
GLvoid	Mouse(int button, int state, int x, int y);
GLvoid	MotionFunc(int x, int y);


float worldRotateAngle_X, worldRotateAngle_Y, worldRotateAngle_Z = 0;
float cameraX = 700.0;
bool isDepthTestOn = true;
bool isCullOn = true;
bool isSmoothOn = true;
bool isUpFaceOn = true;
bool isFrontFaceOn = true;
bool isRightOn = false;
bool isLeftOn = false;
float rightPos = 0;
float leftPos = 0;
CLight leftLight;
CLight rightLight;
CModel cEarth(25, 150);

GLfloat ambientf[] = { 0.3, 0.3, 0.3, 0.0 };
GLfloat diffusef[] = { 0.6, 0.6, 0.6, 0.0 };
GLfloat specref[] = { 0.1, 0.1, 0.1, 1.0 };


TwoPoints	tMousePos;
CGameTimer	GameTimer;


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
	leftLight.SetAmbientLight(leftLight.GetAmbientLight()[0],
		leftLight.GetAmbientLight()[1],
		leftLight.GetAmbientLight()[2]);
	leftLight.SetDiffuseLight(leftLight.GetDiffuseLight()[0],
		leftLight.GetDiffuseLight()[1],
		leftLight.GetDiffuseLight()[2]);
	leftLight.SetSpecularLight(leftLight.GetSpecularLight()[0],
		leftLight.GetSpecularLight()[1],
		leftLight.GetSpecularLight()[2]);
	leftLight.LightInit(LIGHT0);
	rightLight.SetAmbientLight(rightLight.GetAmbientLight()[0],
		rightLight.GetAmbientLight()[1],
		rightLight.GetAmbientLight()[2]);
	rightLight.SetDiffuseLight(rightLight.GetDiffuseLight()[0],
		rightLight.GetDiffuseLight()[1],
		rightLight.GetDiffuseLight()[2]);
	rightLight.SetSpecularLight(rightLight.GetSpecularLight()[0],
		rightLight.GetSpecularLight()[1],
		rightLight.GetSpecularLight()[2]);
	rightLight.LightInit(LIGHT1);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glLoadIdentity();
	gluLookAt(0.0, 200.0, cameraX, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glRotatef(worldRotateAngle_X, 1, 0, 0);
	glRotatef(worldRotateAngle_Y, 0, 1, 0);
	glRotatef(worldRotateAngle_Z, 0, 0, 1);
	glEnable(GL_NORMALIZE);
	//glNormal3f(0, -1, 0);
	//leftLight.SetLightPos(leftLight.GetLightPos()[0], rightPos, leftLight.GetLightPos()[2]);
	glPushMatrix();
	{
		glShadeModel(GL_SMOOTH);

		glPushMatrix();
		{
			//glTranslatef(-500, 0, -800);
			if (isLeftOn == true)
				glEnable(GL_LIGHT0);
			else if (isLeftOn == false)
				glDisable(GL_LIGHT0);

			glPushMatrix();
			{
				glTranslatef(0, rightPos, 0);
				glTranslatef(leftLight.GetLightPos()[0], leftLight.GetLightPos()[1], leftLight.GetLightPos()[2]);
				glutSolidCone(5, 10, 5, 5);
			}
			glPopMatrix();

			//glTranslatef(500, 0, -800);
			if (isRightOn == true)
				glEnable(GL_LIGHT1);
			else if (isRightOn == false)
				glDisable(GL_LIGHT1);
			glPushMatrix();
			{
				glTranslatef(0, rightPos, 0);
				glTranslatef(rightLight.GetLightPos()[0], rightLight.GetLightPos()[1], rightLight.GetLightPos()[2]);
				glutSolidCone(5, 10, 5, 5);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{

			glColor3ub(255, 255, 0);
			glTranslatef(0, 0, 0);
			glScalef(5.0, 0.1, 5.0);
			//
			glNormal3f(0, 1, 0);
			glutSolidCube(100);
		}
		glPopMatrix();
		glPushMatrix();
		{

			glBegin(GL_POLYGON);
			glColor3ub(255, 0, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(0, 100, 0);
			glColor3ub(255, 255, 0);
			glNormal3f(-1, 2, 0);
			glVertex3f(-50, 0, -50);
			glColor3ub(0, 255, 0);
			glNormal3f(-1, 2, 0);
			glVertex3f(-50, 0, 50);
			glColor3ub(0, 0, 255);
			glNormal3f(1, 2, 0);
			glVertex3f(50, 0, 50);
			glColor3ub(0, 255, 255);
			glNormal3f(1, 2, 0);
			glVertex3f(50, 0, -50);
			glColor3ub(255, 255, 0);
			glNormal3f(-1, 2, -1);
			glVertex3f(-50, 0, -50);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3ub(50, 50, 255);
			cEarth.DrawModel();
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
	//leftLight.SetLightPos(leftLight.GetLightPos()[0], rightPos, leftLight.GetLightPos()[2]);
	glTranslatef(0, rightPos, 0);
	glutSwapBuffers(); // 결과 출력

}

GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0, w / h, 1.0, 1000.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (isLeftOn == true)
			isLeftOn = false;
		else if (isLeftOn == false)
			isLeftOn = true;
		break;
	case '2':
		if (isRightOn == true)
			isRightOn = false;
		else if (isRightOn == false)
			isRightOn = true;

		break;
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
	case 'a':
		leftLight.SetAmbientLight(leftLight.GetAmbientLight()[0] - 0.1,
			leftLight.GetAmbientLight()[1] - 0.1,
			leftLight.GetAmbientLight()[2] - 0.1);
		rightLight.SetAmbientLight(rightLight.GetAmbientLight()[0] - 0.1,
			rightLight.GetAmbientLight()[1] - 0.1,
			rightLight.GetAmbientLight()[2] - 0.1);
		break;
	case 'A':
		leftLight.SetAmbientLight(leftLight.GetAmbientLight()[0] + 0.1,
			leftLight.GetAmbientLight()[1] + 0.1,
			leftLight.GetAmbientLight()[2] + 0.1);
		rightLight.SetAmbientLight(rightLight.GetAmbientLight()[0] + 0.1,
			rightLight.GetAmbientLight()[1] + 0.1,
			rightLight.GetAmbientLight()[2] + 0.1);
		break;
	case 'd':
		leftLight.SetDiffuseLight(leftLight.GetDiffuseLight()[0] - 0.1,
			leftLight.GetDiffuseLight()[1] - 0.1,
			leftLight.GetDiffuseLight()[2] - 0.1);
		rightLight.SetDiffuseLight(rightLight.GetDiffuseLight()[0] - 0.1,
			rightLight.GetDiffuseLight()[1] - 0.1,
			rightLight.GetDiffuseLight()[2] - 0.1);
		break;
	case 'D':
		leftLight.SetDiffuseLight(leftLight.GetDiffuseLight()[0] + 0.1,
			leftLight.GetDiffuseLight()[1] + 0.1,
			leftLight.GetDiffuseLight()[2] + 0.1);
		rightLight.SetDiffuseLight(rightLight.GetDiffuseLight()[0] + 0.1,
			rightLight.GetDiffuseLight()[1] + 0.1,
			rightLight.GetDiffuseLight()[2] + 0.1);
		break;
	case 's':
		leftLight.SetSpecularLight(leftLight.GetSpecularLight()[0] - 0.1,
			leftLight.GetSpecularLight()[1] - 0.1,
			leftLight.GetSpecularLight()[2] - 0.1);
		rightLight.SetSpecularLight(rightLight.GetSpecularLight()[0] - 0.1,
			rightLight.GetSpecularLight()[1] - 0.1,
			rightLight.GetSpecularLight()[2] - 0.1);
		break;
	case 'S':
		leftLight.SetSpecularLight(leftLight.GetSpecularLight()[0] + 0.1,
			leftLight.GetSpecularLight()[1] + 0.1,
			leftLight.GetSpecularLight()[2] + 0.1);
		rightLight.SetSpecularLight(rightLight.GetSpecularLight()[0] + 0.1,
			rightLight.GetSpecularLight()[1] + 0.1,
			rightLight.GetSpecularLight()[2] + 0.1);
		break;

	case '+':
		cameraX -= 2;
		break;
	case '-':
		cameraX += 2;
	case 'b':
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
		rightPos -= 5;
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		rightPos += 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid moveModel(int value)
{
	GameTimer.Tick();
	cEarth.Update();
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
	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면 제거", depthChoice);
	glutAddSubMenu("컬링", cullingChoice);
	glutAddMenuEntry("종료", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	cEarth.Initialize();
	LightInit();
	glEnable(GL_DEPTH_TEST);
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

GLvoid LightInit()
{
	leftLight.SetAmbientLight(0.1f, 0.1f, 0.1f);
	leftLight.SetDiffuseLight(0.7f, 0.7f, 0.7f);
	leftLight.SetSpecularLight(0.1f, 0.1f, 0.1f);
	leftLight.SetLightPos(-400, 100, 0, 1.0);
	leftLight.LightInit(LIGHT0);
	//glEnable(GL_LIGHTING);
	rightLight.SetAmbientLight(0.1f, 0.1f, 0.1f);
	rightLight.SetDiffuseLight(0.7f, 0.7f, 0.7f);
	rightLight.SetSpecularLight(0.1f, 0.1f, 0.1f);
	rightLight.SetLightPos(400, 100, 0, 1.0);
	//rightLight.LightInit(LIGHT1);
	//glEnable(GL_LIGHTING);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientf);

	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


}


