#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	float iX;
	float iY;
	float iX2;
	float iY2;
	float Red;
	float Green;
	float Blue;
	int Rotate;

}Rect;

GLvoid Mouse(int button, int state, int iX, int iY);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void TimeRotateFunction(int value);
void Keyboard(unsigned char key, int x, int y);
int iCount = 0;
float iSpeed = 10.f;
int Render_Count = 0;
Rect RectInfomation[10];

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("실습4");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	//glutTimerFunc(100, TimeRotateFunction, 2);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Render_Count; ++i)
	{
		glColor3f(RectInfomation[i].Red, RectInfomation[i].Green, RectInfomation[i].Blue);
		glRectf(RectInfomation[i].iX, 600.f - RectInfomation[i].iY, RectInfomation[i].iX2, 600.f - RectInfomation[i].iY2);
		/*glBegin(GL_POLYGON);
		glVertex2f(RectInfomation[i].iX - 20.f, 600.f - RectInfomation[i].iY + 10.f);		//왜 600에서 빼야하나??
		glVertex2f(RectInfomation[i].iX + 20.f, 600.f - RectInfomation[i].iY + 10.f);
		glVertex2f(RectInfomation[i].iX + 20.f, 600.f - RectInfomation[i].iY - 10.f);
		glVertex2f(RectInfomation[i].iX - 20.f, 600.f - RectInfomation[i].iY - 10.f);
		glEnd();*/
	}

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int iX, int iY)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (iCount == 10)
			iCount = 0;

		RectInfomation[iCount].iX = iX - 20.f;
		RectInfomation[iCount].iY = iY + 10.f;
		RectInfomation[iCount].iX2 = iX + 20.f;
		RectInfomation[iCount].iY2 = iY - 10.f;
		RectInfomation[iCount].Red = 0.3f;
		RectInfomation[iCount].Green = 0.4f;
		RectInfomation[iCount].Blue = 0.6f;
		RectInfomation[iCount].Rotate = 0;
		++iCount;
		//폭40 높이20인 사각형을 만든다.
		if (Render_Count < 10)
			Render_Count += 1;

	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	for (int i = 0; i < Render_Count; ++i)
	{
		if (RectInfomation[i].iX2 >= 800)
			RectInfomation[i].Rotate = 1;
		else if (RectInfomation[i].iY <= 0)
			RectInfomation[i].Rotate = 2;
		else if (RectInfomation[i].iX <= 0)
			RectInfomation[i].Rotate = 3;
		else if (RectInfomation[i].iY2 >= 600)
			RectInfomation[i].Rotate = 0;

		if (RectInfomation[i].Rotate == 0)
		{
			RectInfomation[i].iX += iSpeed;
			RectInfomation[i].iY -= iSpeed - 5.f;;
			RectInfomation[i].iX2 += iSpeed;
			RectInfomation[i].iY2 -= iSpeed - 5.f;;
		}

		else if (RectInfomation[i].Rotate == 1)
		{
			RectInfomation[i].iX -= iSpeed;
			RectInfomation[i].iY -= iSpeed;
			RectInfomation[i].iX2 -= iSpeed;
			RectInfomation[i].iY2 -= iSpeed;
		}

		else if (RectInfomation[i].Rotate == 2)
		{
			RectInfomation[i].iX -= iSpeed;
			RectInfomation[i].iY += iSpeed;
			RectInfomation[i].iX2 -= iSpeed;
			RectInfomation[i].iY2 += iSpeed;
		}

		else if (RectInfomation[i].Rotate == 3)
		{
			RectInfomation[i].iX += iSpeed;
			RectInfomation[i].iY += iSpeed;
			RectInfomation[i].iX2 += iSpeed;
			RectInfomation[i].iY2 += iSpeed;
		}
	}

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void TimeRotateFunction(int value)
{
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimeRotateFunction, 2); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		iSpeed += 5.f;

	if (key == '-')
		iSpeed -= 5.f;
}
