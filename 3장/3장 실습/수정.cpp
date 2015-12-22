#include <GL/glut.h> // includes gl.h glu.h
#include <stdlib.h>	//중복없는 난수를 위한 헤더1
#include <time.h>	//중복없는 난수를 위한 헤더2

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

struct point{
	int x;
	int y;
};

point p[10];
int btt = 0;
int click = 0;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));		//시간마다 난수를 다르게 해서 중복을 피함
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse); // 마우스 콜백함수
	glutTimerFunc(1000, Timerfunction, 1);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'White' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (int i = 0; i < 10; i++)
	{
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'red' 으로 지정
		glRectf(p[i].x, p[i].y, p[i].x + 40, p[i].y - 40); // 사각형 그리기
	}
	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Timerfunction(int value)
{
	p[btt].x = rand() % 760 + 40;
	p[btt].y = rand() % 560 + 40;
	btt++;

	glutPostRedisplay();
	glutTimerFunc(1000, Timerfunction, 1);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		click = 1;
	}
}

void init()
{
	for (int i = 0; i < 10; i++)
	{
		p[i].x = 1000;
	}
}